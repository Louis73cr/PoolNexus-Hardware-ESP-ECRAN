/*
 * TouchScreen.cpp - Implémentation de la classe TouchScreen
 */

#include "TouchScreen.hpp"

// -------- CONSTRUCTEUR --------

TouchScreen::TouchScreen() 
    : initialized(false)
    , screenRotation(0)
{
}

// -------- INITIALISATION --------

bool TouchScreen::begin() {
    // Initialise le bus I2C
    Wire.begin(PIN_SDA, PIN_SCL);
    Wire.setClock(I2C_CLOCK);
    
    // Configure les pins
    pinMode(PIN_INT, INPUT_PULLUP);
    pinMode(PIN_RST, OUTPUT);
    
    // Reset matériel du contrôleur tactile
    digitalWrite(PIN_RST, LOW);
    delay(200);
    digitalWrite(PIN_RST, HIGH);
    delay(200);
    
    // Vérifie que le contrôleur répond
    Wire.beginTransmission(I2C_ADDR);
    if (Wire.endTransmission() != 0) {
        Serial.println("Erreur: Contrôleur tactile non détecté!");
        return false;
    }
    
    initialized = true;
    Serial.println("Contrôleur tactile initialisé");
    return true;
}

void TouchScreen::setRotation(uint8_t rotation) {
    if (rotation > 3) rotation = 0;
    screenRotation = rotation;
}

// -------- LECTURE TACTILE --------

bool TouchScreen::sendReadCommand() {
    // Commande de lecture propriétaire du contrôleur
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

bool TouchScreen::readTouchData(uint8_t* data) {
    size_t dataSize = MAX_TOUCH_POINTS * 6 + 2;
    
    if (Wire.requestFrom(I2C_ADDR, dataSize) != dataSize) {
        return false;
    }
    
    for (size_t i = 0; i < dataSize; i++) {
        data[i] = Wire.read();
    }
    
    return true;
}

bool TouchScreen::decodeTouchData(uint8_t* data, uint16_t& x, uint16_t& y) {
    // Vérifie qu'un toucher est détecté
    if (data[1] == 0 || data[1] > MAX_TOUCH_POINTS) {
        return false;
    }
    
    // Décode les coordonnées (12 bits répartis sur 2 octets)
    uint16_t rawX = ((data[2] & 0x0F) << 8) | data[3];
    uint16_t rawY = ((data[4] & 0x0F) << 8) | data[5];
    
    // Filtre anti-aberration
    if (rawX > 500 || rawY > 500) {
        return false;
    }
    
    // Applique la calibration selon la rotation
    calibrateCoordinates(rawX, rawY, x, y);
    
    return true;
}

void TouchScreen::calibrateCoordinates(uint16_t rawX, uint16_t rawY, uint16_t& x, uint16_t& y) {
    switch (screenRotation) {
        case 0: // Portrait
            x = rawY;
            y = map(rawX, 0, 320, 320, 0);
            break;
            
        case 1: // Paysage (rotation utilisée par défaut)
            x = rawY;
            y = map(rawX, 0, 320, 320, 0);
            break;
            
        case 2: // Portrait inversé
            x = map(rawY, 0, 480, 480, 0);
            y = rawX;
            break;
            
        case 3: // Paysage inversé
            x = map(rawY, 0, 480, 480, 0);
            y = map(rawX, 0, 320, 0, 320);
            break;
    }
}

bool TouchScreen::isTouched() {
    if (!initialized) return false;
    
    uint16_t x, y;
    return getTouchPoint(x, y);
}

bool TouchScreen::getTouchPoint(uint16_t& x, uint16_t& y) {
    if (!initialized) return false;
    
    // Envoie la commande de lecture
    if (!sendReadCommand()) {
        return false;
    }
    
    // Lit les données
    uint8_t data[MAX_TOUCH_POINTS * 6 + 2] = {0};
    if (!readTouchData(data)) {
        return false;
    }
    
    // Décode et calibre les coordonnées
    return decodeTouchData(data, x, y);
}

bool TouchScreen::waitForTouch(uint32_t timeout_ms) {
    uint32_t startTime = millis();
    
    while (true) {
        if (isTouched()) {
            return true;
        }
        
        // Vérifie le timeout
        if (timeout_ms > 0 && (millis() - startTime) >= timeout_ms) {
            return false;
        }
        
        delay(10);
    }
}

bool TouchScreen::waitForRelease(uint32_t timeout_ms) {
    uint32_t startTime = millis();
    
    while (true) {
        if (!isTouched()) {
            return true;
        }
        
        // Vérifie le timeout
        if (timeout_ms > 0 && (millis() - startTime) >= timeout_ms) {
            return false;
        }
        
        delay(10);
    }
}
