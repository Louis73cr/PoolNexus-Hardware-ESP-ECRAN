/**
 * @file MenuPage.hpp
 * @brief Page de menu avec options de navigation
 * 
 * Affiche un menu avec plusieurs options permettant d'accéder
 * aux différentes sections de l'application.
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#ifndef MENU_PAGE_H
#define MENU_PAGE_H

#include "utils/Page.hpp"
#include "HomePage.hpp"  // Pour les PageID

/**
 * @class MenuPage
 * @brief Page de menu principal avec navigation vers les sous-pages
 * 
 * Interface graphique:
 * - Bouton "Retour" en haut à gauche
 * - Liste d'options cliquables:
 *   - Status
 *   - Settings
 *   - Home
 */
class MenuPage : public Page {
private:
    // ========== Bouton Retour ==========
    
    /** @brief Position X du bouton Retour */
    const int16_t btnBackX = 20;
    /** @brief Position Y du bouton Retour */
    const int16_t btnBackY = 20;
    /** @brief Largeur du bouton Retour */
    const int16_t btnBackW = 100;
    /** @brief Hauteur du bouton Retour */
    const int16_t btnBackH = 40;
    
    // ========== Options du menu ==========
    
    /** @brief Position X des options */
    const int16_t optionX = 100;
    /** @brief Position Y de la première option */
    const int16_t optionStartY = 100;
    /** @brief Largeur des options */
    const int16_t optionW = 280;
    /** @brief Hauteur des options */
    const int16_t optionH = 50;
    /** @brief Espacement vertical entre les options */
    const int16_t optionSpacing = 60;
    
    /**
     * @brief Vérifie si un point est dans un rectangle
     * @param x Coordonnée X du point
     * @param y Coordonnée Y du point
     * @param rx Position X du rectangle
     * @param ry Position Y du rectangle
     * @param rw Largeur du rectangle
     * @param rh Hauteur du rectangle
     * @return true si le point est dans le rectangle
     */
    bool isTouchInRect(uint16_t x, uint16_t y, int16_t rx, int16_t ry, int16_t rw, int16_t rh);
    
    /**
     * @brief Dessine un bouton avec texte
     * @param x Position X
     * @param y Position Y
     * @param w Largeur
     * @param h Hauteur
     * @param text Texte du bouton
     * @param bgColor Couleur de fond
     * @param textColor Couleur du texte
     */
    void drawButton(int16_t x, int16_t y, int16_t w, int16_t h,
                    const char* text, uint16_t bgColor, uint16_t textColor);

public:
    /**
     * @brief Constructeur de la MenuPage
     * @param display Pointeur vers Display
     * @param touch Pointeur vers TouchScreen
     */
    MenuPage(Display* display, TouchScreen* touch);
    
    /**
     * @brief Dessine l'interface du menu
     * 
     * Affiche:
     * - Titre "Menu"
     * - Bouton "Retour"
     * - Options: Status, Settings, Home
     */
    void draw() override;
    
    /**
     * @brief Gère les touches sur le menu
     * 
     * @param x Coordonnée X du toucher
     * @param y Coordonnée Y du toucher
     * @return ID de la page destination ou -1
     */
    int handleTouch(uint16_t x, uint16_t y) override;
};

#endif // MENU_PAGE_H
