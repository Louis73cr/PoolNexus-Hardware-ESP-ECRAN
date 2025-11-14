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
#ifndef CALIBRATION_REDOX_PAGE_LVGL_HPP
#define CALIBRATION_REDOX_PAGE_LVGL_HPP

#include "utils/LVGLPageBase.hpp"
#include "../Translation/text.hpp"

class PageManager;

class CalibrationRedoxPageLVGL : public LVGLPageBase, public Page {
private:
    static Text* globalTranslator;
    
    lv_obj_t* btn_calibrate;
    lv_obj_t* label_status;
    
    float current_redox;
    
    static void on_calibrate(lv_event_t* e);
    
public:
    CalibrationRedoxPageLVGL(PageManager* mgr = nullptr);
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
