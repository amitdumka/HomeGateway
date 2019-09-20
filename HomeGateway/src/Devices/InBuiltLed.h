#ifndef INBUILTLED_H
#define INBUILTLED_H

#include <Arduino.h>
#include "Devices/RGBLed.h"

// TODO:   Version 2.0 is started from Here , and Witty Cloud Based
// Creating Devices List Supported and thier structer so can be used for any thing

class InBuilt_LED
{
private:
    bool LedState = false;
    int LedPin;

public:
    ~InBuilt_LED();
    InBuilt_LED();
    InBuilt_LED(int pin, bool state = false);
    // Set State true or false of Led
    void setState(bool state);
    // Set Pin Mode to OUTPUT mode
    void setMode();
    // Return state of led , true or false.
    bool getState();
    // Switch On or Off LED , true or false, and set the state
    void LedOnOff(bool onOff);
};

#endif

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