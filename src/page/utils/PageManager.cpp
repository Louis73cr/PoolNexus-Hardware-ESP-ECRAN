/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   PageManager.cpp                                :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: Louis Croci <louis.croci@epitech.eu>       +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/14 21:25:29 by Louis Croci    #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/14 21:25:29 by Louis Croci    ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */
/**
 * @file PageManager.cpp
 * @brief Implementation of page manager for LVGL UI.
 */

#include "PageManager.hpp"
#include "../MainDisplayPageLVGL.hpp"
#include "../SettingsPageLVGL.hpp"
#include "../CalibrationPHPageLVGL.hpp"
#include "../CalibrationRedoxPageLVGL.hpp"
#include "../CloudPageLVGL.hpp"
#include "../WiFiPageLVGL.hpp"
#include "../MQTTPageLVGL.hpp"
#include "../PumpPageLVGL.hpp"
#include "../SwitchPageLVGL.hpp"
#include "../LevelProbePageLVGL.hpp"
#include "../PoolFillPageLVGL.hpp"
#include "../LockPageLVGL.hpp"
#include "../ScreenPageLVGL.hpp"
#include "../LanguagePageLVGL.hpp"
#include "../ResetPageLVGL.hpp"
#include "LVGLPageBase.hpp"

#include <Arduino.h>

PageManager::PageManager() {
  for (auto &p : pages) p = nullptr;

  pages[static_cast<size_t>(PageID::PAGE_MAIN_DISPLAY)] = new MainDisplayPageLVGL(this);
  pages[static_cast<size_t>(PageID::PAGE_SETTINGS)] = new SettingsPageLVGL(this);
  pages[static_cast<size_t>(PageID::PAGE_CALIBRATION_PH)] = new CalibrationPHPageLVGL(this);
  pages[static_cast<size_t>(PageID::PAGE_CALIBRATION_REDOX)] = new CalibrationRedoxPageLVGL(this);
  pages[static_cast<size_t>(PageID::PAGE_CLOUD)] = new CloudPageLVGL(this);
  pages[static_cast<size_t>(PageID::PAGE_WIFI)] = new WiFiPageLVGL(this);
  pages[static_cast<size_t>(PageID::PAGE_MQTT)] = new MQTTPageLVGL(this);
  pages[static_cast<size_t>(PageID::PAGE_PUMP)] = new PumpPageLVGL(this);
  pages[static_cast<size_t>(PageID::PAGE_SWITCH)] = new SwitchPageLVGL(this);
  pages[static_cast<size_t>(PageID::PAGE_LEVEL_PROBE)] = new LevelProbePageLVGL(this);
  pages[static_cast<size_t>(PageID::PAGE_POOL_FILL)] = new PoolFillPageLVGL(this);
  pages[static_cast<size_t>(PageID::PAGE_LOCK)] = new LockPageLVGL(this);
  pages[static_cast<size_t>(PageID::PAGE_SCREEN)] = new ScreenPageLVGL(this);
  pages[static_cast<size_t>(PageID::PAGE_LANGUAGE)] = new LanguagePageLVGL(this);
  pages[static_cast<size_t>(PageID::PAGE_RESET)] = new ResetPageLVGL(this);
  
  setupPageManagerForPages();
}

void PageManager::setupPageManagerForPages() {
  for (auto* page : pages) {
    if (page) {
      setupPageManagerForPage(page);
    }
  }
}

void PageManager::setupPageManagerForPage(Page* page) {
  // Essayer de caster vers LVGLPageBase
  // Comme toutes les pages héritent de Page, on doit vérifier si elles héritent aussi de LVGLPageBase
  // On utilise un cast multiple pour accéder à LVGLPageBase
  // Note: Cette approche fonctionne car les pages héritent de Page et LVGLPageBase (héritage multiple)
  
  // Pour chaque page qui hérite de LVGLPageBase, on peut utiliser un cast
  // Mais comme on ne peut pas utiliser dynamic_cast facilement, on va passer le PageManager
  // dans les constructeurs des pages qui en ont besoin
  
  // Pour l'instant, on va utiliser une approche différente : passer this dans les constructeurs
  // des pages qui héritent de LVGLPageBase
}

PageManager::~PageManager() {
  if (getCurrentPage()) {
    getCurrentPage()->onHide();
  }

  for (auto* page : pages) {
    delete page;
  }
}

void PageManager::begin() {
    setupPageManagerForPages();
    
    size_t idx = static_cast<size_t>(currentPageId);

    if (pages[idx]) {
        pages[idx]->onEnter();
        pages[idx]->create();
        pages[idx]->show();
        currentPageShown = true;
    }
}

void PageManager::loop() {
    // loop() ne doit PAS appeler show() à chaque fois
    // show() est appelé uniquement lors de la création ou du changement de page
    // Cette méthode peut être utilisée pour d'autres mises à jour périodiques si nécessaire
}


void PageManager::navigateToPage(PageID pageId) {
    size_t oldIdx = static_cast<size_t>(currentPageId);
    size_t newIdx = static_cast<size_t>(pageId);

    if (newIdx >= pages.size() || !pages[newIdx]) {
        Serial.printf("[PageManager] ERROR: Invalid page ID %d or page is NULL\n", (int)pageId);
        return;
    }

    Serial.printf("[PageManager] Navigating from page %d to page %d\n", (int)currentPageId, (int)pageId);

    if (pages[oldIdx]) pages[oldIdx]->onExit();

    currentPageId = pageId;
    currentPageShown = false;

    pages[newIdx]->onEnter();
    pages[newIdx]->create();
    pages[newIdx]->show();
    currentPageShown = true;
    
    Serial.printf("[PageManager] Navigation complete to page %d\n", (int)pageId);
}

Page* PageManager::getCurrentPage() const {
  size_t idx = static_cast<size_t>(currentPageId);
  if (idx < pages.size()) return pages[idx];
  return nullptr;
}
