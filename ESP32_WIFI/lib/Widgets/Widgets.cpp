#include <Arduino.h>
#include <Ticker.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Widgets.h>

// obj
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT);
GFXcanvas1 canvas(SCREEN_WIDTH, SCREEN_HEIGHT);

update(uint8_t thehour, uint8_t theminute, uint8_t thesecond, String day, uint8_t number, String month)
{
    _hour = thehour;
    _minute = theminute;
    _seconde = thesecond;
    _day = day;
    _number = number;
    _month = month;
    _angle_min = (_minute / 60) * 2 * PI + PI / 2;
    _angle_h = (_minute / 60) * 2 * PI + PI / 2;
}

AnaClock anaclock(&canvas, 32, 32, 30)
{
    _calculX(float rayon, float angle);
    _calculY(float rayon, float angle);
}

float _calculX(float rayon, float angle)
{

    return rayon * cos(angle);
}

float _calculY(float rayon, float angle)
{
    return rayon * sin(angle);
}

void draw()
{
    canvas.fillCircle(20, 20, 20, WHITE);
    canvas.fillCircle(20, 20, 16, BLACK);

    oled.drawBitmap(0, 0, , SCREEN_WIDTH, SCREEN_HEIGHT, 1, 0);
    oled.display();
}