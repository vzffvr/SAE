#ifndef BOUTON_H
#define BOUTON_H

#include <Arduino.h>

class BOUTON
{
public:
    BOUTON();
    void begin(uint8_t pin);
    bool pressed();
    void wait_for_realesed();

private:
    uint8_t pin_;
    bool st_;
};
#endif