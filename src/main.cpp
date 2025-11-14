/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   main.cpp                                       :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: Louis Croci <louis.croci@epitech.eu>       +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/14 21:09:18 by Louis Croci    #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/14 21:09:18 by Louis Croci    ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */

/**
 * @file main.cpp
 * @brief Main entry point for PoolNexus LVGL firmware.
 *
 * Initializes display, touch, translation, and page management for LVGL UI.
 * Simulates sensor values and manages page navigation.
 */

#include <Arduino.h>
#include "screen/DisplayLVGL.hpp"
#include "screen/TouchController.hpp"
#include "screen/LVGLTouchInput.hpp"
#include "page/MainDisplayPageLVGL.hpp"
#include "page/SettingsPageLVGL.hpp"
#include "page/PumpPageLVGL.hpp"
#include "page/CalibrationRedoxPageLVGL.hpp"
#include "page/CalibrationPHPageLVGL.hpp"
#include "page/SwitchPageLVGL.hpp"
#include "page/PoolFillPageLVGL.hpp"
#include "page/MQTTPageLVGL.hpp"
#include "page/LevelProbePageLVGL.hpp"
#include "page/LockPageLVGL.hpp"
#include "page/ScreenPageLVGL.hpp"
#include "page/LanguagePageLVGL.hpp"
#include "page/CloudPageLVGL.hpp"
#include "page/WiFiPageLVGL.hpp"
#include "page/ResetPageLVGL.hpp"
#include "page/utils/Page.hpp"
#include "page/utils/PageManager.hpp"
#include "Translation/text.hpp"

DisplayLVGL* display;
TouchController* touch;
LVGLTouchInput* touchLVGL;
/**
 * @brief Global translator instance for UI text.
 */
Text translator;
PageManager* pageManager;

/**
 * @brief Arduino setup function. Initializes hardware and UI components.
 */
void setup() {

    Serial.begin(115200);
    delay(2000);
    Serial.println("\n\n=== PoolNexus LVGL Demo ===");
    Serial.println("Starting initialization...");
    display = new DisplayLVGL();
    if (!display->begin()) {
        while(1) {
            delay(100);
        }
    }
    touch = new TouchController();
    if (!touch->begin()) {
        while(1) {
            delay(100);
        }
    }
    touch->setRotation(1);
    touchLVGL = new LVGLTouchInput(touch);
    if (!touchLVGL->begin()) {
        while(1) delay(100);
    }
    translator.setLanguage(Text::Language::FRENCH);
    LanguagePageLVGL::setGlobalTranslator(&translator);
    SettingsPageLVGL::setGlobalTranslator(&translator);
    PumpPageLVGL::setGlobalTranslator(&translator);
    CalibrationPHPageLVGL::setGlobalTranslator(&translator);
    CalibrationRedoxPageLVGL::setGlobalTranslator(&translator);
    CloudPageLVGL::setGlobalTranslator(&translator);
    WiFiPageLVGL::setGlobalTranslator(&translator);
    MQTTPageLVGL::setGlobalTranslator(&translator);
    SwitchPageLVGL::setGlobalTranslator(&translator);
    LevelProbePageLVGL::setGlobalTranslator(&translator);
    PoolFillPageLVGL::setGlobalTranslator(&translator);
    LockPageLVGL::setGlobalTranslator(&translator);
    ScreenPageLVGL::setGlobalTranslator(&translator);
    ResetPageLVGL::setGlobalTranslator(&translator);
    pageManager = new PageManager();
    pageManager->begin();
}

/**
 * @brief Arduino loop function. Updates LVGL and simulates sensor values.
 */
void loop() {
    display->loop();
    pageManager->loop();
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate > 2000) {
        float ph = 7.0 + random(-5, 5) / 10.0;
        float redox = 750 + random(-50, 50);
        float temp = 24.5 + random(-10, 10) / 10.0;
        Page* current = pageManager->getCurrentPage();
        if (current) {
            PageID currentId = static_cast<PageID>(pageManager->getCurrentPageId());
            if (currentId == PageID::PAGE_MAIN_DISPLAY) {
                auto mainDisplay = static_cast<MainDisplayPageLVGL*>(current);
                if (mainDisplay) {
                    mainDisplay->updateValues(ph, redox, temp);
                }
            }
        }
        lastUpdate = millis();
    }
    delay(5);
}
