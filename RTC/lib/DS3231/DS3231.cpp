#include <DS3231.h>

DS3231::DS3231()
{
    _adrs = 0;
}

bool DS3231::begin(uint8_t adrs)
{
    _adrs = adrs;
    bool res = Wire.begin();
    if (!res)
    {
        Serial.println("mal init");
    } 
    return res;
}

uint8_t DS3231::BCD_to_BIN(uint8_t val)
{
}

uint8_t DS3231::BIN_to_BCD(uint8_t val)
{

}
