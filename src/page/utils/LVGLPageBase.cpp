/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   LVGLPageBase.cpp                               :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: Louis Croci <louis.croci@epitech.eu>       +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/14 21:26:21 by Louis Croci    #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/14 21:26:21 by Louis Croci    ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */
/**
 * @file LVGLPageBase.cpp
 * @brief Base class implementation for LVGL pages.
 */

#include "LVGLPageBase.hpp"
#include "PageManager.hpp"
#include <iostream>

LVGLPageBase::LVGLPageBase(const char* titleText, PageManager* mgr)
    : screen(nullptr), navbar(nullptr), content_area(nullptr), backButton(nullptr),
      nextPageId(-1), title(titleText), pageManager(mgr) {}

LVGLPageBase::~LVGLPageBase() {
    if (screen) lv_obj_del(screen);
}

void LVGLPageBase::build(PageType type) {
    if (screen) return;
    screen = lv_obj_create(nullptr);

    switch(type) {
        case HOME: {
            lv_obj_set_style_bg_color(screen, lv_color_hex(LVGLStyles::COLOR_BACKGROUND), 0);
            break;
        }
        case STANDARD: {
            lv_obj_set_style_bg_color(screen, lv_color_hex(LVGLStyles::COLOR_BACKGROUND), 0);
            navbar = createNavBar(screen, title ? title : "");
            backButton = createButton(navbar, 0, 0, 50, 50, "X", LVGLStyles::COLOR_DANGER, 0);
            lv_obj_align(backButton, LV_ALIGN_TOP_LEFT, -10, -10);
            lv_obj_add_flag(backButton, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_add_event_cb(backButton, on_back_clicked, LV_EVENT_CLICKED, this);
            content_area = createScrollableList(screen, 10, 60, 460, 200);
            break;
        }
        case ALERT: {
            lv_obj_set_style_bg_color(screen, lv_color_hex(LVGLStyles::COLOR_DANGER), 0);
            navbar = createNavBar(screen, title ? title : "");
            lv_obj_add_flag(navbar, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_add_event_cb(navbar, on_back_clicked, LV_EVENT_CLICKED, this);
            content_area = createScrollableList(screen, 10, 60, 460, 200);
            break;
        }
        case INFO: {
            lv_obj_set_style_bg_color(screen, lv_color_hex(LVGLStyles::COLOR_INFO), 0);
            navbar = createNavBar(screen, title ? title : "");
            lv_obj_add_flag(navbar, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_add_event_cb(navbar, on_back_clicked, LV_EVENT_CLICKED, this);
            content_area = createScrollableList(screen, 10, 60, 460, 200);
            break;
        }
    }
}

void LVGLPageBase::show() {
    if (!screen) {
        Serial.println("[LVGLPageBase] screen is NULL, calling build()");
        build();
    }
    if (!screen) {
        Serial.println("[LVGLPageBase] ERROR: screen is still NULL after build()!");
        return;
    }
    fade_to_screen(screen, LVGL_FADE_MS);
}

void LVGLPageBase::on_back_clicked(lv_event_t* e) {
    auto* self = static_cast<LVGLPageBase*>(e->user_data);
    if (!self || !self->pageManager) return;
    
    self->pageManager->navigateToPage(PageID::PAGE_SETTINGS);
}
