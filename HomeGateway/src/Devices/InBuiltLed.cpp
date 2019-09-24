#include "InBuiltLed.h"

InBuilt_LED::~InBuilt_LED()
{
    free(this);
}
InBuilt_LED::InBuilt_LED()
{
    LedPin = D4;
    LedState = false;
}
InBuilt_LED::InBuilt_LED(int pin, bool state = false)
{
    LedPin = pin;
    LedState = state;
    pinMode(LedPin,OUTPUT);  // SetInput Mode while creating Objected.
}

// Set State true or false of Led
void InBuilt_LED::setState(bool state) { LedState = state; }

// Set Pin Mode to OUTPUT mode
void InBuilt_LED::setMode() { pinMode(LedPin, OUTPUT); }

// Return state of led , true or false.
bool InBuilt_LED::getState() { return LedState; }

// Switch On or Off LED , true or false, and set the state
void InBuilt_LED::LedOnOff(bool onOff)
{
    if (onOff)
    {
        digitalWrite(LedPin, HIGH);
        LedState = true;
    }
    else
    {
        digitalWrite(LedPin, LOW);
        LedState = false;
    }
}