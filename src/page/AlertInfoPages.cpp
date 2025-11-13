/**
 * @file AlertInfoPages.cpp
 * @brief Implémentation des pages Alert et Info
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#include "AlertInfoPages.hpp"
#include <Arduino.h>

// Couleurs
#define COLOR_BG 0xF7BE           // Gris clair fond
#define COLOR_HEADER_RED 0xF800   // Rouge pour alertes
#define COLOR_HEADER_BLUE 0x0255  // Bleu pour infos
#define COLOR_CARD 0xFFFF         // Blanc
#define COLOR_TEXT_WHITE 0xFFFF   // Blanc
#define COLOR_TEXT_BLACK 0x0000   // Noir
#define COLOR_BTN_RED 0xF800      // Rouge
#define COLOR_BTN_GRAY 0x7BEF     // Gris
#define COLOR_BTN_BLUE 0x0255     // Bleu
#define COLOR_ALERT_BG 0x4208     // Gris foncé

// ============== AlertPage ==============

AlertPage::AlertPage(Display* display, TouchScreen* touch) 
    : Page(display, touch), nextPageId(-1) {
    utils = new interfaceUtils(display);
    alerts.push_back("Niveaux bas");
    alerts.push_back("Nivaux de liquide dans le bidon de chlore bas, regulations de chlore stoppe");
}

AlertPage::~AlertPage() {
    delete utils;
}

void AlertPage::draw() {
    display->fillScreen(COLOR_BG);
    
    drawHeader();
    drawAlertContent();
    drawNavigation();
    
    display->flush();
}

int AlertPage::handleTouch(uint16_t x, uint16_t y) {
    // Réinitialiser nextPageId
    nextPageId = -1;
    
    int touchedId = utils->getTouchedButton(x, y);
    
    if (touchedId >= 0) {
        // Exécuter le callback du bouton touché
        utils->executeButtonCallback(touchedId);
        delay(100);
    }
    
    // Gestion spéciale des boutons sans callback
    if (touchedId == btnDelete) {
        if (alerts.size() > 0 && currentAlertIndex < alerts.size()) {
            if (currentAlertIndex > 0) {
                alerts.erase(alerts.begin() + currentAlertIndex);
                if (currentAlertIndex >= alerts.size()) {
                    currentAlertIndex = alerts.size() - 1;
                }
                draw();
            }
        }
        return -1;
    }
    
    if (touchedId == btnPrevious && currentAlertIndex > 0) {
        currentAlertIndex--;
        draw();
        return -1;
    }
    
    if (touchedId == btnNext && currentAlertIndex < alerts.size() - 1) {
        currentAlertIndex++;
        draw();
        return -1;
    }
    
    return nextPageId;
}

void AlertPage::drawHeader() {
    display->fillRect(0, 0, 480, 50, COLOR_HEADER_RED);
    
    interfaceUtils::ButtonZone closeBtn(0, 10, 10, 30, 30, COLOR_HEADER_RED, true, nullptr, nullptr, onCloseClick, this);
    utils->createButton(closeBtn);
    btnClose = 0;
    
    display->drawLine(18, 18, 32, 32, COLOR_TEXT_WHITE);
    display->drawLine(32, 18, 18, 32, COLOR_TEXT_WHITE);
    
    display->setTextColor(COLOR_TEXT_WHITE);
    display->setTextSize(2);
    String title = "Alerte";
    int16_t titleWidth = title.length() * 12;
    int16_t titleX = (480 - titleWidth) / 2;
    display->setCursor(titleX, 17);
    display->print(title);
}

void AlertPage::drawAlertContent() {
    if (alerts.size() == 0) return;
    
    display->fillRoundRect(40, 60, 400, 60, 5, COLOR_ALERT_BG);
    
    display->fillCircle(80, 90, 15, COLOR_BTN_RED);
    
    display->setTextColor(COLOR_TEXT_WHITE);
    display->setTextSize(2);
    display->setCursor(110, 75);
    display->print(alerts[currentAlertIndex]);
    
    interfaceUtils::ButtonZone deleteBtn(1, 385, 70, 40, 40, COLOR_ALERT_BG, true, nullptr, nullptr, onDeleteClick, this);
    utils->createButton(deleteBtn);
    btnDelete = 1;
    
    display->fillRect(397, 80, 16, 20, COLOR_BTN_RED);
    display->fillRect(395, 78, 20, 3, COLOR_BTN_RED);
    
    if (currentAlertIndex + 1 < alerts.size() && alerts[0] == "Niveaux bas") {
        display->fillRoundRect(40, 140, 400, 100, 5, COLOR_CARD);
        display->setTextColor(COLOR_TEXT_BLACK);
        display->setTextSize(2);
        display->setCursor(50, 150);
        display->print("Nivaux de liquide dans le");
        display->setCursor(50, 175);
        display->print("bidon de chlore bas,");
        display->setCursor(50, 200);
        display->print("regulations de chlore");
        display->setCursor(50, 225);
        display->print("stoppe");
    }
}

void AlertPage::drawNavigation() {
    if (alerts.size() <= 1) return;
    
    bool prevActive = (currentAlertIndex > 0);
    interfaceUtils::ButtonZone prevBtn(2, 50, 260, 150, 50, COLOR_BTN_GRAY, prevActive, nullptr, nullptr, onPreviousClick, this);
    utils->createButton(prevBtn);
    btnPrevious = 2;
    
    if (prevActive) {
        display->fillTriangle(150, 275, 150, 295, 120, 285, COLOR_TEXT_BLACK);
    }
    
    bool nextActive = (currentAlertIndex < alerts.size() - 1);
    interfaceUtils::ButtonZone nextBtn(3, 280, 260, 150, 50, COLOR_BTN_BLUE, nextActive, nullptr, nullptr, onNextClick, this);
    utils->createButton(nextBtn);
    btnNext = 3;
    
    if (nextActive) {
        display->fillTriangle(330, 275, 330, 295, 360, 285, COLOR_TEXT_WHITE);
    }
}

void AlertPage::addAlert(String alert) {
    alerts.push_back(alert);
}

void AlertPage::onCloseClick(void* context) {
    AlertPage* page = static_cast<AlertPage*>(context);
    Serial.println("Fermeture AlertPage - Retour à MainDisplay");
    page->nextPageId = PAGE_MAIN_DISPLAY;
}

void AlertPage::onDeleteClick(void* context) {
    // Handled in handleTouch
}

void AlertPage::onPreviousClick(void* context) {
    // Handled in handleTouch
}

void AlertPage::onNextClick(void* context) {
    // Handled in handleTouch
}

// ============== InfoPage ==============

InfoPage::InfoPage(Display* display, TouchScreen* touch) 
    : Page(display, touch), nextPageId(-1) {
    utils = new interfaceUtils(display);
    infoTitle = "Informations";
    infoContent = "L'activation des sondes de niveaux, provoque l'arret de la regulation en cas de manque de produit.";
}

InfoPage::~InfoPage() {
    delete utils;
}

void InfoPage::draw() {
    display->fillScreen(COLOR_BG);
    
    drawHeader();
    drawContent();
    
    display->flush();
}

int InfoPage::handleTouch(uint16_t x, uint16_t y) {
    // Réinitialiser nextPageId
    nextPageId = -1;
    
    int touchedId = utils->getTouchedButton(x, y);
    
    if (touchedId >= 0) {
        // Exécuter le callback du bouton touché
        utils->executeButtonCallback(touchedId);
        delay(100);
    }
    
    return nextPageId;
}

void InfoPage::drawHeader() {
    display->fillRect(0, 0, 480, 50, COLOR_HEADER_BLUE);
    
    interfaceUtils::ButtonZone closeBtn(0, 10, 10, 30, 30, COLOR_HEADER_BLUE, true, nullptr, nullptr, onCloseClick, this);
    utils->createButton(closeBtn);
    btnClose = 0;
    
    display->drawLine(18, 18, 32, 32, COLOR_TEXT_WHITE);
    display->drawLine(32, 18, 18, 32, COLOR_TEXT_WHITE);
    
    display->setTextColor(COLOR_TEXT_WHITE);
    display->setTextSize(2);
    int16_t titleWidth = infoTitle.length() * 12 + 30;
    int16_t titleX = (480 - titleWidth) / 2;
    
    display->fillCircle(titleX + 15, 25, 15, 0x0010);
    display->setTextSize(3);
    display->setCursor(titleX + 10, 13);
    display->print("i");
    
    display->setTextSize(2);
    display->setCursor(titleX + 35, 17);
    display->print(infoTitle);
}

void InfoPage::drawContent() {
    display->fillRoundRect(40, 70, 400, 180, 5, COLOR_CARD);
    
    display->setTextColor(COLOR_TEXT_BLACK);
    display->setTextSize(2);
    
    int16_t y = 90;
    int16_t lineHeight = 25;
    String line = "";
    
    for (unsigned int i = 0; i < infoContent.length(); i++) {
        char c = infoContent.charAt(i);
        line += c;
        
        if (line.length() >= 35 || c == '\n' || i == infoContent.length() - 1) {
            display->setCursor(50, y);
            display->print(line);
            y += lineHeight;
            line = "";
        }
    }
}

void InfoPage::setInfo(String title, String content) {
    infoTitle = title;
    infoContent = content;
}

void InfoPage::onCloseClick(void* context) {
    InfoPage* page = static_cast<InfoPage*>(context);
    Serial.println("Fermeture InfoPage - Retour à MainDisplay");
    page->nextPageId = PAGE_MAIN_DISPLAY;
}

