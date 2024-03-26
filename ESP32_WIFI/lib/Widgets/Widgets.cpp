#include <Arduino.h>
#include <Ticker.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Widgets.h>
// obj
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT);
GFXcanvas1 canvas(SCREEN_WIDTH, SCREEN_HEIGHT);

AnaClock anaclock(&canvas, 32, 32, 30);

