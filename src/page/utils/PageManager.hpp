/**
 * @file PageManager.hpp
 * @brief Gestionnaire de navigation entre pages (State Machine Pattern)
 * 
 * Le PageManager implémente une machine à états pour gérer la navigation
 * entre différentes pages de l'interface utilisateur.
 * 
 * Responsabilités:
 * - Enregistrement des pages disponibles
 * - Gestion de la page active
 * - Transitions entre pages
 * - Appels automatiques des méthodes draw(), update(), handleTouch()
 * - Historique de navigation pour bouton "Retour"
 * 
 * Architecture:
 * - Pattern State Machine: chaque page est un état
 * - Pattern Observer: détecte les touches et notifie la page active
 * - Pattern Command: handleTouch() retourne l'ID de la prochaine page
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H

#include <Arduino.h>
#include "Page.hpp"

/** @brief Taille maximale de l'historique de navigation */
#define MAX_PAGE_HISTORY 10

/**
 * @class PageManager
 * @brief Gestionnaire central de navigation et d'affichage des pages
 * 
 * Cette classe coordonne toutes les pages de l'application et gère
 * les transitions entre elles. Elle sert d'intermédiaire entre
 * le matériel (Display, TouchScreen) et les pages.
 * 
 * Workflow typique:
 * 1. Création du PageManager avec Display et TouchScreen
 * 2. Enregistrement de toutes les pages via registerPage()
 * 3. Définition de la page initiale avec setCurrentPage()
 * 4. Appel de update() dans loop() pour gérer tout automatiquement
 * 
 * Exemple d'utilisation:
 * @code
 * Display screen;
 * TouchScreen touch;
 * PageManager manager(&screen, &touch, 4);
 * 
 * HomePage home(&screen, &touch);
 * MenuPage menu(&screen, &touch);
 * 
 * manager.registerPage(0, &home);
 * manager.registerPage(1, &menu);
 * manager.setCurrentPage(0);
 * 
 * void loop() {
 *     manager.update();  // Gère tout automatiquement
 * }
 * @endcode
 */
class PageManager {
private:
    /** @brief Tableau dynamique de pointeurs vers les pages enregistrées */
    Page** pages;
    /** @brief Nombre total de pages enregistrables */
    int numPages;
    /** @brief ID de la page actuellement affichée */
    int currentPageId;
    /** @brief Pile d'historique des pages visitées (pour navigation arrière) */
    int pageHistory[MAX_PAGE_HISTORY];
    /** @brief Taille actuelle de la pile d'historique */
    int historySize;
    
    /** @brief Pointeur partagé vers l'objet Display */
    Display* display;
    /** @brief Pointeur partagé vers l'objet TouchScreen */
    TouchScreen* touch;

public:
    // ========== Constructeur et destructeur ==========
    
    /**
     * @brief Constructeur du PageManager
     * 
     * Alloue la mémoire pour stocker les pointeurs de pages et initialise
     * les variables internes.
     * 
     * @param display Pointeur vers l'objet Display (ne doit pas être nullptr)
     * @param touch Pointeur vers l'objet TouchScreen (ne doit pas être nullptr)
     * @param maxPages Nombre maximum de pages gérables
     * 
     * @note Appelez registerPage() pour chaque page après construction
     */
    PageManager(Display* display, TouchScreen* touch, int maxPages);
    
    /**
     * @brief Destructeur du PageManager
     * 
     * Libère la mémoire allouée pour le tableau de pages.
     * 
     * @note Ne détruit PAS les objets Page eux-mêmes (responsabilité de l'appelant)
     */
    ~PageManager();
    
    // ========== Enregistrement des pages ==========
    
    /**
     * @brief Enregistre une page dans le gestionnaire
     * 
     * Associe un ID unique à un objet Page. Cet ID sera utilisé pour
     * la navigation entre pages.
     * 
     * @param pageId Identifiant unique de la page (0 à numPages-1)
     * @param page Pointeur vers l'objet Page à enregistrer
     * 
     * @warning Le pageId doit être < numPages, sinon comportement indéfini
     * @note Appelez cette méthode pour toutes vos pages dans setup()
     */
    void registerPage(int pageId, Page* page);
    
    // ========== Navigation entre pages ==========
    
    /**
     * @brief Change la page actuellement affichée
     * 
     * Effectue une transition vers une nouvelle page:
     * 1. Appelle onExit() sur la page actuelle
     * 2. Ajoute la page actuelle à l'historique (si demandé)
     * 3. Change currentPageId
     * 4. Appelle onEnter() sur la nouvelle page
     * 5. Active le flag needsRedraw
     * 
     * @param pageId ID de la page destination
     * @param addToHistory Si true, ajoute la page actuelle à l'historique (défaut: true)
     * 
     * @note Si addToHistory=false, le bouton retour ne pourra pas revenir à cette page
     */
    void setCurrentPage(int pageId, bool addToHistory = true);
    
    /**
     * @brief Retourne l'ID de la page actuellement affichée
     * 
     * @return ID de la page active
     */
    int getCurrentPageId() const {
        return currentPageId;
    }
    
    /**
     * @brief Retourne à la page précédente dans l'historique
     * 
     * Implémente la fonctionnalité "bouton retour" en dépilant l'historique.
     * 
     * @return true si retour effectué avec succès, false si l'historique est vide
     * 
     * @note Utilise setCurrentPage() avec addToHistory=false pour éviter la boucle
     */
    bool goBack();
    
    /**
     * @brief Efface complètement l'historique de navigation
     * 
     * Vide la pile d'historique. Le bouton retour ne fonctionnera plus
     * jusqu'à ce que de nouvelles pages soient visitées.
     * 
     * @note Utile pour redémarrer la navigation depuis une page racine
     */
    void clearHistory();
    
    // ========== Mise à jour (appel dans loop) ==========
    
    /**
     * @brief Met à jour la page active et gère les interactions
     * 
     * Méthode principale à appeler dans loop().
     * Elle gère automatiquement:
     * 1. Appel de page->update() (animations, logique)
     * 2. Détection de toucher via TouchScreen
     * 3. Si touché: appel de page->handleTouch(x, y)
     * 4. Si handleTouch retourne un ID != -1: navigation vers cette page
     * 5. Si needsRedraw activé: appel de page->draw()
     * 
     * @note Cette méthode centralise toute la logique de l'interface!
     * 
     * Exemple typique:
     * @code
     * void loop() {
     *     pageManager.update();
     *     delay(10);
     * }
     * @endcode
     */
    void update();
    
    /**
     * @brief Force le redessin complet de la page active
     * 
     * Active le flag needsRedraw de la page courante, ce qui provoquera
     * un appel de draw() lors du prochain update().
     * 
     * @note Utile après des changements externes (données, configuration, etc.)
     */
    void forceRedraw();
};

#endif // PAGE_MANAGER_H
