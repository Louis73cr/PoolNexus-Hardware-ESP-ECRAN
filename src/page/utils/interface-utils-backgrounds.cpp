/**
 * @file interface-utils-backgrounds.cpp
 * @brief Implémentation des fonds d'écran selon le type de page
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#include "interface-utils.hpp"

/**
 * @brief Dessine le fond d'écran en fonction du type de page
 */
void interfaceUtils::drawBackground(PAGE_TYPE pageType, void (*callback)(void*), void* context, String title) {
    switch (pageType) {
        case START_PAGE:
            // Fond dégradé bleu pour la page de démarrage
            display->fillScreen(COLOR_BLEU_NEXUS);
            
            // Logo ou titre centré
            display->setTextSize(3);
            display->setTextColor(COLOR_BLANC);
            display->setCursor(display->getWidth() / 2 - 100, display->getHeight() / 2 - 50);
            display->print("PoolNexus");
            
            // Version ou sous-titre
            display->setTextSize(1);
            display->setCursor(display->getWidth() / 2 - 60, display->getHeight() / 2);
            display->print("Pool Controller");
            break;
            
        case HOME:
            // Fond avec en-tête et zone de contenu
            display->fillScreen(COLOR_BLANC_CASER);
            
            // En-tête bleu
            display->fillRect(0, 0, display->getWidth(), 60, COLOR_BLEU_NEXUS);
            display->setTextSize(2);
            display->setTextColor(COLOR_BLANC);
            display->setCursor(20, 22);
            display->print("Accueil");
            
            // Bouton retour si callback fourni
            if (callback != nullptr) {
                TextZone* backText = new TextZone(nextButtonId, 0, 0, "<", COLOR_BLANC, true);
                ButtonZone backButton(
                    nextButtonId++,
                    10, 15, 40, 30,
                    COLOR_BLEU,
                    true,
                    backText,
                    nullptr,
                    callback,
                    context
                );
                createButton(backButton);
            }
            break;
            
        case PAGE: {
            // Fond standard pour pages génériques
            display->fillScreen(COLOR_BLANC_CASER);
            
            // Barre supérieure simple
            display->fillRect(0, 0, display->getWidth(), 50, COLOR_BLANC);
            
            // Titre centré dans le header
            display->setTextSize(2);
            display->setTextColor(COLOR_BLACK);
            int16_t titleWidth = title.length() * 12; // Approximation pour taille 2 (6px * 2)
            int16_t titleX = (display->getWidth() - titleWidth) / 2;
            int16_t titleY = (50 - 16) / 2; // (hauteur header - hauteur texte) / 2
            display->setCursor(titleX, titleY);
            display->print(title);

            // Bouton retour
            if (callback != nullptr) {
                TextZone* backText = new TextZone(nextButtonId, 0, 0, "X", COLOR_BLANC, true);
                ButtonZone backButton(
                    nextButtonId++,
                    10, 10, 80, 30,
                    COLOR_RED,
                    true,
                    backText,
                    nullptr,
                    callback,
                    context
                );
                createButton(backButton);
            }
            break;
        }
            
        case INFO:
            // Fond pour page d'information
            display->fillScreen(COLOR_BLANC);
            
            // Bordure turquoise
            display->drawRect(5, 5, display->getWidth() - 10, display->getHeight() - 10, 
                            COLOR_TURQUOISE);
            display->drawRect(6, 6, display->getWidth() - 12, display->getHeight() - 12, 
                            COLOR_TURQUOISE);
            break;
            
        case CONFIRMATION:
            // Fond pour page de confirmation
            display->fillScreen(COLOR_BLANC_CASER);
            
            // Icône de confirmation (checkmark)
            display->fillCircle(display->getWidth() / 2, 80, 40, COLOR_GREEN);
            display->setTextSize(4);
            display->setTextColor(COLOR_BLANC);
            display->setCursor(display->getWidth() / 2 - 15, 60);
            display->print("✓");
            break;
    }
    
    display->flush();
}
