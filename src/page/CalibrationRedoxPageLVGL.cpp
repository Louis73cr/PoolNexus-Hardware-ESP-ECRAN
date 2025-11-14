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
 * @file CalibrationRedoxPageLVGL.cpp
 * @brief Implementation of Redox calibration page for LVGL UI.
 */

#include "CalibrationRedoxPageLVGL.hpp"
#include "utils/interface-utils-lvgl.hpp"
#include "../Translation/text.hpp"
#include <Arduino.h>

Text* CalibrationRedoxPageLVGL::globalTranslator = nullptr;

CalibrationRedoxPageLVGL::CalibrationRedoxPageLVGL(PageManager* mgr) 
    : LVGLPageBase("Calibration Redox", mgr),
      btn_calibrate(nullptr), label_status(nullptr), current_redox(750.0) {
}

void CalibrationRedoxPageLVGL::build(PageType type) {
    LVGLPageBase::build(type);
    
    if (!content_area) {
        Serial.println("[CalibrationRedoxPageLVGL] ERROR: content_area is NULL!");
        return;
    }
    
    const char* title_text = globalTranslator ? 
        Text::Settings::calibration_Redox(globalTranslator->getCurrentLanguage()) : 
        "Calibration Redox";
    auto* title = createLabel(content_area, 0, 10, title_text, 
                             LVGLStyles::FONT_MEDIUM, LVGLStyles::COLOR_TEXT_PRIMARY);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 0);
    
    lv_obj_t* card_redox = createCard(content_area, 20, 60, 420, 70);
    const char* redox_label_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Redox actuel" : "Current Redox") : 
        "Redox actuel";
    auto* label_redox = createLabel(card_redox, 20, 20, redox_label_text, 
                                   LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    
    char redox_str[16];
    snprintf(redox_str, sizeof(redox_str), "%.0f mV", current_redox);
    label_status = createLabel(card_redox, 300, 20, redox_str, 
                              LVGLStyles::FONT_LARGE, LVGLStyles::COLOR_INFO);
    
    const char* calibrate_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Calibrer Redox" : "Calibrate Redox") : 
        "Calibrer Redox";
    btn_calibrate = createButton(content_area, 150, 150, 180, 80, calibrate_text, 
                                LVGLStyles::COLOR_PRIMARY);
    lv_obj_add_event_cb(btn_calibrate, on_calibrate, LV_EVENT_CLICKED, this);
}

void CalibrationRedoxPageLVGL::on_calibrate(lv_event_t* e) {
    CalibrationRedoxPageLVGL* page = (CalibrationRedoxPageLVGL*)e->user_data;
    if (!page) return;
    Serial.println("[CalibrationRedoxPageLVGL] Calibration Redox");
    // TODO: Implémenter la calibration
}

