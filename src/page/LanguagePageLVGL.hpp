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
#ifndef LANGUAGE_PAGE_LVGL_HPP
#define LANGUAGE_PAGE_LVGL_HPP

#include "utils/LVGLPageBase.hpp"
#include "../Translation/text.hpp"

class PageManager;

class LanguagePageLVGL : public LVGLPageBase, public Page {
private:
    static Text* globalTranslator;
    static void on_language_clicked(lv_event_t* e);
public:
    LanguagePageLVGL(PageManager* mgr = nullptr) : LVGLPageBase("Language Settings", mgr) {}

    void build(PageType type = STANDARD) override;
    static void setGlobalTranslator(Text* translator) {
        globalTranslator = translator;
    }
    void show() override { LVGLPageBase::show(); }
    void create() override {}
};

#endif
