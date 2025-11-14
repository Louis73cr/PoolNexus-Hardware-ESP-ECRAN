/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   interface-utils-lvgl.cpp                       :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: Louis Croci <louis.croci@epitech.eu>       +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/14 21:26:49 by Louis Croci    #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/14 21:26:49 by Louis Croci    ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */

/**
 * @file interface-utils-lvgl.cpp
 * @brief Implementation of LVGL utility functions for UI components and effects.
 * @author Louis Croci
 * @date 2025-11-14
 */

#include "interface-utils-lvgl.hpp"

namespace LVGLStyles {
    const lv_font_t* FONT_SMALL = &lv_font_montserrat_14;
    const lv_font_t* FONT_NORMAL = &lv_font_montserrat_16;
    const lv_font_t* FONT_MEDIUM = &lv_font_montserrat_20;
    const lv_font_t* FONT_LARGE = &lv_font_montserrat_24;
    const lv_font_t* FONT_XLARGE = &lv_font_montserrat_28;
}

/**
 * @brief Create a card-style container object.
 * @param parent Parent LVGL object.
 * @param x X position.
 * @param y Y position.
 * @param width Card width.
 * @param height Card height.
 * @return Pointer to the created LVGL card object.
 */
lv_obj_t* createCard(lv_obj_t* parent, int16_t x, int16_t y, lv_coord_t width, lv_coord_t height) {
    lv_obj_t* card = lv_obj_create(parent);
    lv_obj_set_size(card, width, height);
    lv_obj_set_pos(card, x, y);
    lv_obj_set_style_bg_color(card, lv_color_hex(LVGLStyles::COLOR_WHITE), 0);
    lv_obj_set_style_radius(card, 10, 0);
    lv_obj_set_style_shadow_width(card, 8, 0);
    lv_obj_set_style_shadow_opa(card, LV_OPA_20, 0);
    lv_obj_set_style_border_width(card, 0, 0);
    lv_obj_set_style_pad_all(card, 10, 0);
    return card;
}

/**
 * @brief Create a styled button with text.
 * @param parent Parent LVGL object.
 * @param x X position.
 * @param y Y position.
 * @param width Button width.
 * @param height Button height.
 * @param text Button label text.
 * @param color Button background color (hex).
 * @param border_radius Button border radius.
 * @return Pointer to the created LVGL button object.
 */
lv_obj_t* createButton(lv_obj_t* parent, int16_t x, int16_t y, lv_coord_t width, lv_coord_t height,
                       const char* text, uint32_t color, int border_radius) {
    lv_obj_t* btn = lv_btn_create(parent);
    lv_obj_set_size(btn, width, height);
    lv_obj_set_pos(btn, x, y);
    lv_obj_set_style_bg_color(btn, lv_color_hex(color), 0);
    lv_obj_set_style_radius(btn, border_radius, 0);
    lv_obj_set_style_shadow_width(btn, 4, 0);
    lv_obj_set_style_shadow_opa(btn, LV_OPA_30, 0);
    
    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_font(label, LVGLStyles::FONT_NORMAL, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(LVGLStyles::COLOR_WHITE), 0);
    lv_obj_center(label);
    
    return btn;
}

/**
 * @brief Create a label with custom font and color.
 * @param parent Parent LVGL object.
 * @param x X position.
 * @param y Y position.
 * @param text Label text.
 * @param font Font to use.
 * @param color Text color (hex).
 * @return Pointer to the created LVGL label object.
 */
lv_obj_t* createLabel(lv_obj_t* parent, int16_t x, int16_t y, const char* text,
                      const lv_font_t* font, uint32_t color) {
    lv_obj_t* label = lv_label_create(parent);
    lv_label_set_text(label, text);
    lv_obj_set_pos(label, x, y);
    lv_obj_set_style_text_font(label, font, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(color), 0);
    return label;
}

/**
 * @brief Create a large title label.
 * @param parent Parent LVGL object.
 * @param x X position.
 * @param y Y position.
 * @param text Title text.
 * @return Pointer to the created LVGL title label object.
 */
lv_obj_t* createTitle(lv_obj_t* parent, int16_t x, int16_t y, const char* text) {
    lv_obj_t* title = createLabel(parent, x, y, text, LVGLStyles::FONT_LARGE, LVGLStyles::COLOR_TEXT_PRIMARY);
    lv_obj_set_style_text_font(title, LVGLStyles::FONT_LARGE, 0);
    return title;
}

/**
 * @brief Create a switch (toggle) object.
 * @param parent Parent LVGL object.
 * @param x X position.
 * @param y Y position.
 * @param initial_state Initial state (true for checked).
 * @return Pointer to the created LVGL switch object.
 */
