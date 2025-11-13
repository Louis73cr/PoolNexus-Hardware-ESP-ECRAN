/**
 * @file SettingsPage.hpp
 * @brief Page de configuration et paramètres
 * 
 * Affiche les options de configuration de l'application:
 * - Luminosité de l'écran
 * - Configuration WiFi
 * - Réglages sonores
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H

#include "utils/Page.hpp"
#include "HomePage.hpp"

/**
 * @class SettingsPage
 * @brief Page de paramètres de l'application
 * 
 * Interface graphique:
 * - Titre "Paramètres"
 * - Liste des paramètres ajustables
 * - Bouton "Retour" pour revenir au menu
 */
class SettingsPage : public Page {
private:
    /** @brief Position X du bouton Retour */
    const int16_t btnBackX = 180;
    /** @brief Position Y du bouton Retour */
    const int16_t btnBackY = 240;
    /** @brief Largeur du bouton Retour */
    const int16_t btnBackW = 120;
    /** @brief Hauteur du bouton Retour */
    const int16_t btnBackH = 50;
    
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
     * @brief Dessine un bouton rectangulaire
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
     * @brief Constructeur de la SettingsPage
     * @param display Pointeur vers Display
     * @param touch Pointeur vers TouchScreen
     */
    SettingsPage(Display* display, TouchScreen* touch);
    
    /**
     * @brief Dessine l'interface des paramètres
     * 
     * Affiche:
     * - Titre "Paramètres"
     * - Options de configuration:
     *   - Luminosité: 80%
     *   - WiFi: Non connecté
     *   - Son: Activé
     * - Bouton "Retour"
     */
    void draw() override;
    
    /**
     * @brief Gère les touches sur la page de paramètres
     * 
     * Détecte le clic sur le bouton "Retour" pour revenir au menu.
     * 
     * @param x Coordonnée X du toucher
     * @param y Coordonnée Y du toucher
     * @return PAGE_MENU si retour cliqué, -1 sinon
     */
    int handleTouch(uint16_t x, uint16_t y) override;
};

#endif // SETTINGS_PAGE_H
