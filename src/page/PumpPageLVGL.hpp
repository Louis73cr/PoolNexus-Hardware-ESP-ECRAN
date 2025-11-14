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
#ifndef PUMP_PAGE_LVGL_HPP
#define PUMP_PAGE_LVGL_HPP

#include "utils/LVGLPageBase.hpp"
#include "../Translation/text.hpp"

class PageManager;

class PumpPageLVGL : public LVGLPageBase, public Page {
private:
    static Text* globalTranslator;
    
    lv_obj_t* switch_enable;
    lv_obj_t* label_enable;
    lv_obj_t* slider_speed;
    lv_obj_t* label_speed;
    lv_obj_t* label_speed_value;
    
    bool pumpEnabled;
    int pumpSpeed;
    
    static void on_switch_changed(lv_event_t* e);
    static void on_slider_changed(lv_event_t* e);
    
public:
    PumpPageLVGL(PageManager* mgr = nullptr);
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
