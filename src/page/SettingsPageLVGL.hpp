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
 * @file SettingsPageLVGL.hpp
 * @brief LVGL settings page with pagination (5 pages).
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#ifndef SETTINGS_PAGE_LVGL_H
#define SETTINGS_PAGE_LVGL_H

#include <lvgl.h>
#include "utils/LVGLPageBase.hpp"
#include "../Translation/text.hpp"

class PageManager;

class SettingsPageLVGL : public LVGLPageBase, public Page {
private:
    static Text* globalTranslator;
    PageManager* pageManager;
    
    int currentPage;
    const int totalPages = 5;
    
    lv_obj_t* btn_previous;
    lv_obj_t* btn_next;
    lv_obj_t* page_indicator;
    
    lv_obj_t* setting_buttons[3];
    lv_obj_t* setting_labels[3];
    int setting_page_ids[3];
    
    /**
     * @brief Draws the content for the current settings page.
     */
    void drawPageContent();

    /**
     * @brief Updates navigation buttons (previous/next).
     */
    void updateNavigationButtons();

    /**
     * @brief Creates a setting button for a given index and text.
     * @param index Button index.
     * @param text Button label.
     * @param pageId Associated page ID.
     */
    void createSettingButton(int index, const char* text, int pageId);

    /**
     * @brief Sets up setting rows (called once).
     */
    void setupSettingRowsOnce();

    /**
     * @brief Sets a row with text and page ID.
     * @param index Row index.
     * @param text Row label.
     * @param pageId Associated page ID.
     */
    void setRow(int index, const char* text, int pageId);

    /**
     * @brief Callback for previous button click.
     * @param e LVGL event.
     */
    static void on_previous_clicked(lv_event_t* e);

    /**
     * @brief Callback for next button click.
     * @param e LVGL event.
     */
    static void on_next_clicked(lv_event_t* e);

    /**
     * @brief Callback for setting button click.
     * @param e LVGL event.
     */
    static void on_setting_clicked(lv_event_t* e);

    /**
     * @brief Callback for back button click (returns to MainDisplay).
     * @param e LVGL event.
     */
    static void on_back_clicked(lv_event_t* e);

public:
    /**
     * @brief Constructor for SettingsPageLVGL.
     * @param mgr Optional PageManager pointer.
     */
    SettingsPageLVGL(PageManager* mgr = nullptr);

    /**
     * @brief Destructor for SettingsPageLVGL.
     */
    ~SettingsPageLVGL();

    /**
     * @brief Sets the PageManager for this page.
     * @param mgr PageManager pointer.
     */
    void setPageManager(PageManager* mgr) { 
        pageManager = mgr; 
        LVGLPageBase::setPageManager(mgr);
    }

    /**
     * @brief Builds the settings page UI.
     * @param type Page type (default: STANDARD).
     */
    void build(PageType type = STANDARD) override;

    /**
     * @brief Shows the settings page.
     */
    void show() override { 
        LVGLPageBase::show(); 
    }

    /**
     * @brief Hides the settings page.
     */
    void hide();

    /**
     * @brief Navigates to the next settings page.
     */
    void nextPage();

    /**
     * @brief Navigates to the previous settings page.
     */
    void previousPage();

    /**
     * @brief Creates the settings page UI if not already created.
     */
    void create() override {
        if (!screen) {
            build(STANDARD);
        }
    }
    
    /**
     * @brief Sets the global translator for all settings pages.
     * @param translator Pointer to Text translator.
     */
    static void setGlobalTranslator(Text* translator) {
        globalTranslator = translator;
    }
};

#endif // SETTINGS_PAGE_LVGL_H
