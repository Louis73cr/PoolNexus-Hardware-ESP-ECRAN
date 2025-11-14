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
 * @file MQTTPageLVGL.cpp
 * @brief Implementation of MQTT page for LVGL UI.
 */

#include "MQTTPageLVGL.hpp"
#include "utils/interface-utils-lvgl.hpp"
#include "../Translation/text.hpp"
#include <Arduino.h>

Text* MQTTPageLVGL::globalTranslator = nullptr;

MQTTPageLVGL::MQTTPageLVGL(PageManager* mgr) 
    : LVGLPageBase("MQTT", mgr),
      switch_enable(nullptr), label_enable(nullptr),
      textarea_broker(nullptr), label_broker(nullptr),
      textarea_port(nullptr), label_port(nullptr),
      textarea_topic(nullptr), label_topic(nullptr),
      btn_test(nullptr),
      mqttEnabled(false) {
}

void MQTTPageLVGL::build(PageType type) {
    LVGLPageBase::build(type);
    
    if (!content_area) {
        Serial.println("[MQTTPageLVGL] ERROR: content_area is NULL!");
        return;
    }
    
    auto* title = createLabel(content_area, 0, 10, "MQTT", 
                             LVGLStyles::FONT_MEDIUM, LVGLStyles::COLOR_TEXT_PRIMARY);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 0);
    
    lv_obj_t* card_enable = createCard(content_area, 20, 60, 420, 70);
    const char* enable_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Activer MQTT" : "Enable MQTT") : 
        "Activer MQTT";
    label_enable = createLabel(card_enable, 20, 20, enable_text, 
                              LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    switch_enable = createSwitch(card_enable, 350, 20, mqttEnabled);
    lv_obj_add_event_cb(switch_enable, on_switch_changed, LV_EVENT_VALUE_CHANGED, this);
    
    lv_obj_t* card_broker = createCard(content_area, 20, 150, 420, 80);
    const char* broker_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Serveur MQTT" : "MQTT Server") : 
        "Serveur MQTT";
    label_broker = createLabel(card_broker, 20, 10, broker_text, 
                              LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    textarea_broker = createTextArea(card_broker, 20, 35, 380, 35, "mqtt.example.com");
    
    lv_obj_t* card_port = createCard(content_area, 20, 250, 200, 80);
    const char* port_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Port" : "Port") : 
        "Port";
    label_port = createLabel(card_port, 20, 10, port_text, 
                            LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    textarea_port = createTextArea(card_port, 20, 35, 160, 35, "1883");
    
    lv_obj_t* card_topic = createCard(content_area, 240, 250, 200, 80);
    const char* topic_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Topic" : "Topic") : 
        "Topic";
    label_topic = createLabel(card_topic, 20, 10, topic_text, 
                             LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    textarea_topic = createTextArea(card_topic, 20, 35, 160, 35, "poolnexus/data");
    
    const char* test_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Tester connexion" : "Test connection") : 
        "Tester connexion";
    btn_test = createButton(content_area, 150, 350, 180, 50, test_text, 
                           LVGLStyles::COLOR_INFO);
    lv_obj_add_event_cb(btn_test, on_test, LV_EVENT_CLICKED, this);
}

void MQTTPageLVGL::on_switch_changed(lv_event_t* e) {
    MQTTPageLVGL* page = (MQTTPageLVGL*)e->user_data;
    if (!page) return;
    page->mqttEnabled = lv_obj_has_state(page->switch_enable, LV_STATE_CHECKED);
    Serial.printf("[MQTTPageLVGL] MQTT %s\n", page->mqttEnabled ? "enabled" : "disabled");
}

void MQTTPageLVGL::on_test(lv_event_t* e) {
    MQTTPageLVGL* page = (MQTTPageLVGL*)e->user_data;
    if (!page) return;
    Serial.println("[MQTTPageLVGL] Test de connexion MQTT");
}

