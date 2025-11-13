/**
 * @file MainDisplayPage.cpp
 * @brief Implémentation de la page d'affichage principal
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#include "MainDisplayPage.hpp"
#include <Arduino.h>

// Couleurs
#define COLOR_BG 0xF7BE           // Gris clair fond
#define COLOR_CARD 0xFFFF         // Blanc
#define COLOR_TEXT_LABEL 0x0000   // Noir
#define COLOR_ORANGE 0xFD60       // Orange
#define COLOR_GREEN 0x07E0        // Vert
#define COLOR_CYAN 0x07FF         // Cyan
#define COLOR_RED 0xF800          // Rouge
#define COLOR_BLUE 0x001F         // Bleu
#define COLOR_GRAY 0x7BEF         // Gris clair

MainDisplayPage::MainDisplayPage(Display* display, TouchScreen* touch) 
    : Page(display, touch), nextPage(-1) {
    utils = new interfaceUtils(display);
}

MainDisplayPage::~MainDisplayPage() {
    delete utils;
}

void MainDisplayPage::draw() {
    display->fillScreen(COLOR_BG);
    
    // Dessiner les 3 cartes de mesures (plus compactes)
    drawMeasurementCard(10, "pH", String(phValue, 2), "", COLOR_ORANGE, true);
    drawMeasurementCard(80, "Redox", String(redoxValue), "mv", COLOR_GREEN, true);
    drawMeasurementCard(150, "Temperature", String(tempValue, 1), "C", COLOR_CYAN, true);
    
    // Créer les boutons pour les icônes du bas
    utils->clearButtons();
    
    // Bouton Power (vert si ON, gris si OFF)
    interfaceUtils::ButtonZone powerBtn(0, 10, 245, 100, 70, isPowerOn ? COLOR_GREEN : COLOR_GRAY, true, nullptr, nullptr, onPowerClick, this);
    utils->createButton(powerBtn);
    btnPower = 0;
    Serial.printf("Button Power: id=%d, x=%d, y=%d, w=%d, h=%d\n", 0, 10, 245, 100, 70);
    
    // Dessiner icône power
    drawPowerIcon(40, 260, isPowerOn);
    
    // Bouton Pump (vert si ON, gris si OFF)
    interfaceUtils::ButtonZone pumpBtn(1, 130, 245, 100, 70, isFilterOn ? COLOR_GREEN : COLOR_GRAY, true, nullptr, nullptr, onFilterClick, this);
    utils->createButton(pumpBtn);
    btnFilter = 1;
    Serial.printf("Button Filter: id=%d, x=%d, y=%d, w=%d, h=%d\n", 1, 130, 245, 100, 70);
    
    // Dessiner icône pompe
    drawPumpIcon(160, 260);
    
    // Bouton Alert (triangle rouge)
    interfaceUtils::ButtonZone alertBtn(2, 250, 245, 100, 70, COLOR_GRAY, true, nullptr, nullptr, onAlertClick, this);
    utils->createButton(alertBtn);
    btnAlert = 2;
    Serial.printf("Button Alert: id=%d, x=%d, y=%d, w=%d, h=%d\n", 2, 250, 245, 100, 70);
    
    // Dessiner icône alerte
    drawAlertIcon(280, 260);
    
    // Bouton Settings (engrenage bleu)
    interfaceUtils::ButtonZone settingsBtn(3, 370, 245, 100, 70, COLOR_BLUE, true, nullptr, nullptr, onSettingsClick, this);
    utils->createButton(settingsBtn);
    btnSettings = 3;
    Serial.printf("Button Settings: id=%d, x=%d, y=%d, w=%d, h=%d\n", 3, 370, 245, 100, 70);
    
    // Dessiner icône engrenage
    drawSettingsIcon(400, 260);
    
    display->flush();
}

int MainDisplayPage::handleTouch(uint16_t x, uint16_t y) {
    int touchedId = utils->getTouchedButton(x, y);
    
    Serial.printf("MainDisplayPage::handleTouch - touchedId: %d (x:%d, y:%d)\n", touchedId, x, y);
    
    // Réinitialiser nextPage
    nextPage = -1;
    
    // Exécuter le callback du bouton touché
    if (touchedId >= 0) {
        utils->executeButtonCallback(touchedId);
        delay(100);
    }
    
    // Retourner la page demandée par le callback
    return nextPage;
}

void MainDisplayPage::drawMeasurementCard(int16_t y, const char* label, String value, const char* unit, uint16_t valueColor, bool hasMenuIcon) {
    // Carte blanche (hauteur réduite à 60px)
    display->fillRoundRect(10, y, 460, 60, 5, COLOR_CARD);
    
    // Label (noir, taille 2)
    display->setTextColor(COLOR_TEXT_LABEL);
    display->setTextSize(2);
    display->setCursor(20, y + 8);
    display->print(label);
    
    // Valeur (colorée, taille 3)
    display->setTextColor(valueColor);
    display->setTextSize(3);
    int16_t valueWidth = value.length() * 18;
    int16_t valueX = 200;
    display->setCursor(valueX, y + 20);
    display->print(value);
    
    // Unité si présente
    if (strlen(unit) > 0) {
        display->setTextSize(2);
        display->setCursor(valueX + valueWidth + 5, y + 28);
        display->print(unit);
    }
    
    // Icône flèche vers le haut à droite si demandé
    if (hasMenuIcon) {
        int16_t iconX = 430;
        int16_t iconY = y + 20;
        // Flèche vers le haut
        display->fillTriangle(iconX + 10, iconY, iconX + 5, iconY + 10, iconX + 15, iconY + 10, valueColor);
    }
}

void MainDisplayPage::drawPowerIcon(int16_t x, int16_t y, bool isOn) {
    uint16_t color = isOn ? COLOR_GREEN : COLOR_CARD;
    // Cercle
    display->drawCircle(x + 15, y + 15, 12, color);
    display->drawCircle(x + 15, y + 15, 11, color);
    // Trait vertical
    display->drawLine(x + 15, y + 5, x + 15, y + 15, color);
    display->drawLine(x + 16, y + 5, x + 16, y + 15, color);
}

void MainDisplayPage::drawPumpIcon(int16_t x, int16_t y) {
    // Pompe simplifiée (rectangle avec hélice)
    display->fillRect(x + 5, y + 10, 20, 15, COLOR_CARD);
    display->drawRect(x + 5, y + 10, 20, 15, COLOR_TEXT_LABEL);
    // Hélice
    display->fillCircle(x + 15, y + 17, 5, COLOR_CARD);
    display->drawLine(x + 12, y + 14, x + 18, y + 20, COLOR_TEXT_LABEL);
    display->drawLine(x + 18, y + 14, x + 12, y + 20, COLOR_TEXT_LABEL);
}

void MainDisplayPage::drawAlertIcon(int16_t x, int16_t y) {
    // Triangle rouge avec !
    display->drawTriangle(x + 15, y + 5, x + 5, y + 25, x + 25, y + 25, COLOR_RED);
    display->drawTriangle(x + 15, y + 6, x + 6, y + 24, x + 24, y + 24, COLOR_RED);
    display->fillTriangle(x + 15, y + 7, x + 7, y + 23, x + 23, y + 23, COLOR_RED);
    // Point d'exclamation
    display->setTextColor(COLOR_CARD);
    display->setTextSize(2);
    display->setCursor(x + 13, y + 10);
    display->print("!");
}

void MainDisplayPage::drawSettingsIcon(int16_t x, int16_t y) {
    // Engrenage simplifié
    display->fillCircle(x + 15, y + 15, 10, COLOR_CARD);
    display->drawCircle(x + 15, y + 15, 10, COLOR_CARD);
    display->fillCircle(x + 15, y + 15, 5, COLOR_CARD);
    // Dents (4 rectangles)
    display->fillRect(x + 13, y + 3, 4, 6, COLOR_CARD);
    display->fillRect(x + 13, y + 21, 4, 6, COLOR_CARD);
    display->fillRect(x + 3, y + 13, 6, 4, COLOR_CARD);
    display->fillRect(x + 21, y + 13, 6, 4, COLOR_CARD);
}

void MainDisplayPage::updatePH(float value) {
    phValue = value;
}

void MainDisplayPage::updateRedox(int value) {
    redoxValue = value;
}

void MainDisplayPage::updateTemperature(float value) {
    tempValue = value;
}

void MainDisplayPage::onPowerClick(void* context) {
    MainDisplayPage* page = static_cast<MainDisplayPage*>(context);
    page->isPowerOn = !page->isPowerOn;
    Serial.println(page->isPowerOn ? "Power ON" : "Power OFF");
    page->nextPage = -1; // Rester sur cette page
    page->draw(); // Redessiner pour voir le changement d'état
}

void MainDisplayPage::onFilterClick(void* context) {
    MainDisplayPage* page = static_cast<MainDisplayPage*>(context);
    page->isFilterOn = !page->isFilterOn;
    Serial.println(page->isFilterOn ? "Pump ON" : "Pump OFF");
    page->nextPage = -1; // Rester sur cette page
    page->draw(); // Redessiner pour voir le changement d'état
}

void MainDisplayPage::onAlertClick(void* context) {
    MainDisplayPage* page = static_cast<MainDisplayPage*>(context);
    Serial.println("Navigating to PAGE_ALERT");
    page->nextPage = PAGE_ALERT; // Naviguer vers PAGE_ALERT
}

void MainDisplayPage::onSettingsClick(void* context) {
    MainDisplayPage* page = static_cast<MainDisplayPage*>(context);
    Serial.println("Navigating to PAGE_SETTINGS");
    page->nextPage = PAGE_SETTINGS; // Naviguer vers PAGE_SETTINGS
}
