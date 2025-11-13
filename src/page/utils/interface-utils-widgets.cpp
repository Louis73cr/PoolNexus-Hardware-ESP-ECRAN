/**
 * @file interface-utils-widgets.cpp
 * @brief Implémentation des widgets (TextField, SwitchButton, etc.)
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#include "interface-utils.hpp"

/**
 * @brief Dessine un champ de texte
 */
void interfaceUtils::drawTextField(TextFieldZone textField) {
    if (!textField.isActive) {
        return;
    }
    
    // Fond du champ
    uint16_t bgColor = textField.isActive ? COLOR_BLANC : COLOR_GREY_LOW;
    display->fillRoundRect(textField.x, textField.y, textField.width, textField.height, 
                          BORDER_RADIUS, bgColor);
    display->drawRoundRect(textField.x, textField.y, textField.width, textField.height, 
                          BORDER_RADIUS, COLOR_GREY_HIGH);
    
    // Texte du champ
    if (textField.textContent != nullptr && textField.textContent->isDisplayed) {
        display->setCursor(textField.x + 10, textField.y + (textField.height - 8) / 2);
        
        // Affichage selon le type
        if (textField.type == TEXTFIELD_PASSWORD) {
            // Masquer avec des astérisques
            String masked = "";
            for (size_t i = 0; i < textField.textContent->text.length(); i++) {
                masked += "*";
            }
            display->setTextColor(textField.textContent->textColor);
            display->print(masked.c_str());
        } else {
            display->setTextColor(textField.textContent->textColor);
            display->print(textField.textContent->text.c_str());
        }
    }
    
    // Placeholder si vide
    else {
        display->setCursor(textField.x + 10, textField.y + (textField.height - 8) / 2);
        display->setTextColor(COLOR_GREY_HIGH);
        
        if (textField.type == TEXTFIELD_NUMBER) {
            display->print("0");
        } else if (textField.type == TEXTFIELD_PASSWORD) {
            display->print("******");
        } else {
            display->print("Entrez du texte...");
        }
    }
    
    display->flush();
}

/**
 * @brief Dessine un bouton switch (ON/OFF)
 */
void interfaceUtils::drawSwitchButton(::SwitchButton switchButton) {
    // Dessiner le fond (carte blanche arrondie)
    display->fillRoundRect(switchButton.x, switchButton.y, switchButton.width, switchButton.height, 
                          BORDER_RADIUS, COLOR_BLANC);
    display->drawRoundRect(switchButton.x, switchButton.y, switchButton.width, switchButton.height, 
                          BORDER_RADIUS, COLOR_GREY_HIGH);
    
    // Dessiner le label
    display->setTextColor(COLOR_BLACK);
    display->setTextSize(2);
    display->setCursor(switchButton.x + 10, switchButton.y + (switchButton.height - 16) / 2);
    display->print(switchButton.label.c_str());
    
    // Icône d'information si nécessaire
    if (switchButton.hasInfoIcon) {
        int16_t iconX = switchButton.x + switchButton.width - 80;
        int16_t iconY = switchButton.y + switchButton.height / 2 - 10;
        display->drawCircle(iconX, iconY + 10, 10, COLOR_BLEU);
        display->setTextColor(COLOR_BLEU);
        display->setTextSize(2);
        display->setCursor(iconX - 4, iconY + 5);
        display->print("i");
    }
    
    // Dessiner le switch toggle
    const int16_t switchWidth = 60;
    const int16_t switchHeight = 30;
    const int16_t knobSize = 24;
    int16_t switchX = switchButton.x + switchButton.width - switchWidth - 10;
    int16_t switchY = switchButton.y + (switchButton.height - switchHeight) / 2;
    
    // Fond du switch
    uint16_t bgColor = switchButton.isOn ? COLOR_GREEN : COLOR_GREY_LOW;
    display->fillRoundRect(switchX, switchY, switchWidth, switchHeight, 
                          switchHeight / 2, bgColor);
    display->drawRoundRect(switchX, switchY, switchWidth, switchHeight, 
                          switchHeight / 2, COLOR_BLACK);
    
    // Bouton mobile
    int16_t knobX = switchButton.isOn ? 
                   (switchX + switchWidth - knobSize - 3) : 
                   (switchX + 3);
    int16_t knobY = switchY + (switchHeight - knobSize) / 2;
    
    display->fillCircle(knobX + knobSize / 2, knobY + knobSize / 2, 
                       knobSize / 2, COLOR_BLANC);
    display->drawCircle(knobX + knobSize / 2, knobY + knobSize / 2, 
                       knobSize / 2, COLOR_BLACK);
    
    display->flush();
}
