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
 * @file MainDisplayPageLVGL.hpp
 * @brief Page principale avec LVGL
 */

#ifndef MAIN_DISPLAY_PAGE_LVGL_HPP
#define MAIN_DISPLAY_PAGE_LVGL_HPP

#include <lvgl.h>
#include "utils/Page.hpp"
#include "utils/LVGLPageBase.hpp"
#include "utils/PageManager.hpp"

class MainDisplayPageLVGL : public Page {
private:
    PageManager* pageManager;

    lv_obj_t* screen;
    lv_obj_t* label_ph;
    lv_obj_t* label_redox;
    lv_obj_t* label_temp;
    lv_obj_t* btn_power;
    lv_obj_t* btn_pump;
    lv_obj_t* btn_alert;
    lv_obj_t* btn_settings;
    
    bool isPowerOn;
    bool isPumpOn;
    int nextPage;

    static void on_power_clicked(lv_event_t* e);
    static void on_pump_clicked(lv_event_t* e);
    static void on_alert_clicked(lv_event_t* e);
    static void on_settings_clicked(lv_event_t* e);

public:
    MainDisplayPageLVGL(PageManager* mgr);
    ~MainDisplayPageLVGL();

    void create();
    void show();
    void updateValues(float ph, float redox, float temp);
};


#endif
