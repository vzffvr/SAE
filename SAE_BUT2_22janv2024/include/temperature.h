#include <Arduino.h>
#include <Wire.h>

#define TC74_adrs 72
#define Registre_temp 0x00
#define Registre_config 0x01

class TC74
{
private:
    uint8_t temp;
    uint8_t signe;
    uint8_t isST;

public:
    void begin();
    uint8_t read();
    bool isStandby();
    bool setStanby(bool ST);
};
