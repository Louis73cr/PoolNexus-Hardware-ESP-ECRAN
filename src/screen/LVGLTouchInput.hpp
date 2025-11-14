/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   LVGLTouchInput.hpp                             :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: Louis Croci <louis.croci@epitech.eu>       +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/14 21:09:48 by Louis Croci    #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/14 21:09:48 by Louis Croci    ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */
/**
 * @file LVGLTouchInput.hpp
 * @brief LVGL touch input interface definition.
 */

#ifndef LVGL_TOUCH_INPUT_HPP
#define LVGL_TOUCH_INPUT_HPP

#include <Arduino.h>
#include <lvgl.h>
#include "TouchController.hpp"

class LVGLTouchInput {
private:
    TouchController* touch;
    lv_indev_drv_t indev_drv;
    lv_indev_t* indev;

    static LVGLTouchInput* instance;
    static void read_touch(lv_indev_drv_t* drv, lv_indev_data_t* data);

public:
    explicit LVGLTouchInput(TouchController* touch);
    ~LVGLTouchInput();

    bool begin();

    static LVGLTouchInput* getInstance() { return instance; }
};

#endif
