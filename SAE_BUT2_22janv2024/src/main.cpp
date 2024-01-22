#include <Arduino.h>
#include <wire.h>
#include <Ticker.h>

// constantes
const uint8_t LED_PIN = 13;

// prototypes
void action();

// objets
Ticker ticker(action, 500, 0, MILLIS);
// variables globales
//*****
void action()
{
    Serial.println("bonjour");
    uint8_t st = digitalRead(LED_PIN);
    delay(500);
    if (st)
    {
        digitalWrite(LED_PIN, 0);
    }
    else
    {
        digitalWrite(LED_PIN, 1);
    }
}
//*****

void setup()
{
    ticker.start();
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    /* bool res = Wire.begin();
    if (res == false)
    {
    }
 */
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
