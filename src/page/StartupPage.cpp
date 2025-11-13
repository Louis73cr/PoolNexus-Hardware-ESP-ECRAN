/**
 * @file StartupPage.cpp
 * @brief Implémentation de la page de démarrage
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#include "StartupPage.hpp"
#include <Arduino.h>

// Couleurs
#define COLOR_BG 0x0010           // Bleu foncé (navy)
#define COLOR_WHITE 0xFFFF        // Blanc
#define COLOR_RED 0xF800          // Rouge
#define COLOR_BLUE 0x001F         // Bleu
#define COLOR_PROGRESS_BG 0x7BEF  // Gris clair
#define COLOR_PROGRESS_FG 0xFFFF  // Blanc

StartupPage::StartupPage(Display* display, TouchScreen* touch) 
    : Page(display, touch), startTime(0) {
    utils = new interfaceUtils(display);
}

StartupPage::~StartupPage() {
    delete utils;
}

void StartupPage::draw() {
    startTime = millis();
    progress = 0;
    isComplete = false;
    
    display->fillScreen(COLOR_BG);
    drawLogo();
    drawProgressBar();
    display->flush();
}

int StartupPage::handleTouch(uint16_t x, uint16_t y) {
    if (!isComplete) {
        unsigned long elapsed = millis() - startTime;
        progress = min(100, (int)(elapsed / 30));
        
        if (progress >= 100) {
            isComplete = true;
            delay(500);
            return PAGE_MAIN_DISPLAY;
        }
        
        drawProgressBar();
        display->flush();
    }
    
    return -1;
}

void StartupPage::drawLogo() {
    display->setTextColor(COLOR_WHITE);
    display->setTextSize(4);
    
    String logo = "Nexus";
    int16_t logoWidth = logo.length() * 24;
    int16_t logoX = (480 - logoWidth) / 2;
    int16_t logoY = 80;
    
    display->setCursor(logoX, logoY);
    display->print(logo);
    
    display->setTextSize(2);
    String subtitle = "Technology & Innovation";
    int16_t subtitleWidth = subtitle.length() * 12;
    int16_t subtitleX = (480 - subtitleWidth) / 2;
    
    display->setCursor(subtitleX, logoY + 50);
    display->print(subtitle);
    
    int16_t lineY = logoY + 80;
    int16_t lineWidth = subtitleWidth;
    int16_t lineX = subtitleX;
    int16_t segmentWidth = lineWidth / 3;
    
    display->fillRect(lineX, lineY, segmentWidth, 4, COLOR_BLUE);
    display->fillRect(lineX + segmentWidth, lineY, segmentWidth, 4, COLOR_WHITE);
    display->fillRect(lineX + 2 * segmentWidth, lineY, segmentWidth, 4, COLOR_RED);
}

void StartupPage::drawProgressBar() {
    int16_t barX = 90;
    int16_t barY = 240;
    int16_t barWidth = 300;
    int16_t barHeight = 20;
    
    display->fillRoundRect(barX, barY, barWidth, barHeight, 10, COLOR_PROGRESS_BG);
    
    int16_t fillWidth = (barWidth - 4) * progress / 100;
    if (fillWidth > 0) {
        display->fillRoundRect(barX + 2, barY + 2, fillWidth, barHeight - 4, 8, COLOR_PROGRESS_FG);
    }
}

void StartupPage::updateProgress(int percent) {
    progress = min(100, max(0, percent));
    drawProgressBar();
    display->flush();
    
    if (progress >= 100) {
        isComplete = true;
    }
}

bool StartupPage::isLoadingComplete() {
    return isComplete;
}
