#ifndef TC74_H
#define TC74_H

#include <Arduino.h>
#include <Wire.h>

#define Registre_temp 0x00
#define Registre_config 0x01

class tc74
{

public:
    tc74();
    bool begin(uint8_t adrs);
    int read();
    bool isStandby();
    void setStanby(bool ST);

private:
    int _temp;
    uint8_t _adrs;
};
#endif