lv_obj_t* createSwitch(lv_obj_t* parent, int16_t x, int16_t y, bool initial_state) {
    lv_obj_t* sw = lv_switch_create(parent);
    lv_obj_set_pos(sw, x, y);
    if (initial_state) {
        lv_obj_add_state(sw, LV_STATE_CHECKED);
    }
    return sw;
}

/**
 * @brief Create a slider object.
 * @param parent Parent LVGL object.
 * @param x X position.
 * @param y Y position.
 * @param width Slider width.
 * @param min_value Minimum slider value.
 * @param max_value Maximum slider value.
 * @param initial_value Initial slider value.
 * @return Pointer to the created LVGL slider object.
 */
lv_obj_t* createSlider(lv_obj_t* parent, int16_t x, int16_t y, lv_coord_t width,
                       int32_t min_value, int32_t max_value, int32_t initial_value) {
    lv_obj_t* slider = lv_slider_create(parent);
    lv_obj_set_size(slider, width, 10);
    lv_obj_set_pos(slider, x, y);
    lv_slider_set_range(slider, min_value, max_value);
    lv_slider_set_value(slider, initial_value, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(slider, lv_color_hex(LVGLStyles::COLOR_PRIMARY), LV_PART_INDICATOR);
    return slider;
}

/**
 * @brief Create a text area input field.
 * @param parent Parent LVGL object.
 * @param x X position.
 * @param y Y position.
 * @param width Text area width.
 * @param height Text area height.
 * @param placeholder Placeholder text.
 * @return Pointer to the created LVGL text area object.
 */
lv_obj_t* createTextArea(lv_obj_t* parent, int16_t x, int16_t y, lv_coord_t width, lv_coord_t height,
                         const char* placeholder) {
    lv_obj_t* ta = lv_textarea_create(parent);
    lv_obj_set_size(ta, width, height);
    lv_obj_set_pos(ta, x, y);
    lv_textarea_set_placeholder_text(ta, placeholder);
    lv_textarea_set_one_line(ta, height < 40);
    return ta;
}

/**
 * @brief Create a dropdown menu object.
 * @param parent Parent LVGL object.
 * @param x X position.
 * @param y Y position.
 * @param width Dropdown width.
 * @param options Dropdown options string.
 * @return Pointer to the created LVGL dropdown object.
 */
lv_obj_t* createDropdown(lv_obj_t* parent, int16_t x, int16_t y, lv_coord_t width,
                         const char* options) {
    lv_obj_t* dd = lv_dropdown_create(parent);
    lv_obj_set_size(dd, width, LV_SIZE_CONTENT);
    lv_obj_set_pos(dd, x, y);
    lv_dropdown_set_options(dd, options);
    return dd;
}

/**
 * @brief Create a card displaying a measurement value and title.
 * @param parent Parent LVGL object.
 * @param x X position.
 * @param y Y position.
 * @param width Card width.
 * @param height Card height.
 * @param title Title text.
 * @param value Value text.
 * @param value_font Font for value.
 * @param value_color Color for value (hex).
 * @return Pointer to the created LVGL card object.
 */
lv_obj_t* createMeasurementCard(lv_obj_t* parent, int16_t x, int16_t y, lv_coord_t width, lv_coord_t height,
                                const char* title, const char* value, const lv_font_t* value_font,
                                uint32_t value_color) {
    lv_obj_t* card = createCard(parent, x, y, width, height);
    
    // Titre
    lv_obj_t* label_title = lv_label_create(card);
    lv_label_set_text(label_title, title);
    lv_obj_set_style_text_font(label_title, LVGLStyles::FONT_SMALL, 0);
    lv_obj_set_style_text_color(label_title, lv_color_hex(LVGLStyles::COLOR_TEXT_SECONDARY), 0);
    lv_obj_align(label_title, LV_ALIGN_TOP_LEFT, 0, 0);
    
    // Valeur
    lv_obj_t* label_value = lv_label_create(card);
    lv_label_set_text(label_value, value);
    lv_obj_set_style_text_font(label_value, value_font, 0);
    lv_obj_set_style_text_color(label_value, lv_color_hex(value_color), 0);
    lv_obj_align(label_value, LV_ALIGN_CENTER, 0, 5);
    
    return card;
}

/**
 * @brief Create a circular icon button.
 * @param parent Parent LVGL object.
 * @param x X position.
 * @param y Y position.
 * @param size Button size (width and height).
 * @param icon Icon text.
 * @param color Button background color (hex).
 * @return Pointer to the created LVGL button object.
 */
lv_obj_t* createIconButton(lv_obj_t* parent, int16_t x, int16_t y, lv_coord_t size,
                           const char* icon, uint32_t color) {
    lv_obj_t* btn = lv_btn_create(parent);
    lv_obj_set_size(btn, size, size);
    lv_obj_set_pos(btn, x, y);
    lv_obj_set_style_bg_color(btn, lv_color_hex(color), 0);
    lv_obj_set_style_radius(btn, size / 2, 0); // Circulaire
    
    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, icon);
    lv_obj_set_style_text_font(label, LVGLStyles::FONT_LARGE, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(LVGLStyles::COLOR_WHITE), 0);
    lv_obj_center(label);
    
    return btn;
}

