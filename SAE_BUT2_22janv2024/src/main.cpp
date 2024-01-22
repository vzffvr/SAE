#include <Arduino.h>
#include <wire.h>
#include <Ticker.h>
#include <temperature.h>

// constantes
const uint8_t LED_PIN = 13;
#define adresse 1001 000

// prototypes
void action();
void TCM102_begin();

// objets
TC74 tc74;
Ticker ticker(action, 2000, 0, MILLIS);
// variables globales
//*****
void action()
{
    Serial.println("Temperature");
    Serial.println(tc74.read());
    Serial.println("standby");
    Serial.println(tc74.isStandby());
}

//*****

void setup()
{
    ticker.start();
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    tc74.begin();
}

void loop()
{
    /* Wire.beginTransmission(0x45);
    Wire.write(3);
    Wire.endTransmission();
    Wire.requestFrom(0x45, byte(1));
    uint8_t val = Wire.read();
    Wire.endTransmission(); */

    ticker.update();
}
