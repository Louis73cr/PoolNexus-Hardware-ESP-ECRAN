/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   PageManager.hpp                                :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: Louis Croci <louis.croci@epitech.eu>       +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/14 21:25:22 by Louis Croci    #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/14 21:25:22 by Louis Croci    ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */
/**
 * @file PageManager.hpp
 * @brief Page manager class definition for LVGL UI.
 */

#ifndef PAGE_MANAGER_HPP
#define PAGE_MANAGER_HPP

#include "Page.hpp"
#include <array>
#include <cstdint>


class LVGLPageBase;

class PageManager {
public:
    PageManager();
    ~PageManager();


    void begin();
    void loop();
    void navigateToPage(PageID pageId);
    Page* getCurrentPage() const;
    PageID getCurrentPageId() const { return currentPageId; }
    void setupPageManagerForPages();

private:
    PageID currentPageId = PageID::PAGE_MAIN_DISPLAY;
    std::array<Page*, PAGE_COUNT> pages{};
    bool currentPageShown = false;
    void setupPageManagerForPage(Page* page);
};

#endif // PAGE_MANAGER_HPP
