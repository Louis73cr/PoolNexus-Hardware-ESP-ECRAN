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
#ifndef MQTT_PAGE_LVGL_HPP
#define MQTT_PAGE_LVGL_HPP

#include "utils/LVGLPageBase.hpp"
#include "utils/Page.hpp"
#include "../Translation/text.hpp"

class PageManager;

class MQTTPageLVGL : public LVGLPageBase, public Page {
private:
    static Text* globalTranslator;
    
    lv_obj_t* switch_enable;
    lv_obj_t* label_enable;
    lv_obj_t* textarea_broker;
    lv_obj_t* label_broker;
    lv_obj_t* textarea_port;
    lv_obj_t* label_port;
    lv_obj_t* textarea_topic;
    lv_obj_t* label_topic;
    lv_obj_t* btn_test;
    
    bool mqttEnabled;
    
    static void on_switch_changed(lv_event_t* e);
    static void on_test(lv_event_t* e);
    
public:
    MQTTPageLVGL(PageManager* mgr = nullptr);
    void build(PageType type = STANDARD) override;
    void show() override { LVGLPageBase::show(); }
    void create() override {
        if (!screen) {
            build(STANDARD);
        }
    }
    
    static void setGlobalTranslator(Text* translator) {
        globalTranslator = translator;
    }
};

#endif
