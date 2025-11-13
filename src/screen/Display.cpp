/*
 * Display.cpp - Implémentation de la classe Display
 */

#include "Display.hpp"

Display::Display() : bus(nullptr), display(nullptr), canvas(nullptr), currentRotation(0) {
    bus = new Arduino_ESP32QSPI(PIN_CS, PIN_SCK, PIN_MOSI, PIN_MISO, PIN_DC, PIN_RST);
    display = new Arduino_AXS15231B(bus, GFX_NOT_DEFINED, 0, false, WIDTH_PORTRAIT, HEIGHT_PORTRAIT);
    canvas = new Arduino_Canvas(WIDTH_PORTRAIT, HEIGHT_PORTRAIT, display, 0, 0, 0);
}

Display::~Display() {
    if (canvas) delete canvas;
    if (display) delete display;
    if (bus) delete bus;
}

bool Display::begin() {
    if (!canvas) return false;
    
    canvas->begin();
    
    // Active le rétro-éclairage
    pinMode(PIN_BL, OUTPUT);
    digitalWrite(PIN_BL, HIGH);
    
    return true;
}

void Display::setRotation(uint8_t rotation) {
    if (rotation > 3) rotation = 0;
    currentRotation = rotation;
    canvas->setRotation(rotation);
}

uint16_t Display::getWidth() {
    return canvas->width();
}

uint16_t Display::getHeight() {
    return canvas->height();
}

void Display::setBacklight(bool enabled) {
    digitalWrite(PIN_BL, enabled ? HIGH : LOW);
}

void Display::fillScreen(uint16_t color) {
    canvas->fillScreen(color);
}

void Display::drawPixel(int16_t x, int16_t y, uint16_t color) {
    canvas->drawPixel(x, y, color);
}

void Display::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    canvas->drawLine(x0, y0, x1, y1, color);
}

void Display::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    canvas->drawRect(x, y, w, h, color);
}

void Display::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    canvas->fillRect(x, y, w, h, color);
}

void Display::drawCircle(int16_t x, int16_t y, int16_t r, uint16_t color) {
    canvas->drawCircle(x, y, r, color);
}

void Display::fillCircle(int16_t x, int16_t y, int16_t r, uint16_t color) {
    canvas->fillCircle(x, y, r, color);
}

void Display::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    canvas->drawTriangle(x0, y0, x1, y1, x2, y2, color);
}

void Display::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    canvas->fillTriangle(x0, y0, x1, y1, x2, y2, color);
}

void Display::setCursor(int16_t x, int16_t y) {
    canvas->setCursor(x, y);
}

void Display::setTextColor(uint16_t color) {
    canvas->setTextColor(color);
}

void Display::setTextColor(uint16_t color, uint16_t bgColor) {
    canvas->setTextColor(color, bgColor);
}

void Display::setTextSize(uint8_t size) {
    canvas->setTextSize(size);
}

void Display::print(const char* text) {
    canvas->print(text);
}

void Display::print(const String& text) {
    canvas->print(text);
}

void Display::print(int number) {
    canvas->print(number);
}

void Display::print(unsigned int number) {
    canvas->print(number);
}

void Display::print(long number) {
    canvas->print(number);
}

void Display::print(unsigned long number) {
    canvas->print(number);
}

void Display::print(float number, int decimals) {
    canvas->print(number, decimals);
}

void Display::println(const char* text) {
    canvas->println(text);
}

void Display::println(const String& text) {
    canvas->println(text);
}

void Display::println(int number) {
    canvas->println(number);
}

void Display::println(unsigned int number) {
    canvas->println(number);
}

void Display::println(long number) {
    canvas->println(number);
}

void Display::println(unsigned long number) {
    canvas->println(number);
}

void Display::println(float number, int decimals) {
    canvas->println(number, decimals);
}

void Display::flush() {
    canvas->flush();
}

void Display::clear() {
    canvas->fillScreen(COLOR_BLACK);
}
