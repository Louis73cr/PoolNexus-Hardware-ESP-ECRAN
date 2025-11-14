/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   TouchController.cpp                            :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: Louis Croci <louis.croci@epitech.eu>       +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/14 21:09:39 by Louis Croci    #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/14 21:09:39 by Louis Croci    ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */
/**
 * @file TouchController.cpp
 * @brief Implementation of touch controller logic for display.
 */

#include "TouchController.hpp"

TouchController::TouchController()
    : initialized(false), screenRotation(0) {}

bool TouchController::begin() {
    Wire.begin(PIN_SDA, PIN_SCL);
    Wire.setClock(I2C_CLOCK);

    pinMode(PIN_INT, INPUT_PULLUP);
    pinMode(PIN_RST, OUTPUT);

    digitalWrite(PIN_RST, LOW);
    delay(200);
    digitalWrite(PIN_RST, HIGH);
    delay(200);

    Wire.beginTransmission(I2C_ADDR);
    if (Wire.endTransmission() != 0) {
        Serial.println("Erreur: Contrôleur tactile non détecté!");
        return false;
    }

    initialized = true;
    Serial.println("Contrôleur tactile initialisé");
    return true;
}

void TouchController::setRotation(uint8_t rotation) {
    if (rotation > 3) rotation = 0;
    screenRotation = rotation;
}

bool TouchController::sendReadCommand() {
    const uint8_t read_cmd[11] = {
        0xb5, 0xab, 0xa5, 0x5a, 0x00, 0x00,
        (uint8_t)((MAX_TOUCH_POINTS * 6 + 2) >> 8),
        (uint8_t)((MAX_TOUCH_POINTS * 6 + 2) & 0xff),
        0x00, 0x00, 0x00
    };

    Wire.beginTransmission(I2C_ADDR);
    Wire.write(read_cmd, 11);
    return (Wire.endTransmission() == 0);
}

bool TouchController::readTouchData(uint8_t* data) {
    size_t dataSize = MAX_TOUCH_POINTS * 6 + 2;
    if (Wire.requestFrom(I2C_ADDR, dataSize) != dataSize) {
        return false;
    }
    for (size_t i = 0; i < dataSize; i++) {
        data[i] = Wire.read();
    }
    return true;
}

bool TouchController::decodeTouchData(uint8_t* data, uint16_t& x, uint16_t& y) {
    if (data[1] == 0 || data[1] > MAX_TOUCH_POINTS) {
        return false;
    }
    uint16_t rawX = ((data[2] & 0x0F) << 8) | data[3];
    uint16_t rawY = ((data[4] & 0x0F) << 8) | data[5];
    if (rawX > 500 || rawY > 500) {
        return false;
    }
    calibrateCoordinates(rawX, rawY, x, y);
    static int touch_count = 0;
    if (++touch_count % 20 == 0) {
        Serial.printf("Touch: raw(%d,%d) -> cal(%d,%d) rot=%d\n", rawX, rawY, x, y, screenRotation);
    }
    return true;
}

void TouchController::calibrateCoordinates(uint16_t rawX, uint16_t rawY, uint16_t& x, uint16_t& y) {
    switch (screenRotation) {
        case 0:
            x = rawY;
            y = map(rawX, 0, 320, 320, 0);
            break;
        case 1:
            x = map(rawY, 0, 480, 0, 480);
            y = map(rawX, 0, 320, 320, 0);
            break;
        case 2:
            x = map(rawY, 0, 480, 480, 0);
            y = rawX;
            break;
        case 3:
            x = map(rawY, 0, 480, 480, 0);
            y = map(rawX, 0, 320, 0, 320);
            break;
    }
}

bool TouchController::isTouched() {
    if (!initialized) return false;
    uint16_t x, y;
    return getTouchPoint(x, y);
}

bool TouchController::getTouchPoint(uint16_t& x, uint16_t& y) {
    if (!initialized) return false;
    if (!sendReadCommand()) return false;
    uint8_t data[MAX_TOUCH_POINTS * 6 + 2] = {0};
    if (!readTouchData(data)) return false;
    return decodeTouchData(data, x, y);
}

bool TouchController::waitForTouch(uint32_t timeout_ms) {
    uint32_t startTime = millis();
    while (true) {
        if (isTouched()) return true;
        if (timeout_ms > 0 && (millis() - startTime) >= timeout_ms) return false;
        delay(10);
    }
}

bool TouchController::waitForRelease(uint32_t timeout_ms) {
    uint32_t startTime = millis();
    while (true) {
        if (!isTouched()) return true;
        if (timeout_ms > 0 && (millis() - startTime) >= timeout_ms) return false;
        delay(10);
    }
}
