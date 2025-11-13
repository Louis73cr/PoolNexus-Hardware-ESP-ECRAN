/*
 * SettingsPage.cpp - Implémentation page paramètres
 */

#include "SettingsPage.hpp"

SettingsPage::SettingsPage(Display* display, TouchScreen* touch)
    : Page(display, touch)
{
}

void SettingsPage::draw() {
    // Fond violet
    display->fillScreen(Display::COLOR_PURPLE);
    
    // Titre
    display->setTextSize(3);
    display->setTextColor(Display::COLOR_WHITE);
    display->setCursor(120, 30);
    display->print("PARAMETRES");
    
    // Contenu exemple
    display->setTextSize(2);
    display->setCursor(50, 100);
    display->print("Luminosite: 100%");
    
    display->setCursor(50, 140);
    display->print("Son: Active");
    
    display->setCursor(50, 180);
    display->print("WiFi: Desactive");
    
    // Bouton retour
    drawButton(btnBackX, btnBackY, btnBackW, btnBackH,
               "RETOUR", Display::COLOR_ORANGE, Display::COLOR_BLACK);
}

int SettingsPage::handleTouch(uint16_t x, uint16_t y) {
    if (isTouchInRect(x, y, btnBackX, btnBackY, btnBackW, btnBackH)) {
        Serial.println("Retour vers MENU");
        return PAGE_MENU;
    }
    return -1;
}

bool SettingsPage::isTouchInRect(uint16_t x, uint16_t y, int16_t rx, int16_t ry, int16_t rw, int16_t rh) {
    return (x >= rx && x <= (rx + rw) && y >= ry && y <= (ry + rh));
}

void SettingsPage::drawButton(int16_t x, int16_t y, int16_t w, int16_t h,
                              const char* text, uint16_t bgColor, uint16_t textColor) {
    display->fillRect(x, y, w, h, bgColor);
    display->drawRect(x, y, w, h, Display::COLOR_WHITE);
    
    display->setTextSize(2);
    display->setTextColor(textColor);
    int16_t textX = x + (w - strlen(text) * 12) / 2;
    int16_t textY = y + (h - 16) / 2;
    display->setCursor(textX, textY);
    display->print(text);
}
