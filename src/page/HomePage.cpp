/*
 * HomePage.cpp - Implémentation de la page d'accueil
 */

#include "HomePage.hpp"

HomePage::HomePage(Display* display, TouchScreen* touch)
    : Page(display, touch)
{
}

void HomePage::draw() {
    // Fond bleu
    display->fillScreen(Display::COLOR_BLUE);
    
    // Titre
    display->setTextSize(3);
    display->setTextColor(Display::COLOR_WHITE);
    display->setCursor(120, 40);
    display->print("PAGE D'ACCUEIL");
    
    // Sous-titre
    display->setTextSize(2);
    display->setCursor(100, 90);
    display->print("ESP32-S3 - C3248W535C");
    
    // Informations système
    display->setTextSize(1);
    display->setTextColor(Display::COLOR_YELLOW);
    display->setCursor(20, 140);
    display->print("RAM libre: ");
    display->print(ESP.getFreeHeap() / 1024);
    display->print(" KB");
    
    display->setCursor(280, 140);
    display->print("PSRAM: ");
    display->print(ESP.getPsramSize() / 1024);
    display->print(" KB");
    
    // Bouton Menu
    drawButton(btnMenuX, btnMenuY, btnMenuW, btnMenuH, 
               "MENU", Display::COLOR_GREEN, Display::COLOR_BLACK);
    
    // Bouton Status
    drawButton(btnStatusX, btnStatusY, btnStatusW, btnStatusH,
               "STATUS", Display::COLOR_ORANGE, Display::COLOR_BLACK);
    
    // Instructions
    display->setTextSize(1);
    display->setTextColor(Display::COLOR_WHITE);
    display->setCursor(130, 290);
    display->print("Touchez un bouton");
}

int HomePage::handleTouch(uint16_t x, uint16_t y) {
    Serial.printf("HomePage: Touch at %d, %d\n", x, y);
    
    // Vérifie si toucher sur bouton Menu
    if (isTouchInRect(x, y, btnMenuX, btnMenuY, btnMenuW, btnMenuH)) {
        Serial.println("Bouton MENU appuye");
        return PAGE_MENU;
    }
    
    // Vérifie si toucher sur bouton Status
    if (isTouchInRect(x, y, btnStatusX, btnStatusY, btnStatusW, btnStatusH)) {
        Serial.println("Bouton STATUS appuye");
        return PAGE_STATUS;
    }
    
    // Reste sur cette page
    return -1;
}

void HomePage::update() {
    // Aucune logique de mise à jour nécessaire pour cette page
}

void HomePage::onEnter() {
    Page::onEnter();
    Serial.println("Entree sur HomePage");
}

bool HomePage::isTouchInRect(uint16_t x, uint16_t y, int16_t rx, int16_t ry, int16_t rw, int16_t rh) {
    return (x >= rx && x <= (rx + rw) && y >= ry && y <= (ry + rh));
}

void HomePage::drawButton(int16_t x, int16_t y, int16_t w, int16_t h,
                          const char* text, uint16_t bgColor, uint16_t textColor) {
    // Fond du bouton
    display->fillRect(x, y, w, h, bgColor);
    
    // Bordure
    display->drawRect(x, y, w, h, Display::COLOR_WHITE);
    display->drawRect(x+1, y+1, w-2, h-2, Display::COLOR_WHITE);
    
    // Texte centré (approximatif)
    display->setTextSize(2);
    display->setTextColor(textColor);
    int16_t textX = x + (w - strlen(text) * 12) / 2;
    int16_t textY = y + (h - 16) / 2;
    display->setCursor(textX, textY);
    display->print(text);
}
