#include <TSL2591.h>

TSL2591::TSL2591()
{
    Adresse = 0x00;
    _Gain = 0;
    _Time = 0;
}

void TSL2591::begin(uint8_t adrss)
{
    Wire.begin();
    Adresse = adrss;
}

uint8_t TSL2591::getId()
{
    uint8_t id = 0;
    Wire.beginTransmission(Adresse);
    Wire.write(rgs_ID);
    Wire.endTransmission();

    Wire.requestFrom(Adresse, byte(1));
    id = Wire.read();
    Wire.endTransmission();
    return id;
}

void TSL2591::config(uint8_t gain, uint8_t time)
{
    _Gain = gain;
    _Time = time;

    uint8_t msg = 0x00;
    uint8_t return_msg = 0x00;

    msg = gain << 4;
    msg = msg | time;
    // Serial.println(msg);

    Wire.beginTransmission(Adresse);
    Wire.write(rgs_ctrl);
    Wire.write(msg);
    Wire.endTransmission();

    /* Wire.requestFrom(Adresse, byte(1));
    return_msg = Wire.read();
    Wire.endTransmission();

    Serial.println("return_msg");
    Serial.println(return_msg); */
}

void TSL2591::enable()
{
    Wire.beginTransmission(Adresse);
    Wire.write(rgs_enable);
    Wire.write(0b00010011);
    Wire.endTransmission();

    // Serial.println("Enabling captor");
}

void TSL2591::disable()
{
    Wire.beginTransmission(Adresse);
    Wire.write(rgs_enable);
    Wire.write(0b00000000);
    Wire.endTransmission();

    // Serial.println("Disabling captor");
}

uint32_t TSL2591::getAllDatas()
{
    uint8_t datach0l = 0x00;
    uint8_t datach0h = 0x00;
    uint16_t data_ch0 = 0x0000;

    uint8_t datach1l = 0x00;
    uint8_t datach1h = 0x00;
    uint16_t data_ch1 = 0x0000;

    uint32_t alldata = 0x00000000;

    enable();

    switch (_Time)
    {
    case ATIME_100:
        delay(120);
        break;
    case ATIME_200:
        delay(220);
        break;
    case ATIME_300:
        delay(320);
        break;
    case ATIME_400:
        delay(420);
        break;
    case ATIME_500:
        delay(520);
        break;
    case ATIME_600:
        delay(620);
        break;
    default:
        delay(120);
        break;
    }

    Wire.beginTransmission(Adresse);
    Wire.write(alldata_rgs);
    Wire.endTransmission();

    Wire.requestFrom(Adresse, byte(4));
    datach0l = Wire.read();
    datach0h = Wire.read();
    datach1l = Wire.read();
    datach1h = Wire.read();
    Wire.endTransmission();

    disable();

    data_ch0 = datach0h << 8 | datach0l;
    data_ch1 = datach1h << 8 | datach1l;
    // Serial.printf("la valeur de ch0 est : %d \n\r", data_ch0);
    //  Serial.printf("la valeur de ch1 est : %d \n\r", data_ch1);
    //  Serial.println(data_ch0);
    //  Serial.println(data_ch1);

    alldata = data_ch0 << 16 | data_ch1;
    return alldata;
}

uint16_t TSL2591::getFullSpectrum()
{
    uint32_t alldata = getAllDatas();

    uint16_t ch0 = alldata >> 16;
    // Serial.println(ch0);
    return ch0;
}

uint16_t TSL2591::getInfraRedSpectrum()
{
    uint32_t alldata = getAllDatas();

    uint16_t ch1 = alldata & 0x00FF;
    // Serial.println(ch1);
    return ch1;
}

uint16_t TSL2591::getVisibleSpectrum()
{
    Serial.printf("la valeur de ch0 est : %d \n\r", getFullSpectrum());
    Serial.printf("la valeur de ch1 est : %d \n\r", getInfraRedSpectrum());
    uint16_t visible = getFullSpectrum() - getInfraRedSpectrum();
    Serial.printf("la valeur de visible est : %d \n\r", visible);

    return visible;
} // Fait par augustin

float TSL2591::calculateLux()
{
    float cpl = 0;
    float _temps = 0;
    float _gain = 0;
    float lux = 0;
    uint16_t ch0 = getFullSpectrum();
    uint16_t ch1 = getInfraRedSpectrum();

    switch (_Time)
    {
    case ATIME_100:
        _temps = 100.0;
        break;
    case ATIME_200:
        _temps = 200.0;
        break;
    case ATIME_300:
        _temps = 300.0;
        break;
    case ATIME_400:
        _temps = 400.0;
        break;
    case ATIME_500:
        _temps = 500.0;
        break;
    case ATIME_600:
        _temps = 600.0;
        break;
    default:
        break;
    }

    switch (_Gain)
    {
    case GAIN_LOW:
        _gain = 1.0;
        break;
    case GAIN_MEDIUM:
        _gain = 25.0;
        break;
    case GAIN_HIGH:
        _gain = 428.0;
        break;
    case GAIN_MAX:
        _gain = 9876.0;
        break;
    default:
        break;
    }

    cpl = (_gain * _temps) / 408.0;
    lux = ((ch0 - ch1) * (1 - ch1 / ch0)) / cpl;

    _Lux = lux;
    return lux;
}

String TSL2591::getString()
{
    calculateLux();
    String res = "";
    res = res + String(_Lux) + "Lux";
    Serial.println(res);
    return res;
}
