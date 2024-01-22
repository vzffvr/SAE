#include <temperature.h>

void TC74::begin()
{
    Wire.begin();
    bool res = Wire.begin();
    if (res == false)
    {
        Serial.println("I2C mal init");
    }
}

uint8_t TC74::read()
{
    Wire.beginTransmission(TC74_adrs);
    Wire.write(Registre_temp);
    Wire.endTransmission();

    Wire.requestFrom(TC74_adrs, byte(1));
    temp = Wire.read();
    Wire.endTransmission();

    signe = temp & 1000000;

    if (signe)
    {
        temp = -(temp ^ 0xFF) + 1;
    }
    return temp;
}

bool TC74::isStandby()
{
    Wire.beginTransmission(TC74_adrs);
    Wire.write(Registre_config);
    Wire.endTransmission();

    Wire.requestFrom(TC74_adrs, byte(1));
    isST = Wire.read();
    isST = isST & 10000000; // 1 Standby 0 normal
    Wire.endTransmission();
    return isST;
}

bool TC74::setStanby(bool ST)
{
    Wire.beginTransmission(TC74_adrs);
    Wire.write(Registre_config);
    Wire.endTransmission();

    Wire.beginTransmission(TC74_adrs);
    Wire.requestFrom(TC74_adrs, byte(1));
    Wire.endTransmission();
}
