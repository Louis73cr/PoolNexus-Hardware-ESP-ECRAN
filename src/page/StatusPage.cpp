/*
 * StatusPage.cpp - Implémentation page de statut
 */

#include "StatusPage.hpp"

StatusPage::StatusPage(Display* display, TouchScreen* touch)
    : Page(display, touch)
    , lastUpdate(0)
    , updateCounter(0)
{
}

void StatusPage::draw() {
    // Fond noir
    display->fillScreen(Display::COLOR_BLACK);
    
    // Titre
    display->setTextSize(3);
    display->setTextColor(Display::COLOR_CYAN);
    display->setCursor(160, 20);
    display->print("STATUS");
    
    // Informations système
    display->setTextSize(2);
    display->setTextColor(Display::COLOR_WHITE);
    
    display->setCursor(20, 70);
    display->print("RAM Libre:");
    display->setCursor(250, 70);
    display->print(ESP.getFreeHeap() / 1024);
    display->print(" KB");
    
    display->setCursor(20, 100);
    display->print("PSRAM:");
    display->setCursor(250, 100);
    display->print(ESP.getPsramSize() / 1024);
    display->print(" KB");
    
    display->setCursor(20, 130);
    display->print("CPU Freq:");
    display->setCursor(250, 130);
    display->print(ESP.getCpuFreqMHz());
    display->print(" MHz");
    
    display->setCursor(20, 160);
    display->print("Uptime:");
    display->setCursor(250, 160);
    display->print(millis() / 1000);
    display->print(" s");
    
    display->setCursor(20, 190);
    display->print("Updates:");
    display->setCursor(250, 190);
    display->print(updateCounter);
    
    // Bouton retour
    drawButton(btnBackX, btnBackY, btnBackW, btnBackH,
               "RETOUR", Display::COLOR_RED, Display::COLOR_WHITE);
}

int StatusPage::handleTouch(uint16_t x, uint16_t y) {
    if (isTouchInRect(x, y, btnBackX, btnBackY, btnBackW, btnBackH)) {
        Serial.println("Retour vers HOME");
        return PAGE_HOME;
    }
    return -1;
}

void StatusPage::update() {
    // Met à jour l'affichage toutes les secondes
    if (millis() - lastUpdate > 1000) {
        lastUpdate = millis();
        updateCounter++;
        
        // Force le redessin
        setNeedsRedraw();
    }
}

void StatusPage::onEnter() {
    Page::onEnter();
    lastUpdate = millis();
    updateCounter = 0;
    Serial.println("Entree sur StatusPage");
}

bool StatusPage::isTouchInRect(uint16_t x, uint16_t y, int16_t rx, int16_t ry, int16_t rw, int16_t rh) {
    return (x >= rx && x <= (rx + rw) && y >= ry && y <= (ry + rh));
}

void StatusPage::drawButton(int16_t x, int16_t y, int16_t w, int16_t h,
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
