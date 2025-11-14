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
 * @file CalibrationPHPageLVGL.cpp
 * @brief Implementation of pH calibration page for LVGL UI.
 */

#include "CalibrationPHPageLVGL.hpp"
#include "utils/interface-utils-lvgl.hpp"
#include "../Translation/text.hpp"
#include <Arduino.h>

Text* CalibrationPHPageLVGL::globalTranslator = nullptr;

CalibrationPHPageLVGL::CalibrationPHPageLVGL(PageManager* mgr) 
    : LVGLPageBase("Calibration pH", mgr),
      btn_calibrate_low(nullptr), btn_calibrate_mid(nullptr), btn_calibrate_high(nullptr),
      label_status(nullptr), current_ph(7.0) {
}

void CalibrationPHPageLVGL::build(PageType type) {
    LVGLPageBase::build(type);
    
    if (!content_area) {
        Serial.println("[CalibrationPHPageLVGL] ERROR: content_area is NULL!");
        return;
    }
    
    const char* title_text = globalTranslator ? 
        Text::Settings::calibration_pH(globalTranslator->getCurrentLanguage()) : 
        "Calibration pH";
    auto* title = createLabel(content_area, 0, 10, title_text, 
                             LVGLStyles::FONT_MEDIUM, LVGLStyles::COLOR_TEXT_PRIMARY);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 0);
    
    lv_obj_t* card_ph = createCard(content_area, 20, 60, 420, 70);
    const char* ph_label_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "pH actuel" : "Current pH") : 
        "pH actuel";
    auto* label_ph = createLabel(card_ph, 20, 20, ph_label_text, 
                                LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    
    char ph_str[16];
    snprintf(ph_str, sizeof(ph_str), "%.2f", current_ph);
    label_status = createLabel(card_ph, 300, 20, ph_str, 
                              LVGLStyles::FONT_LARGE, LVGLStyles::COLOR_PRIMARY);
    
    const char* low_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Point bas\n(pH 4.0)" : "Low point\n(pH 4.0)") : 
        "Point bas\n(pH 4.0)";
    btn_calibrate_low = createButton(content_area, 20, 150, 130, 80, low_text, 
                                    LVGLStyles::COLOR_INFO);
    lv_obj_add_event_cb(btn_calibrate_low, on_calibrate_low, LV_EVENT_CLICKED, this);
    
    const char* mid_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Point milieu\n(pH 7.0)" : "Mid point\n(pH 7.0)") : 
        "Point milieu\n(pH 7.0)";
    btn_calibrate_mid = createButton(content_area, 175, 150, 130, 80, mid_text, 
                                    LVGLStyles::COLOR_SUCCESS);
    lv_obj_add_event_cb(btn_calibrate_mid, on_calibrate_mid, LV_EVENT_CLICKED, this);
    
    const char* high_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Point haut\n(pH 10.0)" : "High point\n(pH 10.0)") : 
        "Point haut\n(pH 10.0)";
    btn_calibrate_high = createButton(content_area, 330, 150, 130, 80, high_text, 
                                     LVGLStyles::COLOR_WARNING);
    lv_obj_add_event_cb(btn_calibrate_high, on_calibrate_high, LV_EVENT_CLICKED, this);
}

void CalibrationPHPageLVGL::on_calibrate_low(lv_event_t* e) {
    CalibrationPHPageLVGL* page = (CalibrationPHPageLVGL*)e->user_data;
    if (!page) return;
    Serial.println("[CalibrationPHPageLVGL] Calibration point bas (pH 4.0)");
    // TODO: Implémenter la calibration
}

void CalibrationPHPageLVGL::on_calibrate_mid(lv_event_t* e) {
    CalibrationPHPageLVGL* page = (CalibrationPHPageLVGL*)e->user_data;
    if (!page) return;
    Serial.println("[CalibrationPHPageLVGL] Calibration point milieu (pH 7.0)");
    // TODO: Implémenter la calibration
}

void CalibrationPHPageLVGL::on_calibrate_high(lv_event_t* e) {
    CalibrationPHPageLVGL* page = (CalibrationPHPageLVGL*)e->user_data;
    if (!page) return;
    Serial.println("[CalibrationPHPageLVGL] Calibration point haut (pH 10.0)");
    // TODO: Implémenter la calibration
}

