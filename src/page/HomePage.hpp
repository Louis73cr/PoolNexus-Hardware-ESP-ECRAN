/**
 * @file HomePage.hpp
 * @brief Page d'accueil de l'application
 * 
 * La HomePage est la première page affichée au démarrage.
 * Elle présente:
 * - Un titre de bienvenue
 * - Des boutons de navigation vers Menu et Status
 * - Des informations système (mémoire, PSRAM)
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#ifndef HOME_PAGE_H
#define HOME_PAGE_H

#include "utils/Page.hpp"

/**
 * @enum PageID
 * @brief Identifiants des pages de l'application
 * 
 * Ces constantes doivent être synchronisées avec les IDs utilisés
 * dans main.cpp lors de l'enregistrement des pages.
 */
enum PageID {
    PAGE_HOME = 0,      ///< Page d'accueil
    PAGE_MENU = 1,      ///< Page de menu
    PAGE_SETTINGS = 2,  ///< Page de paramètres
    PAGE_STATUS = 3     ///< Page de statut système
};

/**
 * @class HomePage
 * @brief Page d'accueil avec navigation vers les sections principales
 * 
 * Interface graphique:
 * - Fond bleu avec titre blanc
 * - Bouton "Menu" en bas à gauche
 * - Bouton "Status" en bas à droite
 * - Affichage de la mémoire libre
 */
class HomePage : public Page {
private:
    // ========== Zones de boutons (coordonnées en pixels) ==========
    
    /** @brief Position X du bouton Menu */
    const int16_t btnMenuX = 50;
    /** @brief Position Y du bouton Menu */
    const int16_t btnMenuY = 200;
    /** @brief Largeur du bouton Menu */
    const int16_t btnMenuW = 150;
    /** @brief Hauteur du bouton Menu */
    const int16_t btnMenuH = 60;
    
    /** @brief Position X du bouton Status */
    const int16_t btnStatusX = 280;
    /** @brief Position Y du bouton Status */
    const int16_t btnStatusY = 200;
    /** @brief Largeur du bouton Status */
    const int16_t btnStatusW = 150;
    /** @brief Hauteur du bouton Status */
    const int16_t btnStatusH = 60;
    
    /**
     * @brief Vérifie si un point est à l'intérieur d'un rectangle
     * 
     * Méthode utilitaire pour détecter les clics sur les boutons.
     * 
     * @param x Coordonnée X du point à tester
     * @param y Coordonnée Y du point à tester
     * @param rx Position X du rectangle
     * @param ry Position Y du rectangle
     * @param rw Largeur du rectangle
     * @param rh Hauteur du rectangle
     * @return true si (x,y) est dans le rectangle, false sinon
     */
    bool isTouchInRect(uint16_t x, uint16_t y, int16_t rx, int16_t ry, int16_t rw, int16_t rh);
    
    /**
     * @brief Dessine un bouton rectangulaire avec texte centré
     * 
     * @param x Position X du coin supérieur gauche
     * @param y Position Y du coin supérieur gauche
     * @param w Largeur du bouton
     * @param h Hauteur du bouton
     * @param text Texte à afficher au centre
     * @param bgColor Couleur de fond du bouton
     * @param textColor Couleur du texte
     */
    void drawButton(int16_t x, int16_t y, int16_t w, int16_t h, 
                    const char* text, uint16_t bgColor, uint16_t textColor);

public:
    /**
     * @brief Constructeur de la HomePage
     * 
     * @param display Pointeur vers l'objet Display
     * @param touch Pointeur vers l'objet TouchScreen
     */
    HomePage(Display* display, TouchScreen* touch);
    
    /**
     * @brief Dessine l'interface de la page d'accueil
     * 
     * Affiche:
     * - Fond bleu
     * - Titre "PoolNexus" en haut
     * - Informations mémoire (Heap, PSRAM)
     * - Bouton "Menu"
     * - Bouton "Status"
     */
    void draw() override;
    
    /**
     * @brief Gère les touches sur la page d'accueil
     * 
     * Détecte les clics sur:
     * - Bouton "Menu" → navigue vers PAGE_MENU
     * - Bouton "Status" → navigue vers PAGE_STATUS
     * 
     * @param x Coordonnée X du toucher
     * @param y Coordonnée Y du toucher
     * @return PAGE_MENU, PAGE_STATUS, ou -1 (rester sur la page)
     */
    int handleTouch(uint16_t x, uint16_t y) override;
    
    /**
     * @brief Met à jour la logique de la page (optionnel)
     */
    void update() override;
    
    /**
     * @brief Appelée lors de l'entrée sur la page
     */
    void onEnter() override;
};

#endif // HOME_PAGE_H
