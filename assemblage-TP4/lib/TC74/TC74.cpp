#include <TC74.h>
tc74::tc74()
{
    _temp = 0;
    _adrs = 0;
}

bool tc74::begin(uint8_t adrs)
{
    _adrs = adrs;
    bool res = Wire.begin();
    return res;
}

int tc74::read()
{
    uint8_t signe = 0;
    Wire.beginTransmission(_adrs);
    Wire.write(Registre_temp);
    Wire.endTransmission();

    Wire.requestFrom(_adrs, byte(1));
    _temp = Wire.read();
    Wire.endTransmission();

    signe = _temp & 1000000;

    if (signe)
    {
        _temp = -(_temp ^ 0xFF) + 1;
    }
    return _temp;
}

bool tc74::isStandby()
{
    bool isST = 0;
    Wire.beginTransmission(_adrs);
    Wire.write(Registre_config);
    Wire.endTransmission();

    Wire.requestFrom(_adrs, byte(1));
    isST = Wire.read();
    isST = isST & 10000000; // 0 normal 1 Standby
    Wire.endTransmission();
    return isST;
}

void tc74::setStanby(bool ST)
{
    uint8_t var = 0;
    if (ST)
    {
        var = 0b10000000;
    }
    else
    {
        var = 0x00;
    }

    Wire.beginTransmission(_adrs);
    Wire.write(Registre_config);
    Wire.write(var);
    Wire.endTransmission();
}
