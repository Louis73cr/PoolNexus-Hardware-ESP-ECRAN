/**
 * @file Page.hpp
 * @brief Classe abstraite de base pour toutes les pages de l'interface
 * 
 * Définit le contrat que chaque page doit respecter:
 * - draw(): Affiche l'interface de la page
 * - handleTouch(x, y): Gère les événements tactiles et retourne la navigation
 * - update(): Met à jour la logique (optionnel)
 * - onEnter(): Appelé lors de l'entrée sur la page (optionnel)
 * - onExit(): Appelé lors de la sortie de la page (optionnel)
 * 
 * Pattern de conception: Template Method
 * Permet d'implémenter facilement de nouvelles pages avec comportement cohérent.
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#ifndef PAGE_H
#define PAGE_H

#include <Arduino.h>
#include "../../screen/Display.hpp"
#include "../../screen/TouchScreen.hpp"

/**
 * @class Page
 * @brief Classe abstraite représentant une page de l'interface utilisateur
 * 
 * Chaque page de l'application (HomePage, MenuPage, etc.) hérite de cette classe
 * et implémente les méthodes virtuelles pures draw() et handleTouch().
 * 
 * La classe fournit:
 * - Accès aux objets Display et TouchScreen
 * - Gestion du flag de redessin (needsRedraw)
 * - Lifecycle hooks (onEnter/onExit)
 * - Méthode update() optionnelle pour animations/capteurs
 * 
 * Exemple d'implémentation:
 * @code
 * class MyPage : public Page {
 * public:
 *     MyPage(Display* display, TouchScreen* touch) 
 *         : Page(display, touch) {}
 *     
 *     void draw() override {
 *         display->fillScreen(Display::COLOR_BLUE);
 *         display->setCursor(10, 10);
 *         display->print("Ma Page");
 *         display->flush();
 *     }
 *     
 *     int handleTouch(uint16_t x, uint16_t y) override {
 *         // Retourner l'ID de la prochaine page ou -1
 *         return -1;
 *     }
 * };
 * @endcode
 */
class Page {
protected:
    /** @brief Pointeur vers l'objet d'affichage partagé */
    Display* display;
    /** @brief Pointeur vers l'objet tactile partagé */
    TouchScreen* touch;
    /** @brief Flag indiquant si la page nécessite un redessin complet */
    bool needsRedraw;

public:
    // ========== Constructeur et destructeur ==========
    
    /**
     * @brief Constructeur de la classe Page
     * 
     * Initialise les pointeurs vers Display et TouchScreen et active le flag needsRedraw.
     * 
     * @param display Pointeur vers l'objet Display (ne doit pas être nullptr)
     * @param touch Pointeur vers l'objet TouchScreen (ne doit pas être nullptr)
     */
    Page(Display* display, TouchScreen* touch)
        : display(display)
        , touch(touch)
        , needsRedraw(true)
    {
    }
    
    /**
     * @brief Destructeur virtuel
     * 
     * Le destructeur virtuel est obligatoire pour les classes abstraites
     * afin de permettre la destruction correcte des objets dérivés.
     */
    virtual ~Page() {}
    
    // ========== Méthodes virtuelles obligatoires ==========
    
    /**
     * @brief Dessine l'interface graphique de la page
     * 
     * Cette méthode DOIT être implémentée par chaque page dérivée.
     * Elle est appelée automatiquement par PageManager quand:
     * - La page devient active pour la première fois
     * - Le flag needsRedraw est activé
     * 
     * Implémentation typique:
     * 1. Effacer l'écran (fillScreen)
     * 2. Dessiner l'interface (textes, boutons, graphiques)
     * 3. Appeler display->flush() pour afficher
     * 
     * @note N'oubliez pas d'appeler flush() à la fin!
     */
    virtual void draw() = 0;
    
    /**
     * @brief Gère les événements tactiles de la page
     * 
     * Cette méthode DOIT être implémentée par chaque page.
     * Elle est appelée par PageManager quand un toucher est détecté.
     * 
     * @param x Coordonnée horizontale du toucher (pixels)
     * @param y Coordonnée verticale du toucher (pixels)
     * @return ID de la prochaine page à afficher, ou -1 pour rester sur cette page
     * 
     * @note Utilisez les coordonnées pour détecter quel bouton a été touché
     */
    virtual int handleTouch(uint16_t x, uint16_t y) = 0;
    
    // ========== Méthodes virtuelles optionnelles ==========
    
    /**
     * @brief Met à jour la logique de la page (appelée en boucle)
     * 
     * Méthode optionnelle appelée à chaque itération de loop() quand la page est active.
     * Utile pour:
     * - Animations continues
     * - Mise à jour de capteurs en temps réel
     * - Timers et compteurs
     * - Rafraîchissement automatique de données
     * 
     * @note Par défaut ne fait rien. Redéfinissez si nécessaire.
     */
    virtual void update() {}
    
    /**
     * @brief Appelée quand on entre sur cette page
     * 
     * Hook de lifecycle appelé par PageManager juste avant le premier draw().
     * Utile pour:
     * - Initialiser des variables
     * - Démarrer des timers
     * - Charger des données
     * 
     * @note Par défaut active needsRedraw. Redéfinissez pour ajouter votre logique.
     */
    virtual void onEnter() {
        needsRedraw = true;
    }
    
    /**
     * @brief Appelée quand on quitte cette page
     * 
     * Hook de lifecycle appelé par PageManager juste avant de changer de page.
     * Utile pour:
     * - Sauvegarder des données
     * - Arrêter des timers
     * - Nettoyer des ressources
     * 
     * @note Par défaut ne fait rien. Redéfinissez si nécessaire.
     */
    virtual void onExit() {}
    
    // ========== Gestion du flag de redessin ==========
    
    /**
     * @brief Force le redessin complet de la page
     * 
     * Active le flag needsRedraw, ce qui provoquera l'appel de draw()
     * lors de la prochaine itération de PageManager::update().
     * 
     * Utilisez cette méthode quand:
     * - Des données ont changé et l'affichage doit être rafraîchi
     * - Un événement externe nécessite un redessin
     */
    void setNeedsRedraw() {
        needsRedraw = true;
    }
    
    /**
     * @brief Vérifie si la page nécessite un redessin
     * 
     * @return true si draw() doit être appelé, false sinon
     * @note Utilisé par PageManager pour optimiser les rafraîchissements
     */
    bool getNeedsRedraw() const {
        return needsRedraw;
    }
    
    /**
     * @brief Efface le flag de redessin
     * 
     * Appelé automatiquement par PageManager après avoir appelé draw().
     * 
     * @note Vous ne devriez pas avoir besoin d'appeler cette méthode manuellement
     */
    void clearRedrawFlag() {
        needsRedraw = false;
    }
};

#endif // PAGE_H
