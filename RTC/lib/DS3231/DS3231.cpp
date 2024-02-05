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


// a essayer BCD to binaire
// Fonction pour convertir un chiffre BCD en binaire
int bcdToBinary(int bcdDigit) {
    return ((bcdDigit / 10) * 0b1010) + (bcdDigit % 10);
}

// Fonction pour convertir un nombre BCD en binaire
int bcdToBinaryConverter(int bcdNumber) {
    int binaryResult = 0;
    int base = 1;

    while (bcdNumber > 0) {
        binaryResult += bcdToBinary(bcdNumber % 16) * base;
        bcdNumber /= 16;
        base *= 100;
    }

    return binaryResult;
}


// Fonction pour convertir un chiffre Binaire to BCD
// Fonction pour convertir un chiffre binaire en BCD
int binaryToBcd(int binaryDigit) {
    return ((binaryDigit / 10) << 4) + (binaryDigit % 10);
}

// Fonction pour convertir un nombre binaire en BCD
int binaryToBcdConverter(int binaryNumber) {
    int bcdResult = 0;
    int base = 1;

    while (binaryNumber > 0) {
        bcdResult += binaryToBcd(binaryNumber % 10000) * base;
        binaryNumber /= 10000;
        base *= 0x10;
    }

    return bcdResult;
}
