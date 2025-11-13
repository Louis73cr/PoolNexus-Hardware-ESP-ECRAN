/**
 * @file SpecializedSettingsPages.hpp
 * @brief Pages de paramètres spécialisés
 * 
 * Inclut: Cloud, WiFi, MQTT, Pompe, Interrupteurs, Sondes de niveaux,
 * Remplissage piscine, Verrouillage, Écran, Langue, Réinitialisation
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#ifndef SPECIALIZED_SETTINGS_PAGES_HPP
#define SPECIALIZED_SETTINGS_PAGES_HPP

#include "utils/Page.hpp"
#include "utils/interface-utils.hpp"
#include <vector>

// ============== Base Class ==============

/**
 * @class SettingsBasePage
 * @brief Classe de base pour toutes les pages de paramètres
 */
class SettingsBasePage : public Page {
protected:
    interfaceUtils* utils;
    std::vector<SwitchButton> switches;
    String pageTitle;
    uint16_t headerColor;
    
    // Button IDs
    int btnClose;
    
    // Navigation
    int nextPageId;
    
    static void onCloseClick(void* context);
    static void onSwitchToggle(void* context);
    
public:
    SettingsBasePage(Display* display, TouchScreen* touch, const char* title, uint16_t color);
    virtual ~SettingsBasePage();
    
    void draw() override;
    int handleTouch(uint16_t x, uint16_t y) override;
    
protected:
    virtual void drawHeader();
    virtual void drawContent() = 0; // À implémenter par les classes dérivées
};

// ============== Specialized Pages ==============

class CloudPage : public SettingsBasePage {
public:
    CloudPage(Display* display, TouchScreen* touch);
protected:
    void drawContent() override;
};

class WiFiPage : public SettingsBasePage {
public:
    WiFiPage(Display* display, TouchScreen* touch);
protected:
    void drawContent() override;
};

class MQTTPage : public SettingsBasePage {
private:
    int currentTab = 0; // 0=Activation, 1=Paramètre, 2=Test
    int btnTab[3];
    static void onTabClick(void* context);
public:
    MQTTPage(Display* display, TouchScreen* touch);
    int handleTouch(uint16_t x, uint16_t y) override;
protected:
    void drawContent() override;
    void drawTabs();
};

class PumpPage : public SettingsBasePage {
public:
    PumpPage(Display* display, TouchScreen* touch);
protected:
    void drawContent() override;
};

class SwitchPage : public SettingsBasePage {
public:
    SwitchPage(Display* display, TouchScreen* touch);
protected:
    void drawContent() override;
};

class LevelProbePage : public SettingsBasePage {
public:
    LevelProbePage(Display* display, TouchScreen* touch);
protected:
    void drawContent() override;
};

class PoolFillPage : public SettingsBasePage {
public:
    PoolFillPage(Display* display, TouchScreen* touch);
protected:
    void drawContent() override;
};

class LockPage : public SettingsBasePage {
public:
    LockPage(Display* display, TouchScreen* touch);
protected:
    void drawContent() override;
};

class ScreenPage : public SettingsBasePage {
public:
    ScreenPage(Display* display, TouchScreen* touch);
protected:
    void drawContent() override;
};

class LanguagePage : public SettingsBasePage {
private:
    int selectedLanguage = 1; // 0=English, 1=Francais, 2=Español, 3=Italiano
    int btnLanguage[4];
    static void onLanguageSelect(void* context);
public:
    LanguagePage(Display* display, TouchScreen* touch);
    int handleTouch(uint16_t x, uint16_t y) override;
protected:
    void drawContent() override;
};

class ResetPage : public SettingsBasePage {
private:
    int btnResetWiFi;
    int btnResetSettings;
    int btnResetDevice;
    static void onResetWiFi(void* context);
    static void onResetSettings(void* context);
    static void onResetDevice(void* context);
public:
    ResetPage(Display* display, TouchScreen* touch);
protected:
    void drawContent() override;
};

#endif
