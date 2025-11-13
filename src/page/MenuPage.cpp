/*
 * MenuPage.cpp - Implémentation de la page menu
 */

#include "MenuPage.hpp"

MenuPage::MenuPage(Display* display, TouchScreen* touch)
    : Page(display, touch)
{
}

void MenuPage::draw() {
    // Fond vert foncé
    display->fillScreen(0x0320); // Vert foncé RGB565
    
    // Bouton retour
    drawButton(btnBackX, btnBackY, btnBackW, btnBackH,
               "RETOUR", Display::COLOR_RED, Display::COLOR_WHITE);
    
    // Titre
    display->setTextSize(3);
    display->setTextColor(Display::COLOR_WHITE);
    display->setCursor(180, 20);
    display->print("MENU");
    
    // Options
    drawButton(optionX, optionStartY, optionW, optionH,
               "Option 1", Display::COLOR_CYAN, Display::COLOR_BLACK);
               
    drawButton(optionX, optionStartY + optionSpacing, optionW, optionH,
               "Option 2", Display::COLOR_CYAN, Display::COLOR_BLACK);
               
    drawButton(optionX, optionStartY + optionSpacing * 2, optionW, optionH,
               "Parametres", Display::COLOR_YELLOW, Display::COLOR_BLACK);
}

int MenuPage::handleTouch(uint16_t x, uint16_t y) {
    Serial.printf("MenuPage: Touch at %d, %d\n", x, y);
    
    // Bouton retour
    if (isTouchInRect(x, y, btnBackX, btnBackY, btnBackW, btnBackH)) {
        Serial.println("Retour vers HOME");
        return PAGE_HOME;
    }
    
    // Option 1
    if (isTouchInRect(x, y, optionX, optionStartY, optionW, optionH)) {
        Serial.println("Option 1 selectionnee");
        // Ici tu peux faire une action ou changer de page
    }
    
    // Option 2
    if (isTouchInRect(x, y, optionX, optionStartY + optionSpacing, optionW, optionH)) {
        Serial.println("Option 2 selectionnee");
    }
    
    // Paramètres
    if (isTouchInRect(x, y, optionX, optionStartY + optionSpacing * 2, optionW, optionH)) {
        Serial.println("Vers SETTINGS");
        return PAGE_SETTINGS;
    }
    
    return -1;
}

bool MenuPage::isTouchInRect(uint16_t x, uint16_t y, int16_t rx, int16_t ry, int16_t rw, int16_t rh) {
    return (x >= rx && x <= (rx + rw) && y >= ry && y <= (ry + rh));
}

void MenuPage::drawButton(int16_t x, int16_t y, int16_t w, int16_t h,
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
