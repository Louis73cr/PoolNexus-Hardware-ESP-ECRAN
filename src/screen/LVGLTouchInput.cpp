/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   LVGLTouchInput.cpp                             :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: Louis Croci <louis.croci@epitech.eu>       +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/14 21:09:59 by Louis Croci    #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/14 21:09:59 by Louis Croci    ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */
/**
 * @file LVGLTouchInput.cpp
 * @brief Implementation of LVGL touch input handling.
 */

#include "LVGLTouchInput.hpp"

LVGLTouchInput* LVGLTouchInput::instance = nullptr;

LVGLTouchInput::LVGLTouchInput(TouchController* touch)
    : touch(touch), indev(nullptr) {
    instance = this;
}

LVGLTouchInput::~LVGLTouchInput() {}

bool LVGLTouchInput::begin() {
    if (!touch) return false;

    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = read_touch;
    indev_drv.user_data = this;

    indev = lv_indev_drv_register(&indev_drv);
    if (!indev) {
        Serial.println("LVGL touch registration failed!");
        return false;
    }

    Serial.println("LVGL touch initialized!");
    return true;
}

void LVGLTouchInput::read_touch(lv_indev_drv_t* drv, lv_indev_data_t* data) {
    LVGLTouchInput* self = static_cast<LVGLTouchInput*>(drv->user_data);
    uint16_t x, y;
    bool touched = self->touch->getTouchPoint(x, y);

    if (touched) {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = x;
        data->point.y = y;

        static unsigned long lastPrint = 0;
        if (millis() - lastPrint > 500) {
            Serial.printf("[LVGL Touch] x=%d, y=%d\n", x, y);
            lastPrint = millis();
        }
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}
