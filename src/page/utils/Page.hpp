/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   Page.hpp                                       :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: Louis Croci <louis.croci@epitech.eu>       +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/14 21:26:02 by Louis Croci    #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/14 21:26:02 by Louis Croci    ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */
/**
 * @file Page.hpp
 * @brief Abstract page interface for LVGL UI.
 */
#ifndef PAGE_H
#define PAGE_H

class Page {
public:
    virtual ~Page() {}

    /**
     * @brief Appelé une seule fois lorsque la page devient active.
     * Doit créer toute l’interface LVGL.
     */
    virtual void create() = 0;

    /**
     * @brief Appelé dans la boucle d’exécution pour mettre à jour
     * les valeurs visibles (sans recréer la GUI).
     */
    virtual void show() = 0;

    /**
     * @brief Appelé une seule fois lorsque la page devient active.
     * Optionnel.
     */
    virtual void onEnter() {}

    /**
     * @brief Appelé une seule fois lorsque la page est quittée.
     * Optionnel.
     */
    virtual void onExit() {}

    /**
     * @brief Appelé une seule fois lorsque la page est masquée.
     * Optionnel.
     */
    virtual void onHide() {}
};

/**
 * @enum PageID
 * @brief Identifiants des pages de l'application
 */
enum PageID {
    PAGE_STARTUP = 0,
    PAGE_MAIN_DISPLAY = 1,
    PAGE_SETTINGS = 3,
    PAGE_CALIBRATION_PH = 4,
    PAGE_CALIBRATION_REDOX = 5,
    PAGE_ALERT = 6,
    PAGE_INFO = 7,
    PAGE_CLOUD = 8,
    PAGE_WIFI = 9,
    PAGE_MQTT = 10,
    PAGE_PUMP = 11,
    PAGE_SWITCH = 12,
    PAGE_LEVEL_PROBE = 13,
    PAGE_POOL_FILL = 14,
    PAGE_LOCK = 15,
    PAGE_SCREEN = 16,
    PAGE_LANGUAGE = 17,
    PAGE_RESET = 18,
    PAGE_COUNT
};

enum PageType {
    HOME,
    STANDARD,
    ALERT,
    INFO,
};

#endif // PAGE_H
