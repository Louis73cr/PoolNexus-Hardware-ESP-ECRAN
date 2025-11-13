/*
 * Page.h - Classe abstraite de base pour toutes les pages
 * 
 * Chaque page de l'application hérite de cette classe et implémente:
 * - draw(): Dessine l'interface de la page
 * - handleTouch(): Gère les interactions tactiles
 * - update(): Met à jour la logique (optionnel)
 */

#ifndef PAGE_H
#define PAGE_H

#include <Arduino.h>
#include "../../screen/Display.h"
#include "../../screen/TouchScreen.h"

class Page {
protected:
    Display* display;        // Pointeur vers l'écran
    TouchScreen* touch;      // Pointeur vers le tactile
    bool needsRedraw;        // Flag indiquant si la page doit être redessinée

public:
    /*
     * Constructeur
     * display: pointeur vers l'objet Display
     * touch: pointeur vers l'objet TouchScreen
     */
    Page(Display* display, TouchScreen* touch)
        : display(display)
        , touch(touch)
        , needsRedraw(true)
    {
    }
    
    /*
     * Destructeur virtuel (important pour les classes abstraites)
     */
    virtual ~Page() {}
    
    /*
     * draw() - Dessine l'interface de la page
     * DOIT être implémenté par chaque page
     * Appelé automatiquement quand la page devient active
     */
    virtual void draw() = 0;
    
    /*
     * handleTouch() - Gère les événements tactiles
     * x, y: coordonnées du toucher
     * Retourne: ID de la page suivante, ou -1 pour rester sur cette page
     */
    virtual int handleTouch(uint16_t x, uint16_t y) = 0;
    
    /*
     * update() - Met à jour la logique de la page (optionnel)
     * Appelé à chaque tour de boucle
     * Utile pour animations, timers, capteurs, etc.
     */
    virtual void update() {}
    
    /*
     * onEnter() - Appelé quand on entre sur la page (optionnel)
     * Utile pour initialiser des variables, démarrer des timers, etc.
     */
    virtual void onEnter() {
        needsRedraw = true;
    }
    
    /*
     * onExit() - Appelé quand on quitte la page (optionnel)
     * Utile pour nettoyer, sauvegarder, arrêter des timers, etc.
     */
    virtual void onExit() {}
    
    /*
     * setNeedsRedraw() - Force le redessin de la page
     */
    void setNeedsRedraw() {
        needsRedraw = true;
    }
    
    /*
     * getNeedsRedraw() - Indique si la page doit être redessinée
     */
    bool getNeedsRedraw() const {
        return needsRedraw;
    }
    
    /*
     * clearRedrawFlag() - Efface le flag de redessin
     */
    void clearRedrawFlag() {
        needsRedraw = false;
    }
};

#endif // PAGE_H
