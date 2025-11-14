/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   TouchController.hpp                            :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: Louis Croci <louis.croci@epitech.eu>       +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/14 21:09:31 by Louis Croci    #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/14 21:09:31 by Louis Croci    ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */
/**
 * @file TouchController.hpp
 * @brief Touch controller interface definition for display.
 */

#ifndef TOUCH_CONTROLLER_HPP
#define TOUCH_CONTROLLER_HPP

#include <Arduino.h>
#include <Wire.h>

class TouchController {
private:
    static const uint8_t I2C_ADDR = 0x3B;
    static const uint8_t PIN_SDA  = 4;
    static const uint8_t PIN_SCL  = 8;
    static const uint8_t PIN_RST  = 12;
    static const uint8_t PIN_INT  = 11;
    static const uint32_t I2C_CLOCK = 400000;
    static const uint8_t MAX_TOUCH_POINTS = 1;

    bool initialized;
    uint8_t screenRotation;

    bool sendReadCommand();
    bool readTouchData(uint8_t* data);
    bool decodeTouchData(uint8_t* data, uint16_t& x, uint16_t& y);
    void calibrateCoordinates(uint16_t rawX, uint16_t rawY, uint16_t& x, uint16_t& y);

public:
    TouchController();
    bool begin();
    void setRotation(uint8_t rotation);
    uint8_t getRotation() const { return screenRotation; }
    bool isTouched();
    bool getTouchPoint(uint16_t& x, uint16_t& y);
    bool waitForTouch(uint32_t timeout_ms = 0);
    bool waitForRelease(uint32_t timeout_ms = 0);
};

#endif // TOUCH_CONTROLLER_HPP