/**
 * @brief Create a navigation bar with a title.
 * @param parent Parent LVGL object.
 * @param title Title text.
 * @return Pointer to the created LVGL navigation bar object.
 */
lv_obj_t* createNavBar(lv_obj_t* parent, const char* title) {
    lv_obj_t* navbar = lv_obj_create(parent);
    lv_obj_set_size(navbar, 480, 50);
    lv_obj_set_pos(navbar, 0, 0);
    lv_obj_set_style_bg_color(navbar, lv_color_hex(LVGLStyles::COLOR_PRIMARY), 0);
    lv_obj_set_style_radius(navbar, 0, 0);
    lv_obj_set_style_border_width(navbar, 0, 0);
    lv_obj_set_style_pad_all(navbar, 10, 0);
    
    lv_obj_t* label = lv_label_create(navbar);
    lv_label_set_text(label, title);
    lv_obj_set_style_text_font(label, LVGLStyles::FONT_MEDIUM, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(LVGLStyles::COLOR_WHITE), 0);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);
    
    return navbar;
}

/**
 * @brief Create a modal dialog overlay.
 * @param parent Parent LVGL object.
 * @param width Modal width.
 * @param height Modal height.
 * @param title Modal title text.
 * @return Pointer to the created LVGL overlay object.
 */
lv_obj_t* createModal(lv_obj_t* parent, lv_coord_t width, lv_coord_t height, const char* title) {
    // Overlay sombre
    lv_obj_t* overlay = lv_obj_create(parent);
    lv_obj_set_size(overlay, 480, 320);
    lv_obj_set_style_bg_color(overlay, lv_color_hex(LVGLStyles::COLOR_BLACK), 0);
    lv_obj_set_style_bg_opa(overlay, LV_OPA_50, 0);
    lv_obj_set_style_border_width(overlay, 0, 0);
    
    // Modal
    lv_obj_t* modal = lv_obj_create(overlay);
    lv_obj_set_size(modal, width, height);
    lv_obj_center(modal);
    lv_obj_set_style_bg_color(modal, lv_color_hex(LVGLStyles::COLOR_WHITE), 0);
    lv_obj_set_style_radius(modal, 10, 0);
    lv_obj_set_style_shadow_width(modal, 20, 0);
    lv_obj_set_style_shadow_opa(modal, LV_OPA_50, 0);
    
    // Titre
    if (title) {
        lv_obj_t* label_title = lv_label_create(modal);
        lv_label_set_text(label_title, title);
        lv_obj_set_style_text_font(label_title, LVGLStyles::FONT_MEDIUM, 0);
        lv_obj_align(label_title, LV_ALIGN_TOP_MID, 0, 10);
    }
    
    return overlay;
}

/**
 * @brief Close and delete a modal dialog.
 * @param modal Pointer to the modal overlay object.
 */
void closeModal(lv_obj_t* modal) {
    if (modal) {
        lv_obj_del(modal);
    }
}

/**
 * @brief Show a temporary toast message.
 * @param parent Parent LVGL object.
 * @param message Message text to display.
 * @param duration_ms Duration in milliseconds before disappearing.
 */
void showToast(lv_obj_t* parent, const char* message, uint32_t duration_ms) {
    lv_obj_t* toast = lv_obj_create(parent);
    lv_obj_set_size(toast, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_color(toast, lv_color_hex(LVGLStyles::COLOR_TEXT_PRIMARY), 0);
    lv_obj_set_style_bg_opa(toast, LV_OPA_90, 0);
    lv_obj_set_style_radius(toast, 5, 0);
    lv_obj_set_style_pad_all(toast, 15, 0);
    
    lv_obj_t* label = lv_label_create(toast);
    lv_label_set_text(label, message);
    lv_obj_set_style_text_color(label, lv_color_hex(LVGLStyles::COLOR_WHITE), 0);
    
    lv_obj_align(toast, LV_ALIGN_BOTTOM_MID, 0, -20);
    
    // Animation de disparition
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, toast);
    lv_anim_set_time(&a, 300);
    lv_anim_set_delay(&a, duration_ms);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_values(&a, lv_obj_get_y(toast), 350);
    lv_anim_set_ready_cb(&a, [](lv_anim_t* a) { lv_obj_del((lv_obj_t*)a->var); });
    lv_anim_start(&a);
}

