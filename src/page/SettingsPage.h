/*
 * SettingsPage.h - Page de paramètres (exemple simple)
 */

#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H

#include "utils/Page.h"
#include "HomePage.h"

class SettingsPage : public Page {
private:
    const int16_t btnBackX = 180;
    const int16_t btnBackY = 240;
    const int16_t btnBackW = 120;
    const int16_t btnBackH = 50;
    
    bool isTouchInRect(uint16_t x, uint16_t y, int16_t rx, int16_t ry, int16_t rw, int16_t rh);
    void drawButton(int16_t x, int16_t y, int16_t w, int16_t h,
                    const char* text, uint16_t bgColor, uint16_t textColor);

public:
    SettingsPage(Display* display, TouchScreen* touch);
    
    void draw() override;
    int handleTouch(uint16_t x, uint16_t y) override;
};

#endif // SETTINGS_PAGE_H
