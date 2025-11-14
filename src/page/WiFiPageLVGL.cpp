/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   WiFiPageLVGL.cpp                               :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: Louis Croci <louis.croci@epitech.eu>       +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/14 21:10:42 by Louis Croci    #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/14 21:10:42 by Louis Croci    ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */
/**
 * @file WiFiPageLVGL.cpp
 * @brief Implementation of WiFi page for LVGL UI.
 */

#include "WiFiPageLVGL.hpp"
#include "utils/interface-utils-lvgl.hpp"
#include "../Translation/text.hpp"
#include <Arduino.h>

Text* WiFiPageLVGL::globalTranslator = nullptr;

WiFiPageLVGL::WiFiPageLVGL(PageManager* mgr) 
    : LVGLPageBase("WiFi", mgr),
      switch_enable(nullptr), label_enable(nullptr),
      textarea_ssid(nullptr), label_ssid(nullptr),
      textarea_password(nullptr), label_password(nullptr),
      btn_connect(nullptr),
      wifiEnabled(false) {
}

void WiFiPageLVGL::build(PageType type) {
    LVGLPageBase::build(type);
    
    if (!content_area) {
        Serial.println("[WiFiPageLVGL] ERROR: content_area is NULL!");
        return;
    }
    
    const char* title_text = globalTranslator ? 
        Text::Settings::wifi(globalTranslator->getCurrentLanguage()) : 
        "WiFi";
    auto* title = createLabel(content_area, 0, 10, title_text, 
                             LVGLStyles::FONT_MEDIUM, LVGLStyles::COLOR_TEXT_PRIMARY);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 0);
    
    lv_obj_t* card_enable = createCard(content_area, 20, 60, 420, 70);
    const char* enable_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Activer WiFi" : "Enable WiFi") : 
        "Activer WiFi";
    label_enable = createLabel(card_enable, 20, 20, enable_text, 
                              LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    switch_enable = createSwitch(card_enable, 350, 20, wifiEnabled);
    lv_obj_add_event_cb(switch_enable, on_switch_changed, LV_EVENT_VALUE_CHANGED, this);
    
    lv_obj_t* card_ssid = createCard(content_area, 20, 150, 420, 80);
    const char* ssid_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Nom du réseau (SSID)" : "Network name (SSID)") : 
        "Nom du réseau (SSID)";
    label_ssid = createLabel(card_ssid, 20, 10, ssid_text, 
                            LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    textarea_ssid = createTextArea(card_ssid, 20, 35, 380, 35, "MonReseauWiFi");
    
    lv_obj_t* card_password = createCard(content_area, 20, 250, 420, 80);
    const char* password_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Mot de passe" : "Password") : 
        "Mot de passe";
    label_password = createLabel(card_password, 20, 10, password_text, 
                                LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    textarea_password = createTextArea(card_password, 20, 35, 380, 35, "");
    lv_textarea_set_password_mode(textarea_password, true);
    
    const char* connect_text = globalTranslator ? 
        (globalTranslator->getCurrentLanguage() == Text::Language::FRENCH ? "Se connecter" : "Connect") : 
        "Se connecter";
    btn_connect = createButton(content_area, 150, 350, 180, 50, connect_text, 
                              LVGLStyles::COLOR_SUCCESS);
    lv_obj_add_event_cb(btn_connect, on_connect, LV_EVENT_CLICKED, this);
}

void WiFiPageLVGL::on_switch_changed(lv_event_t* e) {
    WiFiPageLVGL* page = (WiFiPageLVGL*)e->user_data;
    if (!page) return;
    page->wifiEnabled = lv_obj_has_state(page->switch_enable, LV_STATE_CHECKED);
    Serial.printf("[WiFiPageLVGL] WiFi %s\n", page->wifiEnabled ? "enabled" : "disabled");
}

void WiFiPageLVGL::on_connect(lv_event_t* e) {
    WiFiPageLVGL* page = (WiFiPageLVGL*)e->user_data;
    if (!page) return;
    Serial.println("[WiFiPageLVGL] Connexion WiFi demandée");
    // TODO: Implémenter la connexion WiFi
}

