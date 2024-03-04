#include <Arduino.h>
#include <Ticker.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Widgets.h>
//
#include <images.h>
const uint32_t PERIOD = 1000;
// obj
Ticker ticker(action, PERIOD, 0, MILLIS);
GFXcanvas1 canvas(OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT);
AnaClock anaclock(&canvas, 32, 32, 30);

//*********************
void action()
{
    //
    anaclock.update(rtc.getHour(), rtc.getMinutes(), rtc.getMinutes(), rtc.getDay(), rtc.getNum(),
                    rtc.getMounth());
    anaclock.draw();
    oled.drawBitmap(0, 0, canvas.getBuffer(), OLED_SCREEN_WIDTH,
                    OLED_SCREEN_HEIGHT, 1, 0);
    oled.display();