/*
 * StatusPage.h - Page d'affichage de statut système
 */

#ifndef STATUS_PAGE_H
#define STATUS_PAGE_H

#include "utils/Page.h"
#include "HomePage.h"

class StatusPage : public Page {
private:
    const int16_t btnBackX = 20;
    const int16_t btnBackY = 260;
    const int16_t btnBackW = 120;
    const int16_t btnBackH = 50;
    
    unsigned long lastUpdate;
    uint16_t updateCounter;
    
    bool isTouchInRect(uint16_t x, uint16_t y, int16_t rx, int16_t ry, int16_t rw, int16_t rh);
    void drawButton(int16_t x, int16_t y, int16_t w, int16_t h,
                    const char* text, uint16_t bgColor, uint16_t textColor);

public:
    StatusPage(Display* display, TouchScreen* touch);
    
    void draw() override;
    int handleTouch(uint16_t x, uint16_t y) override;
    void update() override;
    void onEnter() override;
};

#endif // STATUS_PAGE_H