/**
 * @brief Create a vertically scrollable list container.
 * @param parent Parent LVGL object.
 * @param x X position.
 * @param y Y position.
 * @param width List width.
 * @param height List height.
 * @return Pointer to the created LVGL list object.
 */
lv_obj_t* createScrollableList(lv_obj_t* parent, int16_t x, int16_t y, lv_coord_t width, lv_coord_t height) {
    lv_obj_t* list = lv_obj_create(parent);
    lv_obj_set_size(list, width, height);
    lv_obj_set_pos(list, x, y);
    lv_obj_set_style_bg_color(list, lv_color_hex(LVGLStyles::COLOR_WHITE), 0);
    lv_obj_set_style_radius(list, 10, 0);
    lv_obj_set_flex_flow(list, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(list, 5, 0);
    return list;
}

/**
 * @brief Add an item to a scrollable list.
 * @param list Parent LVGL list object.
 * @param text Item text.
 * @param icon Optional icon text.
 * @return Pointer to the created LVGL list item object.
 */
lv_obj_t* addListItem(lv_obj_t* list, const char* text, const char* icon) {
    lv_obj_t* item = lv_obj_create(list);
    lv_obj_set_width(item, lv_pct(100));
    lv_obj_set_height(item, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_color(item, lv_color_hex(LVGLStyles::COLOR_WHITE), 0);
    lv_obj_set_style_border_width(item, 0, 0);
    lv_obj_set_style_pad_all(item, 10, 0);
    
    if (icon) {
        lv_obj_t* label_icon = lv_label_create(item);
        lv_label_set_text(label_icon, icon);
        lv_obj_align(label_icon, LV_ALIGN_LEFT_MID, 0, 0);
    }
    
    lv_obj_t* label_text = lv_label_create(item);
    lv_label_set_text(label_text, text);
    lv_obj_align(label_text, icon ? LV_ALIGN_LEFT_MID : LV_ALIGN_LEFT_MID, icon ? 40 : 0, 0);
    
    return item;
}

/**
 * @brief Animation callback to set background opacity.
 * @param obj LVGL object pointer.
 * @param v Opacity value.
 */
static void anim_set_bg_opa(void* obj, int32_t v) {
    lv_obj_set_style_bg_opa((lv_obj_t*)obj, (lv_opa_t)v, 0);
}

/**
 * @brief Fade transition to a new LVGL screen.
 * @param new_screen Pointer to the new screen object.
 * @param time_ms Transition duration in milliseconds.
 */
void fade_to_screen(lv_obj_t* new_screen, uint16_t time_ms) {
    if (!new_screen) return;

    if (time_ms == 0) {
        lv_scr_load(new_screen);
        return;
    }

    lv_disp_t* disp = lv_disp_get_default();
    if (!disp) {
        lv_scr_load(new_screen);
        return;
    }

    lv_coord_t w = lv_disp_get_hor_res(disp);
    lv_coord_t h = lv_disp_get_ver_res(disp);

    lv_obj_t* overlay = lv_obj_create(lv_layer_top());
    lv_obj_set_size(overlay, w, h);
    lv_obj_set_pos(overlay, 0, 0);
    lv_obj_set_style_bg_color(overlay, lv_color_hex(LVGLStyles::COLOR_BLACK), 0);
    lv_obj_set_style_bg_opa(overlay, LV_OPA_0, 0);
    lv_obj_set_style_border_width(overlay, 0, 0);
    lv_obj_set_style_pad_all(overlay, 0, 0);
    lv_obj_clear_flag(overlay, LV_OBJ_FLAG_SCROLLABLE);

    lv_anim_t a_in;
    lv_anim_init(&a_in);
    lv_anim_set_var(&a_in, overlay);
    lv_anim_set_time(&a_in, time_ms / 2);
    lv_anim_set_exec_cb(&a_in, anim_set_bg_opa);
    lv_anim_set_values(&a_in, 0, 255);

    lv_anim_set_ready_cb(&a_in, [](lv_anim_t* a) {
        lv_obj_t* ov = (lv_obj_t*)a->var;
    });

    lv_anim_start(&a_in);

    uint32_t start = millis();
    while (millis() - start < (time_ms / 2)) {
        lv_timer_handler();
        delay(1);
    }

    lv_scr_load(new_screen);

    lv_anim_t a_out;
    lv_anim_init(&a_out);
    lv_anim_set_var(&a_out, overlay);
    lv_anim_set_time(&a_out, time_ms / 2);
    lv_anim_set_exec_cb(&a_out, anim_set_bg_opa);
    lv_anim_set_values(&a_out, 255, 0);
    lv_anim_set_ready_cb(&a_out, [](lv_anim_t* a) {
        lv_obj_del((lv_obj_t*)a->var);
    });
    lv_anim_start(&a_out);
}
