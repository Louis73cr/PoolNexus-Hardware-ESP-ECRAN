/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   SwitchPageLVGL.hpp                             :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: Louis Croci <louis.croci@epitech.eu>       +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/14 21:10:51 by Louis Croci    #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/14 21:10:51 by Louis Croci    ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */
/**
 * @file ScreenPageLVGL.cpp
 * @brief Implementation of screen page for LVGL UI.
 */

#include "ScreenPageLVGL.hpp"
#include "utils/interface-utils-lvgl.hpp"
#include "../Translation/text.hpp"
#include <Arduino.h>

Text* ScreenPageLVGL::globalTranslator = nullptr;

ScreenPageLVGL::ScreenPageLVGL(PageManager* mgr) 
    : LVGLPageBase("Ecran", mgr),
      slider_brightness(nullptr), label_brightness(nullptr), label_brightness_value(nullptr),
      slider_timeout(nullptr), label_timeout(nullptr), label_timeout_value(nullptr),
      brightness(80), screenTimeout(30) {
}

void ScreenPageLVGL::build(PageType type) {
    LVGLPageBase::build(type);
    
    if (!content_area) {
        Serial.println("[ScreenPageLVGL] ERROR: content_area is NULL!");
        return;
    }
    
    // Titre
    const char* title_text = globalTranslator ? 
        Text::Settings::screen(globalTranslator->getCurrentLanguage()) : 
        "Ecran";
    auto* title = createLabel(content_area, 0, 10, title_text, 
                             LVGLStyles::FONT_MEDIUM, LVGLStyles::COLOR_TEXT_PRIMARY);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 0);
    
    // Carte pour la luminosité
    lv_obj_t* card_brightness = createCard(content_area, 20, 60, 420, 100);
    const char* brightness_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Luminosité (%)" : "Brightness (%)") : 
        "Luminosité (%)";
    label_brightness = createLabel(card_brightness, 20, 10, brightness_text, 
                                  LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    slider_brightness = createSlider(card_brightness, 20, 40, 380, 0, 100, brightness);
    lv_obj_add_event_cb(slider_brightness, on_brightness_changed, LV_EVENT_VALUE_CHANGED, this);
    
    char brightness_str[16];
    snprintf(brightness_str, sizeof(brightness_str), "%d%%", brightness);
    label_brightness_value = createLabel(card_brightness, 350, 10, brightness_str, 
                                        LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_SECONDARY);
    
    // Carte pour le timeout d'écran
    lv_obj_t* card_timeout = createCard(content_area, 20, 180, 420, 100);
    const char* timeout_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Timeout écran (sec)" : "Screen timeout (sec)") : 
        "Timeout écran (sec)";
    label_timeout = createLabel(card_timeout, 20, 10, timeout_text, 
                               LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    slider_timeout = createSlider(card_timeout, 20, 40, 380, 5, 300, screenTimeout);
    lv_obj_add_event_cb(slider_timeout, on_timeout_changed, LV_EVENT_VALUE_CHANGED, this);
    
    char timeout_str[16];
    snprintf(timeout_str, sizeof(timeout_str), "%d sec", screenTimeout);
    label_timeout_value = createLabel(card_timeout, 350, 10, timeout_str, 
                                     LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_SECONDARY);
}

void ScreenPageLVGL::on_brightness_changed(lv_event_t* e) {
    ScreenPageLVGL* page = (ScreenPageLVGL*)e->user_data;
    if (!page || !page->label_brightness_value) return;
    page->brightness = lv_slider_get_value(page->slider_brightness);
    char brightness_str[16];
    snprintf(brightness_str, sizeof(brightness_str), "%d%%", page->brightness);
    lv_label_set_text(page->label_brightness_value, brightness_str);
    Serial.printf("[ScreenPageLVGL] Brightness changed to %d%%\n", page->brightness);
    // TODO: Appliquer la luminosité à l'écran
}

void ScreenPageLVGL::on_timeout_changed(lv_event_t* e) {
    ScreenPageLVGL* page = (ScreenPageLVGL*)e->user_data;
    if (!page || !page->label_timeout_value) return;
    page->screenTimeout = lv_slider_get_value(page->slider_timeout);
    char timeout_str[16];
    snprintf(timeout_str, sizeof(timeout_str), "%d sec", page->screenTimeout);
    lv_label_set_text(page->label_timeout_value, timeout_str);
    Serial.printf("[ScreenPageLVGL] Screen timeout changed to %d seconds\n", page->screenTimeout);
}

