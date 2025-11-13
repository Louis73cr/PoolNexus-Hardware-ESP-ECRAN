/**
 * @file interface-utils-buttons.cpp
 * @brief Implémentation des fonctions de gestion des boutons
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#include "interface-utils.hpp"

/**
 * @brief Crée et dessine un bouton avec toutes ses propriétés
 */
void interfaceUtils::createButton(ButtonZone button) {
    // Permet de créer des boutons sans contenu texte/image
    // (utile pour les boutons avec dessin personnalisé d'icônes)
    buttonZones.push_back(button);
    
    // Ne dessine que si le bouton a du contenu
    if (button.textContent != nullptr || button.imageContent != nullptr) {
        drawButton(button.id);
    }
}

/**
 * @brief Dessine un bouton existant par son ID
 */
bool interfaceUtils::drawButton(int id) {
    for (const auto& btn : buttonZones) {
        if (btn.id == id) {
            // Dessiner le rectangle du bouton avec coins arrondis
            uint16_t finalBgColor = btn.isActive ? btn.bgColor : COLOR_GREY_LOW;
            display->fillRoundRect(btn.x, btn.y, btn.width, btn.height, BORDER_RADIUS, finalBgColor);
            display->drawRoundRect(btn.x, btn.y, btn.width, btn.height, BORDER_RADIUS, COLOR_BLACK);

            // Dessiner le contenu texte si présent et affiché
            if (btn.textContent != nullptr && btn.textContent->isDisplayed) {
                // Calcul plus précis du centrage
                // Chaque caractère fait environ 6 pixels de large pour la taille 1
                // La hauteur de la police est environ 8 pixels pour la taille 1
                display->setTextSize(1);
                int16_t charWidth = 6;
                int16_t charHeight = 8;
                int16_t textWidth = btn.textContent->text.length() * charWidth;
                int16_t textHeight = charHeight;
                
                // Centrage horizontal et vertical parfait
                int16_t textX = btn.x + (btn.width - textWidth) / 2;
                int16_t textY = btn.y + (btn.height - textHeight) / 2;

                display->setCursor(textX, textY);
                display->setTextColor(btn.textContent->textColor);
                display->print(btn.textContent->text.c_str());
            }
            
            // Dessiner l'image si présente et affichée
            if (btn.imageContent != nullptr && btn.imageContent->isDisplayed) {
                // TODO: Implémenter le dessin d'image
                // int16_t imgX = btn.x + (btn.width - btn.imageContent->width) / 2;
                // int16_t imgY = btn.y + (btn.height - btn.imageContent->height) / 2;
                // display->drawBitmap(imgX, imgY, btn.imageContent->imageData, 
                //                     btn.imageContent->width, btn.imageContent->height, COLOR_WHITE);
            }
            
            return true;
        }
    }
    return false;
}

/**
 * @brief Redessine tous les boutons
 */
void interfaceUtils::drawAllButtons() {
    for (const auto& btn : buttonZones) {
        drawButton(btn.id);
    }
}

/**
 * @brief Modifie le texte d'un bouton et le redessine
 */
bool interfaceUtils::setButtonText(int id, const char* newText) {
    for (auto& btn : buttonZones) {
        if (btn.id == id && btn.textContent != nullptr) {
            btn.textContent->text = newText;
            drawButton(id);
            return true;
        }
    }
    return false;
}

/**
 * @brief Modifie l'état actif d'un bouton et le redessine
 */
bool interfaceUtils::setButtonActive(int id, bool active) {
    for (auto& btn : buttonZones) {
        if (btn.id == id) {
            btn.isActive = active;
            drawButton(id);
            return true;
        }
    }
    return false;
}

/**
 * @brief Modifie la couleur de fond d'un bouton et le redessine
 */
bool interfaceUtils::setButtonColor(int id, uint16_t bgColor) {
    for (auto& btn : buttonZones) {
        if (btn.id == id) {
            btn.bgColor = bgColor;
            drawButton(id);
            return true;
        }
    }
    return false;
}

/**
 * @brief Vérifie quel bouton a été touché
 */
int interfaceUtils::getTouchedButton(int16_t touchX, int16_t touchY) {
    for (const auto& btn : buttonZones) {
        if (btn.contains(touchX, touchY)) {
            return btn.id;
        }
    }
    return -1;
}

/**
 * @brief Exécute le callback du bouton spécifié par son ID
 */
bool interfaceUtils::executeButtonCallback(int buttonId) {
    for (const auto& btn : buttonZones) {
        if (btn.id == buttonId) {
            return btn.execute();
        }
    }
    return false;
}

/**
 * @brief Réinitialise toutes les zones tactiles
 */
void interfaceUtils::clearButtons() {
    buttonZones.clear();
    nextButtonId = 0;
}
