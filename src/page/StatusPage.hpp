/**
 * @file StatusPage.hpp
 * @brief Page d'affichage du statut système en temps réel
 * 
 * Affiche les informations de diagnostic du système:
 * - Mémoire disponible (Heap)
 * - PSRAM disponible
 * - Fréquence du CPU
 * - Temps de fonctionnement (uptime)
 * - Compteur de rafraîchissements
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#ifndef STATUS_PAGE_H
#define STATUS_PAGE_H

#include "utils/Page.hpp"
#include "HomePage.hpp"

/**
 * @class StatusPage
 * @brief Page de statut système avec mise à jour en temps réel
 * 
 * Interface graphique:
 * - Titre "Statut Système"
 * - Informations ESP32 mises à jour dynamiquement
 * - Bouton "Retour" pour revenir au menu
 * 
 * Cette page utilise update() pour rafraîchir les informations
 * toutes les secondes.
 */
class StatusPage : public Page {
private:
    /** @brief Position X du bouton Retour */
    const int16_t btnBackX = 20;
    /** @brief Position Y du bouton Retour */
    const int16_t btnBackY = 260;
    /** @brief Largeur du bouton Retour */
    const int16_t btnBackW = 120;
    /** @brief Hauteur du bouton Retour */
    const int16_t btnBackH = 50;
    
    /** @brief Timestamp de la dernière mise à jour (millisecondes) */
    unsigned long lastUpdate;
    /** @brief Compteur de rafraîchissements de la page */
    uint16_t updateCounter;
    
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
     * @brief Constructeur de la StatusPage
     * @param display Pointeur vers Display
     * @param touch Pointeur vers TouchScreen
     */
    StatusPage(Display* display, TouchScreen* touch);
    
    /**
     * @brief Dessine l'interface de la page de statut
     * 
     * Affiche:
     * - Titre "Statut Système"
     * - Heap libre (bytes)
     * - PSRAM libre (bytes)
     * - Fréquence CPU (MHz)
     * - Uptime (millisecondes)
     * - Compteur de mises à jour
     * - Bouton "Retour"
     */
    void draw() override;
    
    /**
     * @brief Gère les touches sur la page de statut
     * 
     * Détecte le clic sur le bouton "Retour" pour revenir au menu.
     * 
     * @param x Coordonnée X du toucher
     * @param y Coordonnée Y du toucher
     * @return PAGE_MENU si retour cliqué, -1 sinon
     */
    int handleTouch(uint16_t x, uint16_t y) override;
    
    /**
     * @brief Met à jour la page toutes les secondes
     * 
     * Vérifie si 1000ms se sont écoulées depuis lastUpdate.
     * Si oui, incrémente updateCounter et force un redessin pour
     * afficher les nouvelles valeurs de mémoire/uptime.
     */
    void update() override;
    
    /**
     * @brief Appelée lors de l'entrée sur la page
     * 
     * Initialise le timestamp et le compteur.
     */
    void onEnter() override;
};

#endif // STATUS_PAGE_H
