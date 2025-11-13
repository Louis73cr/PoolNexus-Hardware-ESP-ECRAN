/**
 * @file SettingsPage.hpp
 * @brief Page de paramètres avec pagination (5 pages)
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H

#include "utils/Page.hpp"
#include "utils/interface-utils.hpp"

class SettingsPage : public Page {
private:
    interfaceUtils* utils;
    
    // Pagination
    int currentPage;
    const int totalPages = 5;
    
    // IDs des boutons
    int btnClose;
    int btnPrevious;
    int btnNext;
    
    // IDs des boutons de paramètres (3 par page)
    int btnSetting1;
    int btnSetting2;
    int btnSetting3;
    
    // Page de destination demandée par un callback (-1 = rester sur la page)
    int nextPageId;
    
    void drawPageContent();
    
    // Callbacks statiques avec contexte
    static void onCloseClick(void* context);
    static void onPreviousClick(void* context);
    static void onNextClick(void* context);

public:
    SettingsPage(Display* display, TouchScreen* touch);
    virtual ~SettingsPage();
    
    void draw() override;
    int handleTouch(uint16_t x, uint16_t y) override;
    
    void nextPage();
    void previousPage();
};

#endif // SETTINGS_PAGE_H
