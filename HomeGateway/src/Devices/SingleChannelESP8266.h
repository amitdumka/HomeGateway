#ifndef SINGLECHANNEL_ESP8266_H
#define SINGLECHANNEL_ESP8266_H
#include "RGBLed.h"
#include "InBuiltLed.h"

/// SingleChannelESP8266 can be used for one relay switch with octo input
class SingleChannelEsp8266
{
    // Fixed Pin Devices.
    // Esp8266 pins.
    // #define ESP8266_GPIO2    2 // Blue LED.
    // #define ESP8266_GPIO4    4 // Relay control.
    // #define ESP8266_GPIO5    5 // Optocoupler input.
    // #define LED_PIN          ESP8266_GPIO2

    const int LED_I_Pin = 2;

    const int Pin_O_Relay = 4;
    const int Pin_I_OC_Input = 5;

    bool isRelayOn = false;
    bool isSwitchOn = false;

protected:
    InBuilt_LED led; // InBuilt_LED Lib from Aks Labs. Version 2.0

public:
    SingleChannelEsp8266();
    ~SingleChannelEsp8266();
    void CallInSetUp();

    void CallInLoop();

    // Switch on led On or Off, True for On and False for Off
    void TongleLed(bool lights = true);

    void OnOffRelay(bool relay = true);
    bool ReadInputSwitch();

    bool IsRelayOn();
    bool IsSwitchOn();
};

#endif