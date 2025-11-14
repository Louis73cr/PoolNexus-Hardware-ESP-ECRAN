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
 * @file LevelProbePageLVGL.cpp
 * @brief Implementation of level probe page for LVGL UI.
 */

#include "LevelProbePageLVGL.hpp"
#include "utils/interface-utils-lvgl.hpp"
#include "../Translation/text.hpp"
#include <Arduino.h>

Text* LevelProbePageLVGL::globalTranslator = nullptr;

LevelProbePageLVGL::LevelProbePageLVGL(PageManager* mgr) 
    : LVGLPageBase("Sondes de niveaux", mgr),
      switch_enable(nullptr), label_enable(nullptr),
      slider_threshold(nullptr), label_threshold(nullptr), label_threshold_value(nullptr),
      probeEnabled(false), threshold(50) {
}

void LevelProbePageLVGL::build(PageType type) {
    LVGLPageBase::build(type);
    
    if (!content_area) {
        Serial.println("[LevelProbePageLVGL] ERROR: content_area is NULL!");
        return;
    }
    
    const char* title_text = globalTranslator ? 
        Text::Settings::product_level(globalTranslator->getCurrentLanguage()) : 
        "Sondes de niveaux";
    auto* title = createLabel(content_area, 0, 10, title_text, 
                             LVGLStyles::FONT_MEDIUM, LVGLStyles::COLOR_TEXT_PRIMARY);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 0);
    
    lv_obj_t* card_enable = createCard(content_area, 20, 60, 420, 70);
    const char* enable_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Activer les sondes" : "Enable probes") : 
        "Activer les sondes";
    label_enable = createLabel(card_enable, 20, 20, enable_text, 
                              LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    switch_enable = createSwitch(card_enable, 350, 20, probeEnabled);
    lv_obj_add_event_cb(switch_enable, on_switch_changed, LV_EVENT_VALUE_CHANGED, this);
    
    lv_obj_t* card_threshold = createCard(content_area, 20, 150, 420, 100);
    const char* threshold_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Seuil d'alerte (%)" : "Alert threshold (%)") : 
        "Seuil d'alerte (%)";
    label_threshold = createLabel(card_threshold, 20, 10, threshold_text, 
                                 LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    slider_threshold = createSlider(card_threshold, 20, 40, 380, 0, 100, threshold);
    lv_obj_add_event_cb(slider_threshold, on_slider_changed, LV_EVENT_VALUE_CHANGED, this);
    
    char threshold_str[16];
    snprintf(threshold_str, sizeof(threshold_str), "%d%%", threshold);
    label_threshold_value = createLabel(card_threshold, 350, 10, threshold_str, 
                                       LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_SECONDARY);
}

void LevelProbePageLVGL::on_switch_changed(lv_event_t* e) {
    LevelProbePageLVGL* page = (LevelProbePageLVGL*)e->user_data;
    if (!page) return;
    page->probeEnabled = lv_obj_has_state(page->switch_enable, LV_STATE_CHECKED);
    Serial.printf("[LevelProbePageLVGL] Probes %s\n", page->probeEnabled ? "enabled" : "disabled");
}

void LevelProbePageLVGL::on_slider_changed(lv_event_t* e) {
    LevelProbePageLVGL* page = (LevelProbePageLVGL*)e->user_data;
    if (!page || !page->label_threshold_value) return;
    page->threshold = lv_slider_get_value(page->slider_threshold);
    char threshold_str[16];
    snprintf(threshold_str, sizeof(threshold_str), "%d%%", page->threshold);
    lv_label_set_text(page->label_threshold_value, threshold_str);
    Serial.printf("[LevelProbePageLVGL] Threshold changed to %d%%\n", page->threshold);
}

