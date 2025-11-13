/**
 * @file SpecializedSettingsPages.cpp
 * @brief Implémentation des pages de paramètres spécialisés
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#include "SpecializedSettingsPages.hpp"
#include <Arduino.h>

// Couleurs
#define COLOR_BG 0xF7BE
#define COLOR_HEADER_BLUE 0x0255
#define COLOR_CARD 0xFFFF
#define COLOR_TEXT_WHITE 0xFFFF
#define COLOR_TEXT_BLACK 0x0000
#define COLOR_BTN_RED 0xF800
#define COLOR_BTN_GRAY 0x7BEF
#define COLOR_BTN_BLUE 0x0255
#define COLOR_BTN_SELECTED 0x0000
#define COLOR_SWITCH_ON 0x07FF
#define COLOR_SWITCH_OFF 0x7BEF

// ============== SettingsBasePage ==============

SettingsBasePage::SettingsBasePage(Display* display, TouchScreen* touch, const char* title, uint16_t color) 
    : Page(display, touch), pageTitle(title), headerColor(color), nextPageId(-1) {
    utils = new interfaceUtils(display);
}

SettingsBasePage::~SettingsBasePage() {
    delete utils;
}

void SettingsBasePage::draw() {
    display->fillScreen(COLOR_BG);
    drawHeader();
    drawContent();
    display->flush();
}

int SettingsBasePage::handleTouch(uint16_t x, uint16_t y) {
    nextPageId = -1;
    int touchedId = utils->getTouchedButton(x, y);
    
    if (touchedId >= 0) {
        utils->executeButtonCallback(touchedId);
    }
    
    // Vérifier les switches
    for (auto& sw : switches) {
        if (x >= sw.x && x <= sw.x + sw.width && y >= sw.y && y <= sw.y + sw.height) {
            sw.toggle();
            draw();
            delay(100);
            break;
        }
    }
    
    return nextPageId;
}

void SettingsBasePage::drawHeader() {
    display->fillRect(0, 0, 480, 50, headerColor);
    
    interfaceUtils::ButtonZone closeBtn(0, 10, 10, 30, 30, COLOR_BTN_RED, true, nullptr, nullptr, onCloseClick, this);
    utils->createButton(closeBtn);
    btnClose = 0;
    
    display->drawLine(18, 18, 32, 32, COLOR_TEXT_WHITE);
    display->drawLine(32, 18, 18, 32, COLOR_TEXT_WHITE);
    
    display->setTextColor(COLOR_TEXT_WHITE);
    display->setTextSize(2);
    int16_t titleWidth = pageTitle.length() * 12;
    int16_t titleX = (480 - titleWidth) / 2;
    display->setCursor(titleX, 17);
    display->print(pageTitle);
}

void SettingsBasePage::onCloseClick(void* context) {
    SettingsBasePage* page = (SettingsBasePage*)context;
    page->nextPageId = PAGE_SETTINGS;
}
void SettingsBasePage::onSwitchToggle(void* context) {}

// ============== CloudPage ==============

CloudPage::CloudPage(Display* display, TouchScreen* touch) : SettingsBasePage(display, touch, "Cloud", COLOR_HEADER_BLUE) {}

void CloudPage::drawContent() {
    // Switch Cloud
    ::SwitchButton swCloud;
    swCloud.id = 1;
    swCloud.x = 50;
    swCloud.y = 70;
    swCloud.width = 380;
    swCloud.height = 50;
    swCloud.label = "Cloud";
    swCloud.hasInfoIcon = true;
    swCloud.isOn = true;
    switches.push_back(swCloud);
    utils->drawSwitchButton(swCloud);
    
    // Switch Mise à jour
    ::SwitchButton swUpdate;
    swUpdate.id = 2;
    swUpdate.x = 50;
    swUpdate.y = 140;
    swUpdate.width = 380;
    swUpdate.height = 50;
    swUpdate.label = "Mise a jour";
    swUpdate.hasInfoIcon = true;
    swUpdate.isOn = true;
    switches.push_back(swUpdate);
    utils->drawSwitchButton(swUpdate);
}

// ============== WiFiPage ==============

WiFiPage::WiFiPage(Display* display, TouchScreen* touch) : SettingsBasePage(display, touch, "WiFi", COLOR_HEADER_BLUE) {}

void WiFiPage::drawContent() {
    // Afficher dialogue de confirmation
    display->fillRoundRect(25, 60, 430, 200, 10, COLOR_BTN_RED);
    
    display->setTextColor(COLOR_TEXT_WHITE);
    display->setTextSize(2);
    display->setCursor(60, 90);
    display->print("Etes-vous sure de vouloir");
    display->setCursor(60, 120);
    display->print("reinitialiser ce parametre ?");
    
    display->setTextSize(3);
    display->setCursor(200, 160);
    display->print("WiFI");
    
    // Bouton OUI (vert)
    ButtonZone btnYes;
    btnYes.id = 1;
    btnYes.x = 105;
    btnYes.y = 210;
    btnYes.width = 110;
    btnYes.height = 40;
    btnYes.bgColor = 0x07E0;
    btnYes.isActive = true;
    interfaceUtils::TextZone* textYes = new interfaceUtils::TextZone(1, 0, 0, "OUI", COLOR_TEXT_WHITE, true);
    btnYes.textContent = textYes;
    btnYes.imageContent = nullptr;
    btnYes.onClickCallback = nullptr;
    btnYes.callbackContext = this;

    utils->createButton(btnYes);
    
    // Bouton NON (rouge)
    ButtonZone btnNo;
    btnNo.id = 2;
    btnNo.x = 265;
    btnNo.y = 210;
    btnNo.width = 110;
    btnNo.height = 40;
    btnNo.bgColor = COLOR_BTN_RED;
    btnNo.isActive = true;
    interfaceUtils::TextZone* textNo = new interfaceUtils::TextZone(2, 0, 0, "NON", COLOR_TEXT_WHITE, true);
    btnNo.textContent = textNo;
    btnNo.imageContent = nullptr;
    btnNo.onClickCallback = nullptr;
    btnNo.callbackContext = this;

    utils->createButton(btnNo);
}

// ============== MQTTPage ==============

MQTTPage::MQTTPage(Display* display, TouchScreen* touch) : SettingsBasePage(display, touch, "MQTT", COLOR_HEADER_BLUE) {}

void MQTTPage::drawContent() {
    drawTabs();
    
    if (currentTab == 0) {
        // Onglet Activation
        ::SwitchButton swMQTT;
        swMQTT.id = 1;
        swMQTT.x = 50;
        swMQTT.y = 130;
        swMQTT.width = 380;
        swMQTT.height = 50;
        swMQTT.label = "Activer la communications MQTT";
        swMQTT.hasInfoIcon = true;
        swMQTT.isOn = true;
        switches.push_back(swMQTT);
        utils->drawSwitchButton(swMQTT);
    } else if (currentTab == 1) {
        // Onglet Paramètre - Afficher les champs
        int16_t y = 130;
        const char* labels[] = {"Server address :", "Server port :", "Identifiant :", "Mot de passe :"};
        const char* values[] = {"192.168.128.147", "1883", "mqtt_user", "********"};
        
        for (int i = 0; i < 4; i++) {
            display->fillRoundRect(50, y, 380, 40, 5, COLOR_CARD);
            display->setTextColor(COLOR_TEXT_BLACK);
            display->setTextSize(2);
            display->setCursor(60, y + 12);
            display->print(labels[i]);
            
            display->fillRect(260, y + 5, 160, 30, COLOR_BTN_GRAY);
            display->setCursor(270, y + 12);
            display->print(values[i]);
            
            y += 50;
        }
    } else {
        // Onglet Test
        ButtonZone btnTest;
        btnTest.id = 10;
        btnTest.x = 140;
        btnTest.y = 130;
        btnTest.width = 200;
        btnTest.height = 50;
        btnTest.bgColor = 0x07E0;
        btnTest.isActive = true;
        interfaceUtils::TextZone* text = new interfaceUtils::TextZone(10, 0, 0, "Tester la connexion", COLOR_TEXT_WHITE, true);
        btnTest.textContent = text;
        btnTest.imageContent = nullptr;
        btnTest.onClickCallback = nullptr;
        btnTest.callbackContext = this;

        utils->createButton(btnTest);
        
        // Résultat du test
        display->setTextColor(0x07E0);
        display->setTextSize(2);
        display->setCursor(100, 220);
        display->print("Connexion etablie");
        display->setCursor(140, 245);
        display->print("avec succes");
    }
}

void MQTTPage::drawTabs() {
    const char* tabs[] = {"Activation", "Parametre", "Test"};
    
    for (int i = 0; i < 3; i++) {
        ButtonZone btnTab;
        btnTab.id = 20 + i;
        btnTab.x = 20 + i * 150;
        btnTab.y = 60;
        btnTab.width = 140;
        btnTab.height = 50;
        btnTab.bgColor = (currentTab == i) ? COLOR_BTN_SELECTED : COLOR_BTN_GRAY;
        btnTab.isActive = true;
        interfaceUtils::TextZone* text = new interfaceUtils::TextZone(i+3, 0, 0, tabs[i], COLOR_TEXT_WHITE, true);
        btnTab.textContent = text;
        btnTab.imageContent = nullptr;
        btnTab.onClickCallback = onTabClick;
        btnTab.callbackContext = this;

        utils->createButton(btnTab);
    }
}

void MQTTPage::onTabClick(void* context) {
    MQTTPage* page = static_cast<MQTTPage*>(context);
    page->nextPageId = -1; // Rester sur la même page
}

int MQTTPage::handleTouch(uint16_t x, uint16_t y) {
    nextPageId = -1;
    int touchedId = utils->getTouchedButton(x, y);
    
    if (touchedId >= 0) {
        utils->executeButtonCallback(touchedId);
        
        // Gérer les onglets (IDs 20, 21, 22)
        if (touchedId >= 20 && touchedId <= 22) {
            currentTab = touchedId - 20;
            draw();
            delay(100);
        }
    }
    
    // Vérifier les switches
    for (auto& sw : switches) {
        if (x >= sw.x && x <= sw.x + sw.width && y >= sw.y && y <= sw.y + sw.height) {
            sw.toggle();
            draw();
            delay(100);
            break;
        }
    }
    
    return nextPageId;
}

// ============== PumpPage ==============

PumpPage::PumpPage(Display* display, TouchScreen* touch) : SettingsBasePage(display, touch, "Pompe", COLOR_HEADER_BLUE) {}

void PumpPage::drawContent() {
    // Mode intelligent
    ::SwitchButton swMode;
    swMode.id = 1;
    swMode.x = 50;
    swMode.y = 70;
    swMode.width = 380;
    swMode.height = 50;
    swMode.label = "Mode inteligent";
    swMode.hasInfoIcon = true;
    swMode.isOn = true;
    switches.push_back(swMode);
    utils->drawSwitchButton(swMode);
    
    // Plage de fonctionnement
    display->setTextColor(COLOR_TEXT_BLACK);
    display->setTextSize(2);
    display->setCursor(50, 140);
    display->print("Plage de fonctionnement :");
    
    // 2 lignes avec boutons
    int16_t y = 170;
    for (int row = 0; row < 2; row++) {
        display->setCursor(80, y + 12);
        display->print("de");
        
        // Boutons pour les heures/minutes
        for (int col = 0; col < 4; col++) {
            int16_t x = 130 + col * 60 + (col >= 2 ? 30 : 0);
            display->fillRect(x, y + 5, 40, 30, COLOR_BTN_GRAY);
            display->setCursor(x + 10, y + 12);
            if (col == 0 || col == 2) display->print("10");
            else display->print("30");
        }
        
        display->setCursor(230, y + 12);
        display->print("a");
        
        // Bouton moins (rouge)
        display->fillRect(360, y + 5, 30, 30, COLOR_BTN_RED);
        display->setTextColor(COLOR_TEXT_WHITE);
        display->setCursor(367, y + 8);
        display->print("-");
        display->setTextColor(COLOR_TEXT_BLACK);
        
        y += 50;
    }
    
    // Bouton plus (vert)
    display->fillRect(220, y + 10, 40, 40, 0x07E0);
    display->setTextColor(COLOR_TEXT_WHITE);
    display->setTextSize(3);
    display->setCursor(228, y + 15);
    display->print("+");
}

// ============== SwitchPage ==============

SwitchPage::SwitchPage(Display* display, TouchScreen* touch) : SettingsBasePage(display, touch, "Interrupteurs", COLOR_HEADER_BLUE) {}

void SwitchPage::drawContent() {
    int16_t y = 70;
    for (int i = 1; i <= 4; i++) {
        ::SwitchButton sw;
        sw.id = i;
        sw.x = 50;
        sw.y = y;
        sw.width = 380;
        sw.height = 50;
        sw.label = "Interrupteur " + String(i);
        sw.hasInfoIcon = false;
        sw.isOn = true;
        switches.push_back(sw);
        utils->drawSwitchButton(sw);
        y += 60;
    }
}

// ============== LevelProbePage ==============

LevelProbePage::LevelProbePage(Display* display, TouchScreen* touch) : SettingsBasePage(display, touch, "Sonde niveaux produits", COLOR_HEADER_BLUE) {}

void LevelProbePage::drawContent() {
    display->setTextColor(COLOR_TEXT_BLACK);
    display->setTextSize(2);
    display->setCursor(50, 80);
    display->print("Activations des sondes de niveaux :");
    
    // pH
    ::SwitchButton swPH;
    swPH.id = 1;
    swPH.x = 50;
    swPH.y = 120;
    swPH.width = 380;
    swPH.height = 50;
    swPH.label = "pH";
    swPH.hasInfoIcon = false;
    swPH.isOn = true;
    switches.push_back(swPH);
    utils->drawSwitchButton(swPH);
    
    // Chlore
    ::SwitchButton swChlore;
    swChlore.id = 2;
    swChlore.x = 50;
    swChlore.y = 190;
    swChlore.width = 380;
    swChlore.height = 50;
    swChlore.label = "Chlore";
    swChlore.hasInfoIcon = false;
    swChlore.isOn = true;
    switches.push_back(swChlore);
    utils->drawSwitchButton(swChlore);
}

// ============== PoolFillPage ==============

PoolFillPage::PoolFillPage(Display* display, TouchScreen* touch) : SettingsBasePage(display, touch, "Remplissage piscine", COLOR_HEADER_BLUE) {}

void PoolFillPage::drawContent() {
    ::SwitchButton sw;
    sw.id = 1;
    sw.x = 50;
    sw.y = 70;
    sw.width = 380;
    sw.height = 50;
    sw.label = "Remplissage automatique";
    sw.hasInfoIcon = false;
    sw.isOn = true;
    switches.push_back(sw);
    utils->drawSwitchButton(sw);
}

// ============== LockPage ==============

LockPage::LockPage(Display* display, TouchScreen* touch) : SettingsBasePage(display, touch, "Verrouillage", COLOR_HEADER_BLUE) {}

void LockPage::drawContent() {
    // Code
    display->fillRoundRect(50, 70, 380, 50, 5, COLOR_CARD);
    display->setTextColor(COLOR_TEXT_BLACK);
    display->setTextSize(2);
    display->setCursor(60, 87);
    display->print("Code");
    
    display->fillRect(260, 80, 160, 30, COLOR_BTN_GRAY);
    display->setCursor(300, 87);
    display->print("****");
    
    // Verrouillage actif
    ::SwitchButton sw;
    sw.id = 1;
    sw.x = 50;
    sw.y = 140;
    sw.width = 380;
    sw.height = 50;
    sw.label = "Verrouillage actif";
    sw.hasInfoIcon = true;
    sw.isOn = true;
    switches.push_back(sw);
    utils->drawSwitchButton(sw);
}

// ============== ScreenPage ==============

ScreenPage::ScreenPage(Display* display, TouchScreen* touch) : SettingsBasePage(display, touch, "Ecran", COLOR_HEADER_BLUE) {}

void ScreenPage::drawContent() {
    // Veille automatique
    ::SwitchButton sw;
    sw.id = 1;
    sw.x = 50;
    sw.y = 70;
    sw.width = 380;
    sw.height = 50;
    sw.label = "Veille automatique";
    sw.hasInfoIcon = true;
    sw.isOn = true;
    switches.push_back(sw);
    utils->drawSwitchButton(sw);
    
    // Luminosité
    display->setTextColor(COLOR_TEXT_BLACK);
    display->setTextSize(2);
    display->setCursor(50, 150);
    display->print("Luminosite :");
    
    // Boutons - 15 +
    ButtonZone btnMinus;
    btnMinus.id = 10;
    btnMinus.x = 150;
    btnMinus.y = 190;
    btnMinus.width = 60;
    btnMinus.height = 50;
    btnMinus.bgColor = COLOR_BTN_RED;
    btnMinus.isActive = true;
    interfaceUtils::TextZone* textMinus = new interfaceUtils::TextZone(10, 0, 0, "-", COLOR_TEXT_WHITE, true);
    btnMinus.textContent = textMinus;
    btnMinus.imageContent = nullptr;
    btnMinus.onClickCallback = nullptr;
    btnMinus.callbackContext = this;

    utils->createButton(btnMinus);
    
    display->fillRect(220, 195, 60, 40, COLOR_BTN_GRAY);
    display->setTextColor(COLOR_TEXT_BLACK);
    display->setCursor(235, 207);
    display->print("15");
    
    ButtonZone btnPlus;
    btnPlus.id = 11;
    btnPlus.x = 290;
    btnPlus.y = 190;
    btnPlus.width = 60;
    btnPlus.height = 50;
    btnPlus.bgColor = 0x07E0;
    btnPlus.isActive = true;
    interfaceUtils::TextZone* textPlus = new interfaceUtils::TextZone(11, 0, 0, "+", COLOR_TEXT_WHITE, true);
    btnPlus.textContent = textPlus;
    btnPlus.imageContent = nullptr;
    btnPlus.onClickCallback = nullptr;
    btnPlus.callbackContext = this;

    utils->createButton(btnPlus);
}

// ============== LanguagePage ==============

LanguagePage::LanguagePage(Display* display, TouchScreen* touch) : SettingsBasePage(display, touch, "Langue", COLOR_HEADER_BLUE) {}

void LanguagePage::drawContent() {
    const char* languages[] = {"English", "Francais", "Espanol", "Italiano"};
    
    int16_t y = 70;
    for (int i = 0; i < 4; i++) {
        display->fillRoundRect(50, y, 380, 50, 5, COLOR_CARD);
        
        display->setTextColor(COLOR_TEXT_BLACK);
        display->setTextSize(2);
        display->setCursor(150, y + 17);
        display->print(languages[i]);
        
        // Icône de sélection (X noir si sélectionné)
        if (selectedLanguage == i) {
            int16_t xPos = 370;
            int16_t yPos = y + 15;
            display->drawLine(xPos, yPos, xPos + 20, yPos + 20, COLOR_TEXT_BLACK);
            display->drawLine(xPos + 20, yPos, xPos, yPos + 20, COLOR_TEXT_BLACK);
            display->drawLine(xPos + 1, yPos, xPos + 21, yPos + 20, COLOR_TEXT_BLACK);
            display->drawLine(xPos + 21, yPos, xPos + 1, yPos + 20, COLOR_TEXT_BLACK);
        } else {
            display->fillRect(375, y + 15, 20, 20, COLOR_BTN_GRAY);
        }
        
        y += 60;
    }
}

void LanguagePage::onLanguageSelect(void* context) {
    LanguagePage* page = static_cast<LanguagePage*>(context);
    page->nextPageId = -1; // Rester sur la même page
}

int LanguagePage::handleTouch(uint16_t x, uint16_t y) {
    nextPageId = -1;
    int touchedId = utils->getTouchedButton(x, y);
    
    if (touchedId >= 0) {
        utils->executeButtonCallback(touchedId);
    }
    
    // Gérer la sélection de langue
    if (x >= 50 && x <= 430) {
        if (y >= 70 && y < 120) {
            selectedLanguage = 0;
            draw();
            delay(100);
        } else if (y >= 130 && y < 180) {
            selectedLanguage = 1;
            draw();
            delay(100);
        } else if (y >= 190 && y < 240) {
            selectedLanguage = 2;
            draw();
            delay(100);
        } else if (y >= 250 && y < 300) {
            selectedLanguage = 3;
            draw();
            delay(100);
        }
    }
    
    return nextPageId;
}

// ============== ResetPage ==============

ResetPage::ResetPage(Display* display, TouchScreen* touch) : SettingsBasePage(display, touch, "Reinitialisation", COLOR_HEADER_BLUE) {}

void ResetPage::drawContent() {
    const char* labels[] = {"WiFi", "Parametre", "Appareil"};
    
    int16_t y = 70;
    for (int i = 0; i < 3; i++) {
        display->fillRoundRect(50, y, 200, 50, 5, COLOR_CARD);
        display->setTextColor(COLOR_TEXT_BLACK);
        display->setTextSize(2);
        display->setCursor(80, y + 17);
        display->print(labels[i]);
        
        ButtonZone btnReset;
        btnReset.id = i + 1;
        btnReset.x = 270;
        btnReset.y = y;
        btnReset.width = 160;
        btnReset.height = 50;
        btnReset.bgColor = COLOR_BTN_RED;
        btnReset.isActive = true;
        interfaceUtils::TextZone* text = new interfaceUtils::TextZone(i+1, 0, 0, "Reinitialiser", COLOR_TEXT_WHITE, true);
        btnReset.textContent = text;
        btnReset.imageContent = nullptr;
        btnReset.onClickCallback = nullptr;
        btnReset.callbackContext = this;

        utils->createButton(btnReset);
        
        y += 70;
    }
}

void ResetPage::onResetWiFi(void* context) {}
void ResetPage::onResetSettings(void* context) {}
void ResetPage::onResetDevice(void* context) {}
