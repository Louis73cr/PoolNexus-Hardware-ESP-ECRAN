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
 * @file SwitchPageLVGL.cpp
 * @brief Page de paramètres des interrupteurs
 */

#include "SwitchPageLVGL.hpp"
#include "utils/interface-utils-lvgl.hpp"
#include "../Translation/text.hpp"
#include <Arduino.h>

Text* SwitchPageLVGL::globalTranslator = nullptr;

/**
 * @brief Constructor for SwitchPageLVGL.
 * @param mgr Optional PageManager pointer.
 */
SwitchPageLVGL::SwitchPageLVGL(PageManager* mgr) 
        : LVGLPageBase("Interrupteur", mgr),
            switch1_enabled(false), switch2_enabled(false), switch3_enabled(false) {
}

/**
 * @brief Builds the switch page UI.
 * @param type Page type (default: STANDARD).
 */
void SwitchPageLVGL::build(PageType type) {
    LVGLPageBase::build(type);
    
    if (!content_area) {
        Serial.println("[SwitchPageLVGL] ERROR: content_area is NULL!");
        return;
    }
    
    const char* title_text = globalTranslator ? 
        Text::Settings::switch_(globalTranslator->getCurrentLanguage()) : 
        "Interrupteur";
    auto* title = createLabel(content_area, 0, 10, title_text, 
                             LVGLStyles::FONT_MEDIUM, LVGLStyles::COLOR_TEXT_PRIMARY);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 0);
    
    lv_obj_t* card1 = createCard(content_area, 20, 60, 420, 70);
    const char* switch1_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Interrupteur 1" : "Switch 1") : 
        "Interrupteur 1";
    auto* label1 = createLabel(card1, 20, 20, switch1_text, 
                              LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    switch1 = createSwitch(card1, 350, 20, switch1_enabled);
    lv_obj_add_event_cb(switch1, on_switch1_changed, LV_EVENT_VALUE_CHANGED, this);
    
    lv_obj_t* card2 = createCard(content_area, 20, 150, 420, 70);
    const char* switch2_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Interrupteur 2" : "Switch 2") : 
        "Interrupteur 2";
    auto* label2 = createLabel(card2, 20, 20, switch2_text, 
                              LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    switch2 = createSwitch(card2, 350, 20, switch2_enabled);
    lv_obj_add_event_cb(switch2, on_switch2_changed, LV_EVENT_VALUE_CHANGED, this);
    
    lv_obj_t* card3 = createCard(content_area, 20, 240, 420, 70);
    const char* switch3_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Interrupteur 3" : "Switch 3") : 
        "Interrupteur 3";
    auto* label3 = createLabel(card3, 20, 20, switch3_text, 
                              LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    switch3 = createSwitch(card3, 350, 20, switch3_enabled);
    lv_obj_add_event_cb(switch3, on_switch3_changed, LV_EVENT_VALUE_CHANGED, this);
}

/**
 * @brief Callback for switch 1 state change.
 * @param e LVGL event.
 */
void SwitchPageLVGL::on_switch1_changed(lv_event_t* e) {
    SwitchPageLVGL* page = (SwitchPageLVGL*)e->user_data;
    if (!page) return;
    page->switch1_enabled = lv_obj_has_state(page->switch1, LV_STATE_CHECKED);
    Serial.printf("[SwitchPageLVGL] Switch 1 %s\n", page->switch1_enabled ? "ON" : "OFF");
}

/**
 * @brief Callback for switch 2 state change.
 * @param e LVGL event.
 */
void SwitchPageLVGL::on_switch2_changed(lv_event_t* e) {
    SwitchPageLVGL* page = (SwitchPageLVGL*)e->user_data;
    if (!page) return;
    page->switch2_enabled = lv_obj_has_state(page->switch2, LV_STATE_CHECKED);
    Serial.printf("[SwitchPageLVGL] Switch 2 %s\n", page->switch2_enabled ? "ON" : "OFF");
}

/**
 * @brief Callback for switch 3 state change.
 * @param e LVGL event.
 */
void SwitchPageLVGL::on_switch3_changed(lv_event_t* e) {
    SwitchPageLVGL* page = (SwitchPageLVGL*)e->user_data;
    if (!page) return;
    page->switch3_enabled = lv_obj_has_state(page->switch3, LV_STATE_CHECKED);
    Serial.printf("[SwitchPageLVGL] Switch 3 %s\n", page->switch3_enabled ? "ON" : "OFF");
}

