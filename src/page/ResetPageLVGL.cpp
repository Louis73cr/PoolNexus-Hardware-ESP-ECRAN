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
 * @file ResetPageLVGL.cpp
 * @brief Implementation of reset page for LVGL UI.
 */

#include "ResetPageLVGL.hpp"
#include "utils/interface-utils-lvgl.hpp"
#include "../Translation/text.hpp"
#include <Arduino.h>

Text* ResetPageLVGL::globalTranslator = nullptr;

ResetPageLVGL::ResetPageLVGL(PageManager* mgr) 
    : LVGLPageBase("Reinitialisation", mgr),
      btn_reset_settings(nullptr), btn_reset_all(nullptr) {
}

void ResetPageLVGL::build(PageType type) {
    LVGLPageBase::build(type);
    
    if (!content_area) {
        Serial.println("[ResetPageLVGL] ERROR: content_area is NULL!");
        return;
    }
    
    const char* title_text = globalTranslator ? 
        Text::Settings::reset(globalTranslator->getCurrentLanguage()) : 
        "Reinitialisation";
    auto* title = createLabel(content_area, 0, 10, title_text, 
                             LVGLStyles::FONT_MEDIUM, LVGLStyles::COLOR_TEXT_PRIMARY);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 0);
    
    const char* warning_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? 
         "Attention: Ces actions sont irreversibles!" : 
         "Warning: These actions are irreversible!") : 
        "Attention: Ces actions sont irreversibles!";
    auto* warning = createLabel(content_area, 0, 60, warning_text, 
                               LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_WARNING);
    lv_obj_align(warning, LV_ALIGN_TOP_MID, 0, 0);
    
    const char* reset_settings_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? 
         "Reinitialiser\nles parametres" : 
         "Reset\nSettings") : 
        "Reinitialiser\nles parametres";
    btn_reset_settings = createButton(content_area, 50, 120, 180, 100, reset_settings_text, 
                                     LVGLStyles::COLOR_WARNING);
    lv_obj_add_event_cb(btn_reset_settings, on_reset_settings, LV_EVENT_CLICKED, this);
    
    const char* reset_all_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? 
         "Reinitialiser\nTout" : 
         "Reset\nEverything") : 
        "Reinitialiser\nTout";
    btn_reset_all = createButton(content_area, 250, 120, 180, 100, reset_all_text, 
                                LVGLStyles::COLOR_DANGER);
    lv_obj_add_event_cb(btn_reset_all, on_reset_all, LV_EVENT_CLICKED, this);
}

void ResetPageLVGL::on_reset_settings(lv_event_t* e) {
    ResetPageLVGL* page = (ResetPageLVGL*)e->user_data;
    if (!page) return;
    Serial.println("[ResetPageLVGL] Reset settings requested");
    // TODO: Implémenter la réinitialisation des paramètres
}

void ResetPageLVGL::on_reset_all(lv_event_t* e) {
    ResetPageLVGL* page = (ResetPageLVGL*)e->user_data;
    if (!page) return;
    Serial.println("[ResetPageLVGL] Reset all requested");
    // TODO: Implémenter la réinitialisation complète
}

