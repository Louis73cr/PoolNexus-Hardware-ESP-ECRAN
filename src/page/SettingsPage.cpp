/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   SettingsPage.cpp                               :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: Louis Croci <louis.croci@epitech.eu>       +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/13 23:15:49 by Louis Croci    #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/13 23:15:49 by Louis Croci    ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */

/**
 * @file SettingsPage.cpp
 * @brief Implémentation de la page de paramètres avec pagination
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#include "SettingsPage.hpp"
#include "utils/interface-utils.hpp"

SettingsPage::SettingsPage(Display* display, TouchScreen* touch)
    : Page(display, touch), currentPage(0), nextPageId(-1)
{
    utils = new interfaceUtils(display);
}

SettingsPage::~SettingsPage() {
    delete utils;
}

// Callbacks statiques
void SettingsPage::onCloseClick(void* context) {
    SettingsPage* page = static_cast<SettingsPage*>(context);
    Serial.println("Bouton fermer cliqué - Retour à la page précédente");
    page->nextPageId = PAGE_MAIN_DISPLAY;  // Code spécial pour goBack()
}

void SettingsPage::onPreviousClick(void* context) {
    SettingsPage* page = static_cast<SettingsPage*>(context);
    if (page && page->currentPage > 0) {
        page->previousPage();
    }
}

void SettingsPage::onNextClick(void* context) {
    SettingsPage* page = static_cast<SettingsPage*>(context);
    if (page && page->currentPage < page->totalPages - 1) {
        page->nextPage();
    }
}

void SettingsPage::draw() {
    utils->clearButtons();
    
    // Fond gris clair
    utils->drawBackground(interfaceUtils::PAGE, onCloseClick, this, "Parametres");
    
    // Dessiner le contenu de la page
    drawPageContent();
    
    // Boutons de navigation en bas
    const int16_t btnY = display->getHeight() - 60;
    const int16_t btnW = 120;
    const int16_t btnH = 50;
    
    // Bouton Précédent (gris si page 0) - sans TextZone, on dessine le texte manuellement
    bool prevActive = currentPage > 0;
    TextZone* Text_previouse = new TextZone( -1, 0, 0, "<", prevActive ? interfaceUtils::COLOR_BLANC : interfaceUtils::COLOR_BLACK, true);
    interfaceUtils::ButtonZone prevBtn(1, 53, btnY, btnW, btnH, 
                      prevActive ? interfaceUtils::COLOR_BLEU : interfaceUtils::COLOR_GREY_LOW, 
                      prevActive, Text_previouse, nullptr, onPreviousClick, this);
    utils->createButton(prevBtn);
    btnPrevious = 1;
    
    
    // Bouton Suivant (gris si dernière page) - sans TextZone, on dessine le texte manuellement
    bool nextActive = currentPage < totalPages - 1;
    TextZone* Text_next = new TextZone( -1, 0, 0, ">", nextActive ? interfaceUtils::COLOR_BLANC : interfaceUtils::COLOR_BLACK, true);
    interfaceUtils::ButtonZone nextBtn(2, display->getWidth() - 173, btnY, btnW, btnH,
                      nextActive ? interfaceUtils::COLOR_BLEU : interfaceUtils::COLOR_GREY_LOW,
                      nextActive, Text_next, nullptr, onNextClick, this);
    utils->createButton(nextBtn);
    btnNext = 2;
    
    display->flush();
}

void SettingsPage::drawPageContent() {
    const int16_t startY = 70;
    const int16_t btnWidth = display->getWidth() - 100;
    const int16_t btnHeight = 50;
    const int16_t spacing = 15;
    
    // Définir les textes selon la page
    const char* texts[5][3] = {
        {"Pompe", "Calibration Redox", "Calibration pH"},
        {"Interrupteur", "Remplisage piscine", "MQTT"},
        {"Sonde niveaux produits", "Verrouillage", "Ecran"},
        {"Language", "Cloud", "WiFi"},
        {"Reinitialisation", "", ""}
    };
    
    for (int i = 0; i < 3; i++) {
        if (strlen(texts[currentPage][i]) > 0) {
            int16_t y = startY + (btnHeight + spacing) * i;
            
            // Créer le bouton sans TextZone
            TextZone* Text_setting = new TextZone( -1, 0, 0, texts[currentPage][i], interfaceUtils::COLOR_BLACK, true, 4);
            interfaceUtils::ButtonZone settingBtn(3 + i, 50, y, btnWidth, btnHeight,
                                 interfaceUtils::COLOR_BLANC, true, Text_setting, nullptr, nullptr, this);
            utils->createButton(settingBtn);
            
            if (i == 0) btnSetting1 = 3;
            else if (i == 1) btnSetting2 = 4;
            else if (i == 2) btnSetting3 = 5;
        }
    }
    
    // Afficher la version sur la dernière page
    if (currentPage == 4) {
        display->setTextSize(1);
        display->setTextColor(interfaceUtils::COLOR_GREY_HIGH);
        display->setCursor(display->getWidth() / 2 - 50, 200);
        display->print("Version : 1.0.1");
    }
}

void SettingsPage::previousPage() {
    if (currentPage > 0) {
        currentPage--;
        draw();
    }
}

void SettingsPage::nextPage() {
    if (currentPage < totalPages - 1) {
        currentPage++;
        draw();
    }
}

int SettingsPage::handleTouch(uint16_t x, uint16_t y) {
    // Réinitialiser nextPageId
    nextPageId = -1;
    
    int touchedBtn = utils->getTouchedButton(x, y);
    
    if (touchedBtn >= 0) {
        // Exécuter le callback du bouton touché
        utils->executeButtonCallback(touchedBtn);
        delay(100);
        
        // Gestion spéciale des boutons de paramètres (si pas de callback défini)
        if (touchedBtn == btnSetting1 || touchedBtn == btnSetting2 || touchedBtn == btnSetting3) {
            int buttonIndex = touchedBtn - 3; // 0, 1 ou 2
            
            // Mapping des boutons vers les pages selon currentPage et buttonIndex
            const int pageMapping[5][3] = {
                {PAGE_PUMP, PAGE_CALIBRATION_REDOX, PAGE_CALIBRATION_PH},      // Page 0
                {PAGE_SWITCH, PAGE_POOL_FILL, PAGE_MQTT},                      // Page 1
                {PAGE_LEVEL_PROBE, PAGE_LOCK, PAGE_SCREEN},                    // Page 2
                {PAGE_LANGUAGE, PAGE_CLOUD, PAGE_WIFI},                        // Page 3
                {PAGE_RESET, -1, -1}                                           // Page 4
            };
            
            int targetPage = pageMapping[currentPage][buttonIndex];
            
            if (targetPage >= 0) {
                Serial.printf("Navigation vers page %d\n", targetPage);
                nextPageId = targetPage;
            }
        }
    }
    
    return nextPageId;
}
