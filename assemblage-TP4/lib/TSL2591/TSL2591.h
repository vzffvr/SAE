#ifndef TSL2591_SENSOR_H
#define TSL2591_SENSOR_H
#include <Wire.h>
#include <Arduino.h>

#define rgs_ID 0xB2
#define C0DATAL 0b101101000
#define C0DATAH 0b101101001
#define C1DATAL 0b101101010
#define C1DATAH 0b101101011
#define rgs_ctrl 0b10100001
#define rgs_enable 0xA0

#define ena_value 0b00010011
#define dis_value 0b00000000

#define alldata_rgs 0xB4

class TSL2591
{
public:
    TSL2591();
    void begin(uint8_t adrss);
    uint8_t getId();
    void config(uint8_t gain, uint8_t time);
    void enable();
    void disable();
    uint16_t getFullSpectrum();
    uint16_t getInfraRedSpectrum();
    uint16_t getVisibleSpectrum();
    float calculateLux();

    String getString();

    enum AGain
    {
        GAIN_LOW = 0b00,
        GAIN_MEDIUM = 0b01,
        GAIN_HIGH = 0b10,
        GAIN_MAX = 0b11,
    };
    enum ATime
    {
        ATIME_100 = 0b000,
        ATIME_200 = 0b001,
        ATIME_300 = 0b010,
        ATIME_400 = 0b011,
        ATIME_500 = 0b100,
        ATIME_600 = 0b101,
    };

private:
    uint8_t Adresse;
    uint8_t _Gain;
    uint8_t _Time;
    float _Lux;
    uint32_t getAllDatas();
};
#endif