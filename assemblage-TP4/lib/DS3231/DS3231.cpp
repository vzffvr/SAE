#include <DS3231.h>

const char *jour[] = {"Dim", "Lun", "Mard", "Mer", "jeu", "Ven", "Sam"};
const char *mois[] = {"Jan", "Fev", "Mars", "Avril", "Mai", "Juin", "Juil", "Aout", "Sept", "Oct", "Nov", "Dec"};

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

// recevoir
uint8_t DS3231::BCD_to_BIN(uint8_t val)
{
    uint8_t A = val / 16;
    A = A * 10;
    uint8_t B = val % 16;
    uint8_t S = A + B;
    return S;
}

// envoi
uint8_t DS3231::BIN_to_BCD(uint8_t val)
{
    uint8_t A = val / 10;
    A = A * 16;
    uint8_t B = val % 10;
    uint8_t S = A + B;

    return S;
}

uint8_t DS3231::get_sec()
{
    uint8_t secondes;
    Wire.beginTransmission(_adrs);
    Wire.write(rgs_sec);
    Wire.endTransmission();

    Wire.requestFrom(_adrs, byte(1));
    secondes = Wire.read();
    Wire.endTransmission();
    secondes = BCD_to_BIN(secondes);

    return secondes;
}

uint8_t DS3231::get_min()
{
    uint8_t minutes;
    Wire.beginTransmission(_adrs);
    Wire.write(rgs_min);
    Wire.endTransmission();

    Wire.requestFrom(_adrs, byte(1));
    minutes = Wire.read();
    Wire.endTransmission();
    minutes = BCD_to_BIN(minutes);

    return minutes;
}

uint8_t DS3231::get_hour()
{
    uint8_t heure;
    Wire.beginTransmission(_adrs);
    Wire.write(rgs_heure);
    Wire.endTransmission();

    Wire.requestFrom(_adrs, byte(1));
    heure = Wire.read();
    Wire.endTransmission();
    heure = BCD_to_BIN(heure);

    return heure;
}

String DS3231::get_jour()
{
    uint8_t day;
    Wire.beginTransmission(_adrs);
    Wire.write(rgs_day);
    Wire.endTransmission();

    Wire.requestFrom(_adrs, byte(1));
    day = BCD_to_BIN(Wire.read());
    Wire.endTransmission();

    String var = jour[day - 1];

    return var;
}

String DS3231::get_mois()
{
    uint8_t month;
    Wire.beginTransmission(_adrs);
    Wire.write(rgs_mois);
    Wire.endTransmission();

    Wire.requestFrom(_adrs, byte(1));
    month = BCD_to_BIN(Wire.read());
    Wire.endTransmission();

    String var = mois[month - 1];

    return var;
}

uint8_t DS3231::get_nb()
{
    uint8_t number;
    Wire.beginTransmission(_adrs);
    Wire.write(rgs_date);
    Wire.endTransmission();

    Wire.requestFrom(_adrs, byte(1));
    number = Wire.read();
    Wire.endTransmission();
    number = BCD_to_BIN(number);

    return number;
}

void DS3231::set_Time(uint8_t hour, uint8_t minutes, uint8_t sec)
{
    Wire.beginTransmission(_adrs);
    Wire.write(rgs_sec);
    Wire.write(BIN_to_BCD(sec));
    Wire.write(BIN_to_BCD(minutes));
    Wire.write(BIN_to_BCD(hour));
    Wire.endTransmission();
}

void DS3231::set_Date(uint8_t day, uint8_t number, uint8_t month)
{
    Wire.beginTransmission(_adrs);
    Wire.write(rgs_day);
    Wire.write(BIN_to_BCD(day));
    Wire.write(BIN_to_BCD(number));
    Wire.write(BIN_to_BCD(month));
    Wire.endTransmission();
}

String DS3231::get_StringTime()
{
    uint8_t hour = get_hour();
    uint8_t minute = get_min();
    String res = "";
    if (minute < 9)
    {
        res = res + String(hour) + ":" + "0" + String(minute);
    }
    else
    {
        res = res + String(hour) + ":" + String(minute);
    }
    return res;
}

String DS3231::get_StringDate()
{
    uint8_t nb = get_nb();

    String res = "";

    res = res + String(nb) + " " + get_mois();

    return res;
}