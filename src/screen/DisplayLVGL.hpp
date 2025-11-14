/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   DisplayLVGL.hpp                                :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: Louis Croci <louis.croci@epitech.eu>       +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/14 21:10:06 by Louis Croci    #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/14 21:10:06 by Louis Croci    ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */

/**
 * @file DisplayLVGL.hpp
 * @brief Classe Display adaptée pour LVGL
 */

#ifndef DISPLAY_LVGL_HPP
#define DISPLAY_LVGL_HPP

#include <Arduino.h>
#include <lvgl.h>
#include <Arduino_GFX_Library.h>

class DisplayLVGL {
private:
    // Configuration matérielle QSPI
    static constexpr int PIN_CS = 45;
    static constexpr int PIN_SCK = 47;
    static constexpr int PIN_MOSI = 21;
    static constexpr int PIN_MISO = 48;
    static constexpr int PIN_DC = 40;
    static constexpr int PIN_RST = 39;
    static constexpr int PIN_BL = 1;
    
    static constexpr int WIDTH_PORTRAIT = 320;
    static constexpr int HEIGHT_PORTRAIT = 480;
    
    Arduino_ESP32QSPI* bus;
    Arduino_AXS15231B* display;
    Arduino_Canvas* canvas;
    
    lv_disp_draw_buf_t draw_buf;
    lv_color_t* buf1;
    lv_color_t* buf2;
    lv_disp_drv_t disp_drv;
    lv_disp_t* disp;
    
    static DisplayLVGL* instance;
    
    static void display_flush(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p);
    
public:
    DisplayLVGL();
    ~DisplayLVGL();
    
    bool begin();
    void loop();
    void setBacklight(bool enabled);
    
    lv_disp_t* getDisplay() { return disp; }
    
    static DisplayLVGL* getInstance() { return instance; }
};

#endif
