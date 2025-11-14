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
#ifndef RESET_PAGE_LVGL_HPP
#define RESET_PAGE_LVGL_HPP

#include "utils/LVGLPageBase.hpp"
#include "utils/Page.hpp"
#include "../Translation/text.hpp"

// Forward declaration
class PageManager;

class ResetPageLVGL : public LVGLPageBase, public Page {
private:
    static Text* globalTranslator;
    
    lv_obj_t* btn_reset_settings;
    lv_obj_t* btn_reset_all;
    
    static void on_reset_settings(lv_event_t* e);
    static void on_reset_all(lv_event_t* e);
    
public:
    ResetPageLVGL(PageManager* mgr = nullptr);
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
