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
 * @file PumpPageLVGL.cpp
 * @brief Implementation of pump page for LVGL UI.
 */

#include "PumpPageLVGL.hpp"
#include "utils/interface-utils-lvgl.hpp"
#include <Arduino.h>

Text* PumpPageLVGL::globalTranslator = nullptr;

PumpPageLVGL::PumpPageLVGL(PageManager* mgr) 
    : LVGLPageBase("Pompe", mgr),
      switch_enable(nullptr), label_enable(nullptr), slider_speed(nullptr), 
      label_speed(nullptr), label_speed_value(nullptr), pumpEnabled(false), pumpSpeed(50) {
}

void PumpPageLVGL::build(PageType type) {
    if (!globalTranslator) {
        Serial.println("[PumpPageLVGL] WARNING: globalTranslator is NULL!");
    }
    
    LVGLPageBase::build(type);
    
    if (!content_area) {
        Serial.println("[PumpPageLVGL] ERROR: content_area is NULL!");
        return;
    }
    
    const char* title_text = globalTranslator ? Text::Settings::pump(globalTranslator->getCurrentLanguage()) : "Pompe";
    auto* title = createLabel(content_area, 0, 10, title_text, 
                             LVGLStyles::FONT_MEDIUM, LVGLStyles::COLOR_TEXT_PRIMARY);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 0);
    
    lv_obj_t* card_enable = createCard(content_area, 20, 60, 420, 70);
    
    const char* enable_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Activer la pompe" : "Enable pump") : 
        "Activer la pompe";
    label_enable = createLabel(card_enable, 20, 20, enable_text, 
                              LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    
    switch_enable = createSwitch(card_enable, 350, 20, pumpEnabled);
    lv_obj_add_event_cb(switch_enable, on_switch_changed, LV_EVENT_VALUE_CHANGED, this);
    
    lv_obj_t* card_speed = createCard(content_area, 20, 150, 420, 100);
    
    const char* speed_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Vitesse" : "Speed") : 
        "Vitesse";
    label_speed = createLabel(card_speed, 20, 10, speed_text, 
                             LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    
    slider_speed = createSlider(card_speed, 20, 40, 380, 0, 100, pumpSpeed);
    lv_obj_add_event_cb(slider_speed, on_slider_changed, LV_EVENT_VALUE_CHANGED, this);
    
    char speed_str[16];
    snprintf(speed_str, sizeof(speed_str), "%d%%", pumpSpeed);
    label_speed_value = createLabel(card_speed, 350, 10, speed_str, 
                                   LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_SECONDARY);
}

void PumpPageLVGL::on_switch_changed(lv_event_t* e) {
    PumpPageLVGL* page = (PumpPageLVGL*)e->user_data;
    if (!page) return;
    
    page->pumpEnabled = lv_obj_has_state(page->switch_enable, LV_STATE_CHECKED);
    Serial.printf("[PumpPageLVGL] Pump %s\n", page->pumpEnabled ? "enabled" : "disabled");
}

void PumpPageLVGL::on_slider_changed(lv_event_t* e) {
    PumpPageLVGL* page = (PumpPageLVGL*)e->user_data;
    if (!page || !page->label_speed_value) return;
    
    page->pumpSpeed = lv_slider_get_value(page->slider_speed);
    char speed_str[16];
    snprintf(speed_str, sizeof(speed_str), "%d%%", page->pumpSpeed);
    lv_label_set_text(page->label_speed_value, speed_str);
    Serial.printf("[PumpPageLVGL] Speed changed to %d%%\n", page->pumpSpeed);
}

