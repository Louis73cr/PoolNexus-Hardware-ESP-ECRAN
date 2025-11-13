/**
 * @file CalibrationPage.cpp
 * @brief Implémentation des pages de calibration
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#include "CalibrationPage.hpp"
#include <Arduino.h>

// Couleurs
#define COLOR_BG 0xF7BE           // Gris clair fond
#define COLOR_HEADER 0x0255       // Bleu
#define COLOR_CARD 0xFFFF         // Blanc
#define COLOR_TEXT_WHITE 0xFFFF   // Blanc
#define COLOR_TEXT_BLACK 0x0000   // Noir
#define COLOR_BTN_GRAY 0x4208     // Gris foncé
#define COLOR_BTN_SELECTED 0x4208 // Gris foncé (sélectionné)
#define COLOR_BTN_BLUE 0x0255     // Bleu
#define COLOR_RED 0xF800          // Rouge
#define COLOR_GREEN 0x07E0        // Vert
#define COLOR_ORANGE 0xFD60       // Orange
#define COLOR_YELLOW 0xFFE0       // Jaune

CalibrationPage::CalibrationPage(Display* display, TouchScreen* touch, const char* type) 
    : Page(display, touch), measureType(type), nextPageId(-1) {
    utils = new interfaceUtils(display);
    
    if (measureType == "pH") {
        title = "Calibration pH";
    } else {
        title = "Calibration Redox";
    }
}

CalibrationPage::~CalibrationPage() {
    delete utils;
}

void CalibrationPage::draw() {
    display->fillScreen(COLOR_BG);
    
    utils->clearButtons();
    
    utils->drawBackground(interfaceUtils::PAGE, onCloseClick, this, title);
    

    drawValueButtons();
    drawStabilityIndicator();
    drawValidateButton();
    
    display->flush();
}

int CalibrationPage::handleTouch(uint16_t x, uint16_t y) {
    // Réinitialiser nextPageId
    nextPageId = -1;
    
    int touchedId = utils->getTouchedButton(x, y);
    
    if (touchedId >= 0) {
        // Exécuter le callback du bouton touché
        utils->executeButtonCallback(touchedId);
        delay(100);
    }
    
    // Gestion spéciale des boutons de sélection de valeur (pas de callback défini)
    for (int i = 0; i < 4; i++) {
        if (touchedId == btnValue[i]) {
            selectedValue = i;
            draw();
            return -1;  // Rester sur la page
        }
    }
    
    return nextPageId;
}

void CalibrationPage::drawHeader() {
    display->fillRect(0, 0, 480, 50, COLOR_HEADER);
    
    interfaceUtils::ButtonZone closeBtn(0, 10, 10, 30, 30, COLOR_RED, true, nullptr, nullptr, onCloseClick, this);
    utils->createButton(closeBtn);
    btnClose = 0;
    
    display->drawLine(18, 18, 32, 32, COLOR_TEXT_WHITE);
    display->drawLine(32, 18, 18, 32, COLOR_TEXT_WHITE);
    
    display->setTextColor(COLOR_TEXT_WHITE);
    display->setTextSize(2);
    int16_t titleWidth = title.length() * 12;
    int16_t titleX = (480 - titleWidth) / 2;
    display->setCursor(titleX, 17);
    display->print(title);
}

void CalibrationPage::drawValueButtons() {
    if (measureType == "pH") {
        const char* labels[] = {"pH 4", "pH 7", "pH 10", "Autre"};
        
        for (int i = 0; i < 4; i++) {
            int x = 20 + (i % 2) * 230;
            int y = 70 + (i / 2) * 60;
            uint16_t color = (selectedValue == i) ? COLOR_BTN_SELECTED : COLOR_BTN_GRAY;
            
            interfaceUtils::TextZone* text = new interfaceUtils::TextZone(i+1, 0, 0, labels[i], COLOR_TEXT_WHITE, true);
            interfaceUtils::ButtonZone btn(i+1, x, y, 210, 50, color, true, text, nullptr, onValueSelect, this);
            utils->createButton(btn);
            btnValue[i] = i+1;
        }
    } else {
        const char* labels[] = {"400 mv", "Autre"};
        
        for (int i = 0; i < 2; i++) {
            int x = 30 + i * 220;
            uint16_t color = (selectedValue == i) ? COLOR_BTN_SELECTED : COLOR_BTN_GRAY;
            
            interfaceUtils::TextZone* text = new interfaceUtils::TextZone(i+1, 0, 0, labels[i], COLOR_TEXT_WHITE, true);
            interfaceUtils::ButtonZone btn(i+1, x, 70, 200, 50, color, true, text, nullptr, onValueSelect, this);
            utils->createButton(btn);
            btnValue[i] = i+1;
        }
    }
}

void CalibrationPage::drawStabilityIndicator() {
    int16_t y = (measureType == "pH") ? 200 : 140;
    
    display->fillRoundRect(20, y, 440, 60, 5, COLOR_CARD);
    
    display->setTextColor(COLOR_TEXT_BLACK);
    display->setTextSize(2);
    display->setCursor(30, y + 20);
    display->print("Stabilite :");
    
    uint16_t stabilityColor = isStable ? COLOR_GREEN : COLOR_ORANGE;
    display->fillCircle(350, y + 30, 20, stabilityColor);
}

void CalibrationPage::drawValidateButton() {
    int16_t y = (measureType == "pH") ? 280 : 220;
    
    interfaceUtils::TextZone* text = new interfaceUtils::TextZone(10, 0, 0, "Valider", COLOR_TEXT_WHITE, true);
    interfaceUtils::ButtonZone validateBtn(10, 140, y, 200, 50, COLOR_BTN_BLUE, true, text, nullptr, onValidateClick, this);
    utils->createButton(validateBtn);
    btnValidate = 10;
}

void CalibrationPage::onCloseClick(void* context) {
    CalibrationPage* page = static_cast<CalibrationPage*>(context);
    Serial.println("Fermeture calibration - Retour à MainDisplay");
    page->nextPageId = PAGE_SETTINGS;
}

void CalibrationPage::onValueSelect(void* context) {
    // Géré dans handleTouch (sélection de valeur)
}

void CalibrationPage::onValidateClick(void* context) {
    CalibrationPage* page = static_cast<CalibrationPage*>(context);
    Serial.println("Validation calibration - Retour à MainDisplay");
    page->nextPageId = PAGE_SETTINGS;
}
