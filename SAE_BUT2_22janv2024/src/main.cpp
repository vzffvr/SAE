#include <Arduino.h>
#include <wire.h>
#include <Ticker.h>
#include <TC74.h>

#define adrs_TC74 72
// constantes
const uint8_t LED_PIN = 13;

// prototypes
void action();

// objets
tc74 TC74;
Ticker ticker(action, 2000, 0, MILLIS);
// variables globales
int temperature;
//*****
void action()
{
    temperature = TC74.read();
    Serial.println("Temperature");
    Serial.println(temperature);
}

void setup()
{

    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    TC74.begin(adrs_TC74);
    TC74.setStanby(false);

    ticker.start();

    /* if (!TC74.isStandby())
    {
        TC74.setStanby(false);
    }
    */
}

void loop()
{
    ticker.update();
}
