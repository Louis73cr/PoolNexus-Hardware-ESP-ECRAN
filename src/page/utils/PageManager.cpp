/*
 * PageManager.cpp - Implémentation du gestionnaire de pages
 */

#include "PageManager.hpp"

PageManager::PageManager(Display* display, TouchScreen* touch, int maxPages)
    : display(display)
    , touch(touch)
    , numPages(maxPages)
    , currentPageId(-1)
    , historySize(0)
{
    // Allocation du tableau de pages
    pages = new Page*[maxPages];
    for (int i = 0; i < maxPages; i++) {
        pages[i] = nullptr;
    }
}

PageManager::~PageManager() {
    // Libération de la mémoire
    if (pages) {
        delete[] pages;
    }
}

void PageManager::registerPage(int pageId, Page* page) {
    if (pageId >= 0 && pageId < numPages) {
        pages[pageId] = page;
        Serial.printf("Page %d enregistrée\n", pageId);
    } else {
        Serial.printf("Erreur: ID de page invalide: %d\n", pageId);
    }
}

void PageManager::setCurrentPage(int pageId, bool addToHistory) {
    if (pageId < 0 || pageId >= numPages || pages[pageId] == nullptr) {
        Serial.printf("Erreur: Page %d invalide ou non enregistrée\n", pageId);
        return;
    }
    
    // Appelle onExit() de la page actuelle
    if (currentPageId >= 0 && pages[currentPageId] != nullptr) {
        pages[currentPageId]->onExit();
    }
    
    // Ajoute à l'historique
    if (addToHistory && currentPageId >= 0) {
        if (historySize < MAX_PAGE_HISTORY) {
            pageHistory[historySize++] = currentPageId;
        } else {
            // Décale l'historique si plein
            for (int i = 0; i < MAX_PAGE_HISTORY - 1; i++) {
                pageHistory[i] = pageHistory[i + 1];
            }
            pageHistory[MAX_PAGE_HISTORY - 1] = currentPageId;
        }
    }
    
    // Change de page
    currentPageId = pageId;
    
    // Appelle onEnter() de la nouvelle page
    if (pages[currentPageId] != nullptr) {
        pages[currentPageId]->onEnter();
        Serial.printf("Transition vers page %d\n", pageId);
    }
}

bool PageManager::goBack() {
    if (historySize > 0) {
        // Récupère la page précédente
        int previousPageId = pageHistory[--historySize];
        
        // Change de page sans ajouter à l'historique
        setCurrentPage(previousPageId, false);
        
        Serial.printf("Retour vers page %d\n", previousPageId);
        return true;
    }
    
    Serial.println("Pas d'historique pour retour");
    return false;
}

void PageManager::clearHistory() {
    historySize = 0;
    Serial.println("Historique effacé");
}

void PageManager::update() {
    if (currentPageId < 0 || pages[currentPageId] == nullptr) {
        return;
    }
    
    Page* currentPage = pages[currentPageId];
    
    // 1. Dessine la page si nécessaire
    if (currentPage->getNeedsRedraw()) {
        currentPage->draw();
        display->flush();
        currentPage->clearRedrawFlag();
    }
    
    // 2. Met à jour la logique de la page
    currentPage->update();
    
    // 3. Gère les événements tactiles
    uint16_t x, y;
    if (touch->getTouchPoint(x, y)) {
        int nextPageId = currentPage->handleTouch(x, y);
        
        // Si la page retourne un ID valide, change de page
        if (nextPageId >= 0 && nextPageId != currentPageId) {
            setCurrentPage(nextPageId);
        }
        
        // Anti-rebond: attend que l'écran soit relâché
        touch->waitForRelease(1000);
    }
}

void PageManager::forceRedraw() {
    if (currentPageId >= 0 && pages[currentPageId] != nullptr) {
        pages[currentPageId]->setNeedsRedraw();
    }
}
