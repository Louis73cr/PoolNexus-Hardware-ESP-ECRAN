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
 * @file MainDisplayPageLVGL.cpp
 * @brief Implémentation page principale LVGL avec utilitaires
 */

#include "MainDisplayPageLVGL.hpp"
#include "utils/interface-utils-lvgl.hpp"
#include <Arduino.h>
#include <cstdio>
#include "../Translation/text.hpp"

MainDisplayPageLVGL::MainDisplayPageLVGL(PageManager* mgr)
    : pageManager(mgr), screen(nullptr), label_ph(nullptr), label_redox(nullptr), 
      label_temp(nullptr), btn_power(nullptr), btn_pump(nullptr), 
      btn_alert(nullptr), btn_settings(nullptr), isPowerOn(false), isPumpOn(false), nextPage(0)
{
}


MainDisplayPageLVGL::~MainDisplayPageLVGL() {
    if (screen) {
        lv_obj_del(screen);
    }
}

void MainDisplayPageLVGL::create() {
    screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_hex(LVGLStyles::COLOR_BACKGROUND), 0);
    
    lv_obj_t* card_ph = createMeasurementCard(screen, 10, 10, 140, 90, "pH", "7.2", 
                                     LVGLStyles::FONT_LARGE, LVGLStyles::COLOR_SUCCESS);
    
    lv_obj_t* card_redox = createMeasurementCard(screen, 170, 10, 140, 90, "Redox", "750 mV",
                                        LVGLStyles::FONT_MEDIUM, LVGLStyles::COLOR_INFO);
    
    lv_obj_t* card_temp = createMeasurementCard(screen, 330, 10, 140, 90, "Temp", "24.5°C",
                                       LVGLStyles::FONT_LARGE, LVGLStyles::COLOR_WARNING);
    
    label_ph = lv_obj_get_child(card_ph, 1);
    label_redox = lv_obj_get_child(card_redox, 1);
    label_temp = lv_obj_get_child(card_temp, 1);
    
    lv_obj_t* graph_area = createCard(screen, 10, 110, 460, 120);
    lv_obj_t* graph_label = createLabel(graph_area, 0, 0, "Historique pH/Redox", 
                                         LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_SECONDARY);
    lv_obj_center(graph_label);
    
    btn_power = createButton(screen, 10, 245, 100, 60, isPowerOn ? "POWER\nON" : "POWER\nOFF",
                             isPowerOn ? LVGLStyles::COLOR_SUCCESS : LVGLStyles::COLOR_DANGER);
    lv_obj_add_event_cb(btn_power, on_power_clicked, LV_EVENT_CLICKED, this);
    
    btn_pump = createButton(screen, 130, 245, 100, 60, isPumpOn ? "PUMP\nON" : "PUMP\nOFF",
                            isPumpOn ? LVGLStyles::COLOR_SUCCESS : 0x9E9E9E);
    lv_obj_add_event_cb(btn_pump, on_pump_clicked, LV_EVENT_CLICKED, this);
    
    btn_alert = createButton(screen, 250, 245, 100, 60, "ALERT", LVGLStyles::COLOR_WARNING);
    lv_obj_add_event_cb(btn_alert, on_alert_clicked, LV_EVENT_CLICKED, this);
    
    btn_settings = createButton(screen, 370, 245, 100, 60, "SETTINGS", LVGLStyles::COLOR_PRIMARY);
    lv_obj_add_event_cb(btn_settings, on_settings_clicked, LV_EVENT_CLICKED, this);
}

void MainDisplayPageLVGL::show() {
    Serial.println("[MainDisplayPageLVGL] show() appelé");
    if (screen) {
        fade_to_screen(screen, LVGL_FADE_MS);
    } else {
        Serial.println("[MainDisplayPageLVGL] screen est NULL !");
    }
}

void MainDisplayPageLVGL::updateValues(float ph, float redox, float temp) {
    char buf[32];
    Serial.println("[MainDisplayPageLVGL] updateValues() appelé");
    if (!label_ph || !label_redox || !label_temp) {
        Serial.println("[MainDisplayPageLVGL] Un ou plusieurs labels sont NULL !");
        return;
    }
    snprintf(buf, sizeof(buf), "%.1f", ph);
    lv_label_set_text(label_ph, buf);
    snprintf(buf, sizeof(buf), "%.0f mV", redox);
    lv_label_set_text(label_redox, buf);
    snprintf(buf, sizeof(buf), "%.1f°C", temp);
    lv_label_set_text(label_temp, buf);
}

void MainDisplayPageLVGL::on_power_clicked(lv_event_t* e) {
    Serial.println("\n*** POWER BUTTON CLICKED ***");
    MainDisplayPageLVGL* page = (MainDisplayPageLVGL*)lv_event_get_user_data(e);
    page->isPowerOn = !page->isPowerOn;
    
    lv_obj_t* label = lv_obj_get_child(page->btn_power, 0);
    if (page->isPowerOn) {
        lv_obj_set_style_bg_color(page->btn_power, lv_color_hex(LVGLStyles::COLOR_SUCCESS), 0);
        lv_label_set_text(label, "POWER\nON");
    } else {
        lv_obj_set_style_bg_color(page->btn_power, lv_color_hex(LVGLStyles::COLOR_DANGER), 0);
        lv_label_set_text(label, "POWER\nOFF");
    }
    
    Serial.printf("Power: %s\n\n", page->isPowerOn ? "ON" : "OFF");
}

void MainDisplayPageLVGL::on_pump_clicked(lv_event_t* e) {
    Serial.println("\n*** PUMP BUTTON CLICKED ***");
    MainDisplayPageLVGL* page = (MainDisplayPageLVGL*)lv_event_get_user_data(e);
    page->isPumpOn = !page->isPumpOn;
    
    lv_obj_t* label = lv_obj_get_child(page->btn_pump, 0);
    if (page->isPumpOn) {
        lv_obj_set_style_bg_color(page->btn_pump, lv_color_hex(LVGLStyles::COLOR_SUCCESS), 0);
        lv_label_set_text(label, "PUMP\nON");
    } else {
        lv_obj_set_style_bg_color(page->btn_pump, lv_color_hex(0x9E9E9E), 0); // Gris
        lv_label_set_text(label, "PUMP\nOFF");
    }
    
    Serial.printf("Pump: %s\n\n", page->isPumpOn ? "ON" : "OFF");
}

void MainDisplayPageLVGL::on_alert_clicked(lv_event_t* e) {
    Serial.println("\n*** ALERT BUTTON CLICKED ***\n");
    // TODO: Navigate to alert page
}

void MainDisplayPageLVGL::on_settings_clicked(lv_event_t* e) {
    Serial.println("\n*** SETTINGS BUTTON CLICKED ***");

    MainDisplayPageLVGL* page = static_cast<MainDisplayPageLVGL*>(lv_event_get_user_data(e));

    page->pageManager->navigateToPage(PageID::PAGE_SETTINGS);
}

