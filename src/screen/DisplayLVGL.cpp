/**
 * @file DisplayLVGL.cpp
 * @brief Implementation Display for LVGL
 */

#include "DisplayLVGL.hpp"

DisplayLVGL* DisplayLVGL::instance = nullptr;

/**
 * @brief Construct the DisplayLVGL object and initialize display/canvas/bus.
 *
 * This constructor sets up the QSPI bus, display driver, and canvas for JC3248W535C.
 * The canvas is used to avoid flickering and uses the native display size (320x480).
 */
DisplayLVGL::DisplayLVGL() : bus(nullptr), display(nullptr), canvas(nullptr), buf1(nullptr), buf2(nullptr), disp(nullptr) {
    instance = this;
    
    bus = new Arduino_ESP32QSPI(PIN_CS, PIN_SCK, PIN_MOSI, PIN_MISO, PIN_DC, PIN_RST);
    display = new Arduino_AXS15231B(bus, GFX_NOT_DEFINED, 0, false, WIDTH_PORTRAIT, HEIGHT_PORTRAIT);
    canvas = new Arduino_Canvas(WIDTH_PORTRAIT, HEIGHT_PORTRAIT, display, 0, 0, 0);
}

/**
 * @brief Destructor for DisplayLVGL. Frees allocated resources.
 */
DisplayLVGL::~DisplayLVGL() {
    if (buf1) free(buf1);
    if (buf2) free(buf2);
    if (canvas) delete canvas;
    if (display) delete display;
    if (bus) delete bus;
}

/**
 * @brief Initialize the display, canvas, and LVGL library.
 *
 * Sets up backlight, initializes canvas and LVGL, allocates buffers, and registers the display driver.
 * @return true if initialization succeeds, false otherwise.
 */
bool DisplayLVGL::begin() {
    Serial.println("Initializing display...");
    
    if (!canvas) {
        Serial.println("ERROR: Canvas is NULL!");
        return false;
    }
    
    pinMode(PIN_BL, OUTPUT);
    digitalWrite(PIN_BL, HIGH);
    delay(50);
    
    if (!canvas->begin()) {
        Serial.println("Canvas init failed!");
        return false;
    }
    Serial.println("Canvas/Display hardware OK");
    
    canvas->setRotation(1);
    canvas->fillScreen(BLACK);
    canvas->flush();
    
    delay(50);
    Serial.println("Backlight ON");
    
    lv_init();
    Serial.println("LVGL init OK");
    
    uint32_t bufSize = 480 * 320 / 10;
    buf1 = (lv_color_t*)heap_caps_malloc(bufSize * sizeof(lv_color_t), MALLOC_CAP_DMA);
    buf2 = (lv_color_t*)heap_caps_malloc(bufSize * sizeof(lv_color_t), MALLOC_CAP_DMA);
    
    if (!buf1 || !buf2) {
        Serial.println("LVGL buffer allocation failed!");
        return false;
    }
    
    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, bufSize);
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = 480;
    disp_drv.ver_res = 320;
    disp_drv.flush_cb = display_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.user_data = this;
    disp = lv_disp_drv_register(&disp_drv);
    if (!disp) {
        Serial.println("LVGL display registration failed!");
        return false;
    }
    
    Serial.println("LVGL initialized successfully!");
    return true;
}

/**
 * @brief LVGL flush callback to transfer a region of pixels to the display.
 *
 * Uses the canvas to draw a region and flushes it to the screen. Called by LVGL when a region needs updating.
 * @param disp_drv Pointer to the LVGL display driver.
 * @param area Area to update.
 * @param color_p Pointer to pixel data.
 */
void DisplayLVGL::display_flush(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p) {
    DisplayLVGL* self = (DisplayLVGL*)disp_drv->user_data;
    
    if (!self || !self->canvas) {
        lv_disp_flush_ready(disp_drv);
        return;
    }
    
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    
    if (area->x1 < 0 || area->y1 < 0 || area->x2 >= 480 || area->y2 >= 320) {
        lv_disp_flush_ready(disp_drv);
        return;
    }
    if (w == 0 || h == 0 || w > 480 || h > 320) {
        lv_disp_flush_ready(disp_drv);
        return;
    }
    self->canvas->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t*)color_p, w, h);
    self->canvas->flush();
    
    lv_disp_flush_ready(disp_drv);
}

/**
 * @brief Main loop for LVGL tick and timer handling.
 *
 * Should be called regularly to keep LVGL running and responsive.
 */
void DisplayLVGL::loop() {
    static uint32_t last = millis();
    uint32_t now = millis();
    uint32_t diff = now - last;
    if (diff > 0) {
        lv_tick_inc(diff);
        last = now;
    }
    lv_timer_handler();
}

/**
 * @brief Enable or disable the display backlight.
 *
 * @param enabled True to turn on, false to turn off.
 */
void DisplayLVGL::setBacklight(bool enabled) {
    digitalWrite(PIN_BL, enabled ? HIGH : LOW);
}
