#ifndef WIDGETS_H
#define WIDGETS_H
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <image.h>
//*********************
// anaclock widget
//*********************
class AnaClock
{
public:
    // constructor
    AnaClock(GFXcanvas1 *pcanvas, uint16_t centerX, uint16_t centerY, uint16_t radius);
    void update(uint8_t thehour, uint8_t theminute, uint8_t thesecond, String day,
                uint8_tnumber, String month);
    void draw();

private:
    void _drawBackground();
    void _drawHour();
    void _drawMinute();
    void _drawSecond();
    void _drawDate();
    float _calculX(float rayon, float angle);
    float _calculY(float rayon, float angle);
    uint16_t _radius;
    uint16_t _centerX;
    uint16_t _centerY;
    float _hour;
    float _minute;
    float _second;
    String _day;
    uint8_t _number;
    String _month;
    GFXcanvas1 *_canvas;
};
//*********************
// gauge widget
//*********************
class Gauge
{
};
#endif