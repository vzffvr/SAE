#include <Arduino.h>

// constantes
const uint8_t LED_PIN = 13;

// prototypes
void action();

// objets

// variables globales
//*****
void action()
{
    Serial.println("bonjour");
    delay(500);
}
//*****

void setup()
{
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void loop()
{
    action();
    digitalWrite(LED_PIN, HIGH);
    action();
    digitalWrite(LED_PIN, LOW);
}
