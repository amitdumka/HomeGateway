#ifndef WITTY_CLOUD_H
#define WITTY_CLOUD_H

#include "RGBLed.h"
#include "InBuiltLed.h"

class WittyCloud
{
protected:
    const int LDRPin = A0;   // Analog , Light detector /Lux
    const int REDPin = D8;   //15
    const int GREENPin = D6; //12
    const int BLUEPin = D7;  //13

    const int Led_I_Pin = 2; //D4  //Inbuilt Led pin

    const int Pin_IO_1 = 5;  //D1   //free
    const int Pin_IO_2 = 16; //D0 //free
    const int Pin_IO_3 = 14; //D5  //free

    const int Pin_O_Flash = 0;  //D3; //flash  only output
    const int Pin_I_Button = 4; //D2  //button

    const int Pin_O_TX = 1; //TX;    // TX Pin
    const int Pin_I_RX = 3; //Rx;    //RX pin
    RGBLed rgbLed;
    InBuilt_LED led;

public:
    WittyCloud()
    {
        rgbLed = RGBLed(REDPin, GREENPin, BLUEPin);
        led = InBuilt_LED(led);
    }
    void CallInSetUp(); //TODO: Need to implementeds
    void CallInLoop();

    void setColor(int r, int g, int b) {}
    void setColor(double colorcode) {}

    void readLight() {}
    bool isLightOn() { return false; }
    bool isLightDim() { return false; }
    bool isLightTooDim() { return false; }
    bool isLightTooBright() { return false; }
};

#endif