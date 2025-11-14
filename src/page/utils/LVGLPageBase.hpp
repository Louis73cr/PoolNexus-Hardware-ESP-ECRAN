/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   LVGLPageBase.hpp                               :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: Louis Croci <louis.croci@epitech.eu>       +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/14 21:26:09 by Louis Croci    #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/14 21:26:09 by Louis Croci    ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */

/**
 * @file LVGLPageBase.hpp
 * @brief Simple base class for LVGL pages with navbar and back handling.
 */

#ifndef LVGL_PAGE_BASE_HPP
#define LVGL_PAGE_BASE_HPP

#include <lvgl.h>
#include "interface-utils-lvgl.hpp"
#include "Page.hpp"
#include "../../Translation/text.hpp"

class PageManager;

class LVGLPageBase {
protected:
    lv_obj_t* screen;
    lv_obj_t* navbar;
    lv_obj_t* content_area;
    lv_obj_t* backButton;
    int nextPageId;
    const char* title;
    PageManager* pageManager;

    static void on_back_clicked(lv_event_t* e);

public:
    explicit LVGLPageBase(const char* titleText, PageManager* mgr = nullptr);
    virtual ~LVGLPageBase();

    virtual void build(PageType type = STANDARD);
    virtual void show();
    
    void setPageManager(PageManager* mgr) { pageManager = mgr; }

    int getNextPageId() const { return nextPageId; }
    void resetNextPageId() { nextPageId = -1; }

    Text* globalTranslator = nullptr;
};

#endif
