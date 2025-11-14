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
 * @file CloudPageLVGL.cpp
 * @brief Implementation of Cloud page for LVGL UI.
 */

#include "CloudPageLVGL.hpp"
#include "utils/interface-utils-lvgl.hpp"
#include "../Translation/text.hpp"
#include <Arduino.h>

Text* CloudPageLVGL::globalTranslator = nullptr;

CloudPageLVGL::CloudPageLVGL(PageManager* mgr) 
    : LVGLPageBase("Cloud", mgr),
      switch_enable(nullptr), label_enable(nullptr), 
      textarea_url(nullptr), label_url(nullptr),
      cloudEnabled(false) {
}

void CloudPageLVGL::build(PageType type) {
    LVGLPageBase::build(type);
    
    if (!content_area) {
        Serial.println("[CloudPageLVGL] ERROR: content_area is NULL!");
        return;
    }
    
    const char* title_text = globalTranslator ? 
        Text::Settings::cloud(globalTranslator->getCurrentLanguage()) : 
        "Cloud";
    auto* title = createLabel(content_area, 0, 10, title_text, 
                             LVGLStyles::FONT_MEDIUM, LVGLStyles::COLOR_TEXT_PRIMARY);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 0);
    
    lv_obj_t* card_enable = createCard(content_area, 20, 60, 420, 70);
    const char* enable_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Activer Cloud" : "Enable Cloud") : 
        "Activer Cloud";
    label_enable = createLabel(card_enable, 20, 20, enable_text, 
                              LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    switch_enable = createSwitch(card_enable, 350, 20, cloudEnabled);
    lv_obj_add_event_cb(switch_enable, on_switch_changed, LV_EVENT_VALUE_CHANGED, this);
    
    lv_obj_t* card_url = createCard(content_area, 20, 150, 420, 100);
    const char* url_label_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "URL du serveur" : "Server URL") : 
        "URL du serveur";
    label_url = createLabel(card_url, 20, 10, url_label_text, 
                           LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    textarea_url = createTextArea(card_url, 20, 35, 380, 50, "https://example.com/api");
}

void CloudPageLVGL::on_switch_changed(lv_event_t* e) {
    CloudPageLVGL* page = (CloudPageLVGL*)e->user_data;
    if (!page) return;
    page->cloudEnabled = lv_obj_has_state(page->switch_enable, LV_STATE_CHECKED);
    Serial.printf("[CloudPageLVGL] Cloud %s\n", page->cloudEnabled ? "enabled" : "disabled");
}

