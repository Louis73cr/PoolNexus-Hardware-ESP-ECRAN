/**
 * @file AlertInfoPages.hpp
 * @brief Pages d'alerte et d'information
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#ifndef ALERT_INFO_PAGES_HPP
#define ALERT_INFO_PAGES_HPP

#include "utils/Page.hpp"
#include "utils/interface-utils.hpp"
#include <vector>

/**
 * @class AlertPage
 * @brief Page d'affichage des alertes
 */
class AlertPage : public Page {
private:
    interfaceUtils* utils;
    std::vector<String> alerts;
    int currentAlertIndex = 0;
    
    // Button IDs
    int btnClose;
    int btnDelete;
    int btnPrevious;
    int btnNext;
    
    // Page de destination demandée par un callback (-1 = rester sur la page)
    int nextPageId;
    
    static void onCloseClick(void* context);
    static void onDeleteClick(void* context);
    static void onPreviousClick(void* context);
    static void onNextClick(void* context);

public:
    AlertPage(Display* display, TouchScreen* touch);
    virtual ~AlertPage();
    
    void draw() override;
    int handleTouch(uint16_t x, uint16_t y) override;
    void addAlert(String alert);
    
private:
    void drawHeader();
    void drawAlertContent();
    void drawNavigation();
};

/**
 * @class InfoPage
 * @brief Page d'informations générales
 */
class InfoPage : public Page {
private:
    interfaceUtils* utils;
    String infoTitle;
    String infoContent;
    
    // Button IDs
    int btnClose;
    
    // Page de destination demandée par un callback (-1 = rester sur la page)
    int nextPageId;
    
    static void onCloseClick(void* context);

public:
    InfoPage(Display* display, TouchScreen* touch);
    virtual ~InfoPage();
    
    void draw() override;
    int handleTouch(uint16_t x, uint16_t y) override;
    void setInfo(String title, String content);
    
private:
    void drawHeader();
    void drawContent();
};

#endif
