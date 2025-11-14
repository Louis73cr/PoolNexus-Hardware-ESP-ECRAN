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
 * @file SettingsPageLVGL.cpp
 * @brief Implementation of settings page for LVGL UI.
 */


#include "SettingsPageLVGL.hpp"
#include "utils/interface-utils-lvgl.hpp"
#include "utils/Page.hpp"
#include "utils/PageManager.hpp"
#include "../Translation/text.hpp"
#include <Arduino.h>

Text* SettingsPageLVGL::globalTranslator = nullptr;

/**
 * @brief Constructor for SettingsPageLVGL.
 * @param mgr Optional PageManager pointer.
 */
SettingsPageLVGL::SettingsPageLVGL(PageManager* mgr) 
    : LVGLPageBase("Parametres", mgr), currentPage(0), pageManager(mgr) {

}

void SettingsPageLVGL::build(PageType type) {
/**
 * @brief Builds the settings page UI.
 * @param type Page type (default: STANDARD).
 */
    Serial.println("[SettingsPageLVGL] build() called");

    LVGLPageBase::build(type);
    
    Serial.printf("[SettingsPageLVGL] After build: screen=%p, content_area=%p, backButton=%p\n", 
                  screen, content_area, backButton);

    if (!content_area) {
        Serial.println("[SettingsPageLVGL] ERROR: content_area is NULL after build!");
        return;
    }
    

    if (backButton) {
        lv_obj_remove_event_cb_with_user_data(backButton, nullptr, this);
        lv_obj_add_event_cb(backButton, on_back_clicked, LV_EVENT_CLICKED, this);
    }

    lv_obj_set_style_bg_opa(content_area, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(content_area, 0, 0);
    lv_obj_set_style_shadow_width(content_area, 0, 0);
    lv_obj_set_style_pad_all(content_area, 0, 0);
    
    lv_obj_set_scrollbar_mode(content_area, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(content_area, LV_DIR_VER);
    lv_obj_set_scroll_snap_y(content_area, LV_SCROLL_SNAP_NONE);
    
    btn_previous = createButton(screen, 53, 260, 120, 50, "<", LVGLStyles::COLOR_TEXT_SECONDARY);
    lv_obj_add_event_cb(btn_previous, on_previous_clicked, LV_EVENT_CLICKED, this);
    
    btn_next = createButton(screen, 307, 260, 120, 50, ">", LVGLStyles::COLOR_TEXT_SECONDARY);
    lv_obj_add_event_cb(btn_next, on_next_clicked, LV_EVENT_CLICKED, this);
    
    page_indicator = createLabel(screen, 190, 275, "1/5", LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_SECONDARY);
    
    setupSettingRowsOnce();
    
    if (globalTranslator) {
        drawPageContent();
        updateNavigationButtons();
    } else {
        Serial.println("[SettingsPageLVGL] WARNING: globalTranslator is NULL, skipping drawPageContent()");
        updateNavigationButtons();
    }
}

SettingsPageLVGL::~SettingsPageLVGL() {
/**
 * @brief Destructor for SettingsPageLVGL.
 */
    // Base class destructor handles screen cleanup
}


void SettingsPageLVGL::hide() {
/**
 * @brief Hides the settings page.
 */
    // La page est cachée automatiquement quand une autre page est chargée
}

void SettingsPageLVGL::drawPageContent() {
/**
 * @brief Draws the content for the current settings page.
 */
    if (!globalTranslator) {
        Serial.println("[SettingsPageLVGL] ERROR: globalTranslator is NULL in drawPageContent()!");
        return;
    }
    if (!content_area) {
        Serial.println("[SettingsPageLVGL] ERROR: content_area is NULL in drawPageContent()!");
        return;
    }
    if (!page_indicator) {
        Serial.println("[SettingsPageLVGL] ERROR: page_indicator is NULL in drawPageContent()!");
        return;
    }
    
    struct SettingItem {
        const char* text;
        int pageId;
    };
    
    const SettingItem items[5][3] = {
        // Page 0
        {{Text::Settings::pump(globalTranslator->getCurrentLanguage()), PAGE_PUMP}, 
         {Text::Settings::calibration_Redox(globalTranslator->getCurrentLanguage()), PAGE_CALIBRATION_REDOX}, 
         {Text::Settings::calibration_pH(globalTranslator->getCurrentLanguage()), PAGE_CALIBRATION_PH}},
        
        // Page 1
        {{Text::Settings::switch_(globalTranslator->getCurrentLanguage()), PAGE_SWITCH}, 
         {Text::Settings::pool_fill(globalTranslator->getCurrentLanguage()), PAGE_POOL_FILL}, 
         {"MQTT", PAGE_MQTT}},
        
        // Page 2
        {{Text::Settings::product_level(globalTranslator->getCurrentLanguage()), PAGE_LEVEL_PROBE}, 
         {Text::Settings::lock_screen(globalTranslator->getCurrentLanguage()), PAGE_LOCK}, 
         {Text::Settings::screen(globalTranslator->getCurrentLanguage()), PAGE_SCREEN}},
        
        // Page 3
        {{Text::Settings::language(globalTranslator->getCurrentLanguage()), PAGE_LANGUAGE}, 
         {Text::Settings::cloud(globalTranslator->getCurrentLanguage()), PAGE_CLOUD}, 
         {Text::Settings::wifi(globalTranslator->getCurrentLanguage()), PAGE_WIFI}},
        
        // Page 4
        {{Text::Settings::reset(globalTranslator->getCurrentLanguage()), PAGE_RESET}, 
         {"", -1}, 
         {"", -1}}
    };
    
    for (int i = 0; i < 3; i++) {
        const char* t = items[currentPage][i].text;
        int id = items[currentPage][i].pageId;
        setRow(i, t, id);
    }
    
    if (currentPage == 4) {
        lv_obj_t* version_label = createLabel(content_area, 0, 150, "Version : 1.0.1", 
                                               LVGLStyles::FONT_SMALL, LVGLStyles::COLOR_TEXT_SECONDARY);
        lv_obj_align(version_label, LV_ALIGN_BOTTOM_MID, 0, -10);
    }
    
    if (page_indicator) {
        char page_text[16];
        snprintf(page_text, sizeof(page_text), "%d/%d", currentPage + 1, totalPages);
        lv_label_set_text(page_indicator, page_text);
    }
}

/**
 * @brief Creates a setting button for a given index and text.
 * @param index Button index.
 * @param text Button label.
 * @param pageId Associated page ID.
 */
void SettingsPageLVGL::createSettingButton(int index, const char* text, int pageId) {
    if (index < 0 || index >= 3) {
        Serial.printf("[SettingsPageLVGL] ERROR: Invalid index %d in createSettingButton()\n", index);
        return;
    }
    
    if (!content_area) {
        Serial.println("[SettingsPageLVGL] ERROR: content_area is NULL in createSettingButton()!");
        return;
    }
    
    int y_pos = index * 65;
    setting_buttons[index] = createCard(content_area, 0, y_pos, 440, 60);
    if (!setting_buttons[index]) {
        Serial.printf("[SettingsPageLVGL] ERROR: Failed to create button[%d]\n", index);
        return;
    }
    
    lv_obj_add_flag(setting_buttons[index], LV_OBJ_FLAG_CLICKABLE);
    
    lv_obj_set_user_data(setting_buttons[index], (void*)(intptr_t)pageId);
    
    lv_obj_add_event_cb(setting_buttons[index], on_setting_clicked, LV_EVENT_CLICKED, this);

    setting_labels[index] = createLabel(setting_buttons[index], 10, 20, text ? text : "", 
                                        LVGLStyles::FONT_NORMAL, LVGLStyles::COLOR_TEXT_PRIMARY);
    if (!setting_labels[index]) {
        Serial.printf("[SettingsPageLVGL] ERROR: Failed to create label[%d]\n", index);
    }
    setting_page_ids[index] = pageId;
}

/**
 * @brief Updates navigation buttons (previous/next).
 */
void SettingsPageLVGL::updateNavigationButtons() {
    if (!btn_previous || !btn_next || !page_indicator) {
        Serial.println("[SettingsPageLVGL] ERROR: Navigation buttons are NULL in updateNavigationButtons()!");
        return;
    }
    
    if (currentPage > 0) {
        lv_obj_set_style_bg_color(btn_previous, lv_color_hex(LVGLStyles::COLOR_PRIMARY), 0);
        lv_obj_clear_state(btn_previous, LV_STATE_DISABLED);
    } else {
        lv_obj_set_style_bg_color(btn_previous, lv_color_hex(LVGLStyles::COLOR_TEXT_SECONDARY), 0);
        lv_obj_add_state(btn_previous, LV_STATE_DISABLED);
    }
    
    if (currentPage < totalPages - 1) {
        lv_obj_set_style_bg_color(btn_next, lv_color_hex(LVGLStyles::COLOR_PRIMARY), 0);
        lv_obj_clear_state(btn_next, LV_STATE_DISABLED);
    } else {
        lv_obj_set_style_bg_color(btn_next, lv_color_hex(LVGLStyles::COLOR_TEXT_SECONDARY), 0);
        lv_obj_add_state(btn_next, LV_STATE_DISABLED);
    }
}

/**
 * @brief Navigates to the previous settings page.
 */
void SettingsPageLVGL::previousPage() {
    if (currentPage > 0) {
        currentPage--;
        drawPageContent();
        updateNavigationButtons();
    }
}

/**
 * @brief Navigates to the next settings page.
 */
void SettingsPageLVGL::nextPage() {
    if (currentPage < totalPages - 1) {
        currentPage++;
        drawPageContent();
        updateNavigationButtons();
    }
}

/**
 * @brief Sets up setting rows (called once).
 */
void SettingsPageLVGL::setupSettingRowsOnce() {
    for (int i = 0; i < 3; i++) {
        createSettingButton(i, "", -1);
        lv_obj_add_flag(setting_buttons[i], LV_OBJ_FLAG_HIDDEN);
    }
}

/**
 * @brief Sets a row with text and page ID.
 * @param index Row index.
 * @param text Row label.
 * @param pageId Associated page ID.
 */
void SettingsPageLVGL::setRow(int index, const char* text, int pageId) {
    if (index < 0 || index >= 3) {
        Serial.printf("[SettingsPageLVGL] ERROR: Invalid index %d in setRow()\n", index);
        return;
    }
    
    if (!setting_buttons[index] || !setting_labels[index]) {
        Serial.printf("[SettingsPageLVGL] ERROR: setting_buttons[%d] or setting_labels[%d] is NULL!\n", index, index);
        return;
    }
    
    if (!content_area) {
        Serial.println("[SettingsPageLVGL] ERROR: content_area is NULL in setRow()!");
        return;
    }
    
    if (text && strlen(text) > 0) {
        lv_label_set_text(setting_labels[index], text);
        lv_obj_clear_flag(setting_buttons[index], LV_OBJ_FLAG_HIDDEN);
        setting_page_ids[index] = pageId;
        lv_obj_set_user_data(setting_buttons[index], (void*)(intptr_t)pageId);
    } else {
        lv_obj_add_flag(setting_buttons[index], LV_OBJ_FLAG_HIDDEN);
        setting_page_ids[index] = -1;
        lv_obj_set_user_data(setting_buttons[index], (void*)(intptr_t)-1);
    }
    lv_obj_scroll_to_y(content_area, 0, LV_ANIM_OFF);
}

/**
 * @brief Callback for previous button click.
 * @param e LVGL event.
 */
void SettingsPageLVGL::on_previous_clicked(lv_event_t* e) {
    SettingsPageLVGL* page = (SettingsPageLVGL*)e->user_data;
    page->previousPage();
}

/**
 * @brief Callback for next button click.
 * @param e LVGL event.
 */
void SettingsPageLVGL::on_next_clicked(lv_event_t* e) {
    SettingsPageLVGL* page = (SettingsPageLVGL*)e->user_data;
    page->nextPage();
}

/**
 * @brief Callback for setting button click.
 * @param e LVGL event.
 */
void SettingsPageLVGL::on_setting_clicked(lv_event_t* e) {
    SettingsPageLVGL* page = (SettingsPageLVGL*)e->user_data;
    if (!page || !page->pageManager) return;
    
    lv_obj_t* btn = lv_event_get_target(e);
    
    int pageId = (int)(intptr_t)lv_obj_get_user_data(btn);
    
    if (pageId >= 0) {
        Serial.printf("[SettingsPageLVGL] Navigation vers page %d\n", pageId);
        page->pageManager->navigateToPage(static_cast<PageID>(pageId));
    }
}

/**
 * @brief Callback for back button click (returns to MainDisplay).
 * @param e LVGL event.
 */
void SettingsPageLVGL::on_back_clicked(lv_event_t* e) {
    SettingsPageLVGL* page = (SettingsPageLVGL*)e->user_data;
    if (!page || !page->pageManager) return;
    
    page->pageManager->navigateToPage(PageID::PAGE_MAIN_DISPLAY);
}
