/**
 * @file StartupPage.hpp
 * @brief Page de démarrage avec logo Nexus
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#ifndef STARTUP_PAGE_HPP
#define STARTUP_PAGE_HPP

#include "utils/Page.hpp"
#include "utils/interface-utils.hpp"

/**
 * @class StartupPage
 * @brief Page affichée au démarrage avec logo et barre de chargement
 */
class StartupPage : public Page {
private:
    interfaceUtils* utils;
    unsigned long startTime;
    int progress = 0;
    bool isComplete = false;

public:
    StartupPage(Display* display, TouchScreen* touch);
    virtual ~StartupPage();
    
    void draw() override;
    int handleTouch(uint16_t x, uint16_t y) override;
    
    void updateProgress(int percent);
    bool isLoadingComplete();
    
private:
    void drawLogo();
    void drawProgressBar();
};

#endif
