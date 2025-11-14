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

#ifndef SWITCH_PAGE_LVGL_HPP
#define SWITCH_PAGE_LVGL_HPP

#include "utils/LVGLPageBase.hpp"
#include "../Translation/text.hpp"

class PageManager;

/**
 * @class SwitchPageLVGL
 * @brief LVGL page for managing switches in the UI.
 */
class SwitchPageLVGL : public LVGLPageBase, public Page {
private:
    static Text* globalTranslator;
    
    lv_obj_t* switch1;
    lv_obj_t* switch2;
    lv_obj_t* switch3;
    
    bool switch1_enabled;
    bool switch2_enabled;
    bool switch3_enabled;
    
    /**
     * @brief Callback for switch 1 state change.
     * @param e LVGL event.
     */
    static void on_switch1_changed(lv_event_t* e);
    /**
     * @brief Callback for switch 2 state change.
     * @param e LVGL event.
     */
    static void on_switch2_changed(lv_event_t* e);
    /**
     * @brief Callback for switch 3 state change.
     * @param e LVGL event.
     */
    static void on_switch3_changed(lv_event_t* e);
    
public:
    /**
     * @brief Constructor for SwitchPageLVGL.
     * @param mgr Optional PageManager pointer.
     */
    SwitchPageLVGL(PageManager* mgr = nullptr);
    /**
     * @brief Builds the switch page UI.
     * @param type Page type (default: STANDARD).
     */
    void build(PageType type = STANDARD) override;
    /**
     * @brief Shows the switch page.
     */
    void show() override { LVGLPageBase::show(); }
    /**
     * @brief Creates the switch page UI if not already created.
     */
    void create() override {
        if (!screen) {
            build(STANDARD);
        }
    }
    /**
     * @brief Sets the global translator for all switch pages.
     * @param translator Pointer to Text translator.
     */
    static void setGlobalTranslator(Text* translator) {
        globalTranslator = translator;
    }
};

#endif
