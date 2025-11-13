/**
 * @file MainDisplayPage.hpp
 * @brief Page d'affichage principal avec mesures pH, Redox, Température
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#ifndef MAIN_DISPLAY_PAGE_HPP
#define MAIN_DISPLAY_PAGE_HPP

#include "utils/Page.hpp"
#include "utils/interface-utils.hpp"

/**
 * @class MainDisplayPage
 * @brief Page principale affichant les mesures en temps réel
 */
class MainDisplayPage : public Page {
private:
    interfaceUtils* utils;
    
    // Valeurs de mesure
    float phValue = 7.08;
    int redoxValue = 470;
    float tempValue = 27.5;
    
    // États des icônes
    bool isPowerOn = true;
    bool isFilterOn = false;
    bool hasAlert = false;
    
    // IDs des boutons
    int btnPower;
    int btnFilter;
    int btnAlert;
    int btnSettings;
    
    // Page de destination demandée par un callback (-1 = rester sur la page)
    int nextPage;
    
    // Callbacks statiques
    static void onPowerClick(void* context);
    static void onFilterClick(void* context);
    static void onAlertClick(void* context);
    static void onSettingsClick(void* context);
    
    void drawMeasurementCard(int16_t y, const char* label, String value, const char* unit, uint16_t valueColor, bool hasMenuIcon);
    void drawPowerIcon(int16_t x, int16_t y, bool isOn);
    void drawPumpIcon(int16_t x, int16_t y);
    void drawAlertIcon(int16_t x, int16_t y);
    void drawSettingsIcon(int16_t x, int16_t y);

public:
    MainDisplayPage(Display* display, TouchScreen* touch);
    virtual ~MainDisplayPage();
    
    void draw() override;
    int handleTouch(uint16_t x, uint16_t y) override;
    
    // Méthodes publiques pour mettre à jour les valeurs
    void updatePH(float value);
    void updateRedox(int value);
    void updateTemperature(float value);
};

#endif
