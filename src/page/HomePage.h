/*
 * HomePage.h - Page d'accueil de l'application
 * 
 * Affiche:
 * - Titre
 * - Boutons pour naviguer vers d'autres pages
 * - Informations système
 */

#ifndef HOME_PAGE_H
#define HOME_PAGE_H

#include "utils/Page.h"

// IDs des pages (à synchroniser avec main.cpp)
enum PageID {
    PAGE_HOME = 0,
    PAGE_MENU = 1,
    PAGE_SETTINGS = 2,
    PAGE_STATUS = 3
};

class HomePage : public Page {
private:
    // Zone de bouton "Menu" (x, y, largeur, hauteur)
    const int16_t btnMenuX = 50;
    const int16_t btnMenuY = 200;
    const int16_t btnMenuW = 150;
    const int16_t btnMenuH = 60;
    
    // Zone de bouton "Status"
    const int16_t btnStatusX = 280;
    const int16_t btnStatusY = 200;
    const int16_t btnStatusW = 150;
    const int16_t btnStatusH = 60;
    
    /*
     * isTouchInRect() - Vérifie si un point est dans un rectangle
     */
    bool isTouchInRect(uint16_t x, uint16_t y, int16_t rx, int16_t ry, int16_t rw, int16_t rh);
    
    /*
     * drawButton() - Dessine un bouton avec texte centré
     */
    void drawButton(int16_t x, int16_t y, int16_t w, int16_t h, 
                    const char* text, uint16_t bgColor, uint16_t textColor);

public:
    HomePage(Display* display, TouchScreen* touch);
    
    void draw() override;
    int handleTouch(uint16_t x, uint16_t y) override;
    void update() override;
    void onEnter() override;
};

#endif // HOME_PAGE_H
