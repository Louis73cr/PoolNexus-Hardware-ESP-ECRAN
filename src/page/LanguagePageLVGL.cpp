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
 * @file LanguagePageLVGL.cpp
 * @brief Implementation of language selection page for LVGL UI.
 */

#include "LanguagePageLVGL.hpp"
#include "utils/interface-utils-lvgl.hpp"
#include <Arduino.h>

Text* LanguagePageLVGL::globalTranslator = nullptr;

void LanguagePageLVGL::build(PageType type) {
    LVGLPageBase::build(type);
    
    if (!globalTranslator) return;
    
    auto* label = createLabel(content_area, 0, 10, "Selection de la langue", 
                              LVGLStyles::FONT_MEDIUM, LVGLStyles::COLOR_TEXT_PRIMARY);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);
    
    int y_offset = 60;
    for (uint8_t i = 0; i < static_cast<uint8_t>(Text::Language::LANGUAGE_COUNT); i++) {
        Text::Language lang = static_cast<Text::Language>(i);
        
        lv_obj_t* btn = createCard(content_area, 20, y_offset, 400, 60);
        lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_user_data(btn, (void*)(intptr_t)lang);
        lv_obj_add_event_cb(btn, on_language_clicked, LV_EVENT_CLICKED, this);
        
        auto* lang_label = createLabel(btn, 20, 20, globalTranslator->getLanguageName(lang),
                                       LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
        
        if (globalTranslator->getCurrentLanguage() == lang) {
            lv_obj_set_style_border_color(btn, lv_color_hex(LVGLStyles::COLOR_PRIMARY), 0);
            lv_obj_set_style_border_width(btn, 3, 0);
        }
        
        y_offset += 70;
    }
}

void LanguagePageLVGL::on_language_clicked(lv_event_t* e) {
    LanguagePageLVGL* page = (LanguagePageLVGL*)e->user_data;
    lv_obj_t* card = lv_event_get_target(e);
    
    if (!globalTranslator) return;
    
    Text::Language selected = (Text::Language)(intptr_t)lv_obj_get_user_data(card);
    
    globalTranslator->setLanguage(selected);
    
    Serial.printf("Langue changée: %s\n", globalTranslator->getLanguageName(selected));
    
    lv_obj_t* parent = lv_obj_get_parent(card);
    for (uint32_t i = 0; i < lv_obj_get_child_cnt(parent); i++) {
        lv_obj_t* child = lv_obj_get_child(parent, i);
        if (lv_obj_has_flag(child, LV_OBJ_FLAG_CLICKABLE)) {
            lv_obj_set_style_border_width(child, 0, 0);
        }
    }
    
    lv_obj_set_style_border_color(card, lv_color_hex(LVGLStyles::COLOR_PRIMARY), 0);
    lv_obj_set_style_border_width(card, 3, 0);
    
    // TODO: Déclencher un rafraîchissement de l'interface pour mettre à jour tous les textes
}
