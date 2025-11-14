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
 * @file LockPageLVGL.cpp
 * @brief Implementation of lock page for LVGL UI.
 */

#include "LockPageLVGL.hpp"
#include "utils/interface-utils-lvgl.hpp"
#include "../Translation/text.hpp"
#include <Arduino.h>

Text* LockPageLVGL::globalTranslator = nullptr;

LockPageLVGL::LockPageLVGL(PageManager* mgr) 
    : LVGLPageBase("Verrouillage", mgr),
      switch_lock(nullptr), label_lock(nullptr),
      slider_timeout(nullptr), label_timeout(nullptr), label_timeout_value(nullptr),
      screenLocked(false), timeoutMinutes(5) {
}

void LockPageLVGL::build(PageType type) {
    LVGLPageBase::build(type);
    
    if (!content_area) {
        Serial.println("[LockPageLVGL] ERROR: content_area is NULL!");
        return;
    }
    
    const char* title_text = globalTranslator ? 
        Text::Settings::lock_screen(globalTranslator->getCurrentLanguage()) : 
        "Verrouillage";
    auto* title = createLabel(content_area, 0, 10, title_text, 
                             LVGLStyles::FONT_MEDIUM, LVGLStyles::COLOR_TEXT_PRIMARY);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 0);
    
    lv_obj_t* card_lock = createCard(content_area, 20, 60, 420, 70);
    const char* lock_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Verrouiller l'écran" : "Lock screen") : 
        "Verrouiller l'écran";
    label_lock = createLabel(card_lock, 20, 20, lock_text, 
                            LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    switch_lock = createSwitch(card_lock, 350, 20, screenLocked);
    lv_obj_add_event_cb(switch_lock, on_switch_changed, LV_EVENT_VALUE_CHANGED, this);
    
    lv_obj_t* card_timeout = createCard(content_area, 20, 150, 420, 100);
    const char* timeout_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Délai de verrouillage (min)" : "Lock timeout (min)") : 
        "Délai de verrouillage (min)";
    label_timeout = createLabel(card_timeout, 20, 10, timeout_text, 
                               LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    slider_timeout = createSlider(card_timeout, 20, 40, 380, 1, 30, timeoutMinutes);
    lv_obj_add_event_cb(slider_timeout, on_slider_changed, LV_EVENT_VALUE_CHANGED, this);
    
    char timeout_str[16];
    snprintf(timeout_str, sizeof(timeout_str), "%d min", timeoutMinutes);
    label_timeout_value = createLabel(card_timeout, 350, 10, timeout_str, 
                                     LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_SECONDARY);
}

void LockPageLVGL::on_switch_changed(lv_event_t* e) {
    LockPageLVGL* page = (LockPageLVGL*)e->user_data;
    if (!page) return;
    page->screenLocked = lv_obj_has_state(page->switch_lock, LV_STATE_CHECKED);
    Serial.printf("[LockPageLVGL] Screen lock %s\n", page->screenLocked ? "enabled" : "disabled");
}

void LockPageLVGL::on_slider_changed(lv_event_t* e) {
    LockPageLVGL* page = (LockPageLVGL*)e->user_data;
    if (!page || !page->label_timeout_value) return;
    page->timeoutMinutes = lv_slider_get_value(page->slider_timeout);
    char timeout_str[16];
    snprintf(timeout_str, sizeof(timeout_str), "%d min", page->timeoutMinutes);
    lv_label_set_text(page->label_timeout_value, timeout_str);
    Serial.printf("[LockPageLVGL] Timeout changed to %d minutes\n", page->timeoutMinutes);
}

