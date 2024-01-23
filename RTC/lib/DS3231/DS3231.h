#ifndef DS3231_H
#define DS3231_H

#include <Arduino.h>
#include <Wire.h>

#define rgs_sec 0x00
#define rgs_min 0x01
#define rgs_heure 0x02
#define rgs_day 0x03
#define rgs_date 0x04

class DS3231
{

public:
    DS3231();
    bool begin(uint8_t adrs);
    uint8_t get_sec();

    uint8_t BCD_to_BIN(uint8_t val);
    uint8_t BIN_to_BCD(uint8_t val);

private:
    uint8_t _adrs;
};
#endif