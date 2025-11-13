/*
 * MenuPage.h - Page de menu avec options
 */

#ifndef MENU_PAGE_H
#define MENU_PAGE_H

#include "utils/Page.h"
#include "HomePage.h"  // Pour les PageID

class MenuPage : public Page {
private:
    // Bouton retour
    const int16_t btnBackX = 20;
    const int16_t btnBackY = 20;
    const int16_t btnBackW = 100;
    const int16_t btnBackH = 40;
    
    // Options du menu
    const int16_t optionX = 100;
    const int16_t optionStartY = 100;
    const int16_t optionW = 280;
    const int16_t optionH = 50;
    const int16_t optionSpacing = 60;
    
    bool isTouchInRect(uint16_t x, uint16_t y, int16_t rx, int16_t ry, int16_t rw, int16_t rh);
    void drawButton(int16_t x, int16_t y, int16_t w, int16_t h,
                    const char* text, uint16_t bgColor, uint16_t textColor);

public:
    MenuPage(Display* display, TouchScreen* touch);
    
    void draw() override;
    int handleTouch(uint16_t x, uint16_t y) override;
};

#endif // MENU_PAGE_H
