#ifndef INBUILTLED_H
#define INBUILTLED_H

#include <Arduino.h>
#include "Devices/RGBLed.h"

// TODO:   Version 2.0 is started from Here , and Witty Cloud Based
// Creating Devices List Supported and thier structer so can be used for any thing

//TODO: class is completed , Due for Formal Testing. 

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

