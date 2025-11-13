/**
 * @file CalibrationPage.hpp
 * @brief Pages de calibration pour pH et Redox
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#ifndef CALIBRATION_PAGE_HPP
#define CALIBRATION_PAGE_HPP

#include "utils/Page.hpp"
#include "utils/interface-utils.hpp"

/**
 * @class CalibrationPage
 * @brief Page de calibration générique
 */
class CalibrationPage : public Page {
protected:
    interfaceUtils* utils;
    String title;
    String measureType; // "pH" ou "Redox"
    
    // Button IDs
    int btnClose;
    int btnValue[4]; // pH: 4,7,10,Autre | Redox: 400,Autre
    int btnValidate;
    
    // État de la calibration
    int selectedValue = 0;
    bool isStable = false;
    String customValue = "";
    
    // Page de destination demandée par un callback (-1 = rester sur la page)
    int nextPageId;
    
    // Callbacks statiques
    static void onCloseClick(void* context);
    static void onValueSelect(void* context);
    static void onValidateClick(void* context);

public:
    CalibrationPage(Display* display, TouchScreen* touch, const char* type);
    virtual ~CalibrationPage();
    
    void draw() override;
    int handleTouch(uint16_t x, uint16_t y) override;
    
private:
    void drawHeader();
    void drawValueButtons();
    void drawStabilityIndicator();
    void drawValidateButton();
};

/**
 * @class CalibrationPHPage
 * @brief Page spécifique pour calibration pH
 */
class CalibrationPHPage : public CalibrationPage {
public:
    CalibrationPHPage(Display* display, TouchScreen* touch) 
        : CalibrationPage(display, touch, "pH") {}
};

/**
 * @class CalibrationRedoxPage
 * @brief Page spécifique pour calibration Redox
 */
class CalibrationRedoxPage : public CalibrationPage {
public:
    CalibrationRedoxPage(Display* display, TouchScreen* touch) 
        : CalibrationPage(display, touch, "Redox") {}
};

#endif
