/***
 *  Devices.RGBLed.H 
 *   All Supported devices is added here  RGBLed
 *   Version : 2.0
 *   Author: Amit Kumar (AKS Labs)
 *   Year : 2019
 ***/

#ifndef RGBLED_H
#define RGBLED_H

#include <Arduino.h>

// TODO:   Version 2.0 is started from Here , and Witty Cloud Based
// Creating Devices List Supported and thier structer so can be used for any thing

class RGBLed
{
private:
    bool RedLedState, GreenLedState, BlueLedState;
    int RedLedPin, GreenLedPin, BlueLedPin;

public:
    RGBLed() { RedLedPin = D8, BlueLedPin = D6, GreenLedPin = D7; }
    RGBLed(int r, int g, int b);

    //void setLedState(bool r, bool g, bool b);
    // void setAnalogColor(float r, float g, float b);
};


#endif
//TODO: Imolement RGBLed
RGBLed::RGBLed(int r, int g, int b)
{
    RedLedPin = r, BlueLedPin = b, GreenLedPin = g;
}
