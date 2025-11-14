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
 * @file PoolFillPageLVGL.cpp
 * @brief Implementation of pool fill page for LVGL UI.
 */

#include "PoolFillPageLVGL.hpp"
#include "utils/interface-utils-lvgl.hpp"
#include "../Translation/text.hpp"
#include <Arduino.h>

Text* PoolFillPageLVGL::globalTranslator = nullptr;

PoolFillPageLVGL::PoolFillPageLVGL(PageManager* mgr) 
    : LVGLPageBase("Remplissage Piscine", mgr),
      switch_auto(nullptr), label_auto(nullptr),
      slider_level(nullptr), label_level(nullptr), label_level_value(nullptr),
      autoFillEnabled(false), fillLevel(80) {
}

void PoolFillPageLVGL::build(PageType type) {
    LVGLPageBase::build(type);
    
    if (!content_area) {
        Serial.println("[PoolFillPageLVGL] ERROR: content_area is NULL!");
        return;
    }
    
    const char* title_text = globalTranslator ? 
        Text::Settings::pool_fill(globalTranslator->getCurrentLanguage()) : 
        "Remplissage Piscine";
    auto* title = createLabel(content_area, 0, 10, title_text, 
                             LVGLStyles::FONT_MEDIUM, LVGLStyles::COLOR_TEXT_PRIMARY);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 0);
    
    lv_obj_t* card_auto = createCard(content_area, 20, 60, 420, 70);
    const char* auto_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Remplissage automatique" : "Auto fill") : 
        "Remplissage automatique";
    label_auto = createLabel(card_auto, 20, 20, auto_text, 
                            LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    switch_auto = createSwitch(card_auto, 350, 20, autoFillEnabled);
    lv_obj_add_event_cb(switch_auto, on_switch_changed, LV_EVENT_VALUE_CHANGED, this);
    
    lv_obj_t* card_level = createCard(content_area, 20, 150, 420, 100);
    const char* level_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Niveau cible (%)" : "Target level (%)") : 
        "Niveau cible (%)";
    label_level = createLabel(card_level, 20, 10, level_text, 
                             LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    slider_level = createSlider(card_level, 20, 40, 380, 0, 100, fillLevel);
    lv_obj_add_event_cb(slider_level, on_slider_changed, LV_EVENT_VALUE_CHANGED, this);
    
    char level_str[16];
    snprintf(level_str, sizeof(level_str), "%d%%", fillLevel);
    label_level_value = createLabel(card_level, 350, 10, level_str, 
                                   LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_SECONDARY);
}

void PoolFillPageLVGL::on_switch_changed(lv_event_t* e) {
    PoolFillPageLVGL* page = (PoolFillPageLVGL*)e->user_data;
    if (!page) return;
    page->autoFillEnabled = lv_obj_has_state(page->switch_auto, LV_STATE_CHECKED);
    Serial.printf("[PoolFillPageLVGL] Auto fill %s\n", page->autoFillEnabled ? "enabled" : "disabled");
}

void PoolFillPageLVGL::on_slider_changed(lv_event_t* e) {
    PoolFillPageLVGL* page = (PoolFillPageLVGL*)e->user_data;
    if (!page || !page->label_level_value) return;
    page->fillLevel = lv_slider_get_value(page->slider_level);
    char level_str[16];
    snprintf(level_str, sizeof(level_str), "%d%%", page->fillLevel);
    lv_label_set_text(page->label_level_value, level_str);
    Serial.printf("[PoolFillPageLVGL] Fill level changed to %d%%\n", page->fillLevel);
}

