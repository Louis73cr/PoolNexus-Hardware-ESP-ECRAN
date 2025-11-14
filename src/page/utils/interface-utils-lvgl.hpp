/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   interface-utils-lvgl.hpp                       :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: Louis Croci <louis.croci@epitech.eu>       +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/14 21:26:31 by Louis Croci    #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/14 21:26:31 by Louis Croci    ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */
/**
 * @file interface-utils-lvgl.hpp
 * @brief Fonctions utilitaires pour créer des éléments d'interface avec LVGL
 */

#ifndef INTERFACE_UTILS_LVGL_HPP
#define INTERFACE_UTILS_LVGL_HPP

#include <lvgl.h>
#include <Arduino.h>

/**
 * @brief Styles standards pour l'interface
 */
namespace LVGLStyles {
    // Couleurs standards
    constexpr uint32_t COLOR_PRIMARY = 0x2196F3;      // Bleu
    constexpr uint32_t COLOR_SUCCESS = 0x4CAF50;      // Vert
    constexpr uint32_t COLOR_WARNING = 0xFF9800;      // Orange
    constexpr uint32_t COLOR_DANGER = 0xF44336;       // Rouge
    constexpr uint32_t COLOR_INFO = 0x00BCD4;         // Cyan
    constexpr uint32_t COLOR_BACKGROUND = 0xECEFF1;   // Gris clair
    constexpr uint32_t COLOR_WHITE = 0xFFFFFF;
    constexpr uint32_t COLOR_BLACK = 0x000000;
    constexpr uint32_t COLOR_TEXT_PRIMARY = 0x212121;
    constexpr uint32_t COLOR_TEXT_SECONDARY = 0x757575;
    
    // Tailles de police
    extern const lv_font_t* FONT_SMALL;    // 14pt
    extern const lv_font_t* FONT_NORMAL;   // 16pt
    extern const lv_font_t* FONT_MEDIUM;   // 20pt
    extern const lv_font_t* FONT_LARGE;    // 24pt
    extern const lv_font_t* FONT_XLARGE;   // 28pt
}

/**
 * @brief Crée une carte (container avec fond blanc et ombres)
 */
lv_obj_t* createCard(lv_obj_t* parent, int16_t x, int16_t y, lv_coord_t width, lv_coord_t height);

/**
 * @brief Crée un bouton stylisé
 */
lv_obj_t* createButton(lv_obj_t* parent, int16_t x, int16_t y, lv_coord_t width, lv_coord_t height,
                       const char* text, uint32_t color = LVGLStyles::COLOR_PRIMARY, int border_radius = 8);

/**
 * @brief Crée un label avec style personnalisé
 */
lv_obj_t* createLabel(lv_obj_t* parent, int16_t x, int16_t y, const char* text,
                      const lv_font_t* font = LVGLStyles::FONT_NORMAL,
                      uint32_t color = LVGLStyles::COLOR_TEXT_PRIMARY);

/**
 * @brief Crée un label de titre (gros, gras)
 */
lv_obj_t* createTitle(lv_obj_t* parent, int16_t x, int16_t y, const char* text);

/**
 * @brief Crée un switch (toggle)
 */
lv_obj_t* createSwitch(lv_obj_t* parent, int16_t x, int16_t y, bool initial_state = false);

/**
 * @brief Crée un slider
 */
lv_obj_t* createSlider(lv_obj_t* parent, int16_t x, int16_t y, lv_coord_t width,
                       int32_t min_value, int32_t max_value, int32_t initial_value);

/**
 * @brief Crée une zone de texte (input)
 */
lv_obj_t* createTextArea(lv_obj_t* parent, int16_t x, int16_t y, lv_coord_t width, lv_coord_t height,
                         const char* placeholder = "");

/**
 * @brief Crée un dropdown (liste déroulante)
 */
lv_obj_t* createDropdown(lv_obj_t* parent, int16_t x, int16_t y, lv_coord_t width,
                         const char* options);

/**
 * @brief Crée une carte de mesure (avec titre et valeur)
 */
lv_obj_t* createMeasurementCard(lv_obj_t* parent, int16_t x, int16_t y, lv_coord_t width, lv_coord_t height,
                                const char* title, const char* value, const lv_font_t* value_font,
                                uint32_t value_color = LVGLStyles::COLOR_TEXT_PRIMARY);

/**
 * @brief Crée un bouton d'icône circulaire
 */
lv_obj_t* createIconButton(lv_obj_t* parent, int16_t x, int16_t y, lv_coord_t size,
                           const char* icon, uint32_t color = LVGLStyles::COLOR_PRIMARY);

/**
 * @brief Crée une barre de navigation
 */
lv_obj_t* createNavBar(lv_obj_t* parent, const char* title);

/**
 * @brief Crée une modal (popup)
 */
lv_obj_t* createModal(lv_obj_t* parent, lv_coord_t width, lv_coord_t height, const char* title);

/**
 * @brief Ferme une modal
 */
void closeModal(lv_obj_t* modal);

/**
 * @brief Affiche un toast (notification temporaire)
 */
void showToast(lv_obj_t* parent, const char* message, uint32_t duration_ms = 3000);

/**
 * @brief Crée une liste scrollable
 */
lv_obj_t* createScrollableList(lv_obj_t* parent, int16_t x, int16_t y, lv_coord_t width, lv_coord_t height);

// Global screen transition helper
static constexpr uint16_t LVGL_FADE_MS = 0; // no transition, instant switch
void fade_to_screen(lv_obj_t* new_screen, uint16_t time_ms = LVGL_FADE_MS);

/**
 * @brief Ajoute un item à une liste
 */
lv_obj_t* addListItem(lv_obj_t* list, const char* text, const char* icon = nullptr);

#endif
