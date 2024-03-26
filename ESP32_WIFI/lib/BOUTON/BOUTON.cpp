#include <BOUTON.h>
BOUTON::BOUTON()
{
    st_ = 0;
    pin_ = 0;
}

void BOUTON::begin(uint8_t pin)
{
    pin_ = pin;
    pinMode(pin_, INPUT);
    st_ = 0;
}

bool BOUTON::pressed()
{
    return digitalRead(pin_);
}

void BOUTON::wait_for_realesed()
{
    if (pressed() == true)
    {
        delay(100);
    }
}