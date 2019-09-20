#ifndef DEVICES_H
#define DEVICES_H

#include <Arduino.h>
#include "Devices/RGBLed.h"
#include "Devices/InBuiltLed.h"

// TODO:   Version 2.0 is started from Here , and Witty Cloud Based
// Creating Devices List Supported and thier structer so can be used for any thing

class NodeMCU
{
    InBuilt_LED led;
    void CallInSetUp();
    void CallInLoop();
};

class ESP32DevKit1_0
{
    InBuilt_LED led;
    void CallInSetUp();
    void CallInLoop();
};

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
    void CallInSetUp();
    void CallInLoop();

    void setColor(int r, int g, int b) {}
    void setColor(double colorcode) {}

    void readLight() {}
    bool isLightOn() { return false; }
    bool isLightDim() { return false; }
    bool isLightTooDim() { return false; }
    bool isLightTooBright() { return false; }
};

class SingleChannelEsp8266
{ // Fix Pin Devices.
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
    InBuilt_LED led;

public:
    SingleChannelEsp8266()
    {
        led = InBuilt_LED(LED_I_Pin);
    }
    ~SingleChannelEsp8266()
    {
        led.~InBuilt_LED();
        free(this);
    }

    void CallInSetUp();

    void CallInSetUp()
    {
        pinMode(LED_I_Pin, INPUT);
        pinMode(Pin_I_OC_Input, INPUT);
        pinMode(Pin_O_Relay, OUTPUT);

        TongleLed(true);
        delay(1000);
        TongleLed(false);
    }

    void CallInLoop();

    // Switch on led On or Off, True for On and False for Off
    void TongleLed(bool lights = true);
    void TongleLed(bool lights = true)
    {
        led.LedOnOff(lights);
    }

    void OnOffRelay(bool relay = true);
    bool ReadInputSwitch();

    bool IsRelayOn();
    bool IsSwitchOn();
};

class RelaySwitch
{

protected:
    int Pin_O_Relay = 0;
    int Pin_I_InputSwitch = -999; // -666 Only RelayPin is activated

    bool RelayState = false;
    bool SwitchState = false;

public:
    RelaySwitch(int relayPin)
    {

        Pin_O_Relay = relayPin;
        Pin_I_InputSwitch = -666;
    }
    RelaySwitch(int relayPin, int switchPin)
    {
        Pin_O_Relay = relayPin;
        Pin_I_InputSwitch = switchPin;
    }

    void InitSwitch()
    {
        pinMode(Pin_O_Relay, OUTPUT);
        if (Pin_I_InputSwitch >= 0)
            pinMode(Pin_I_InputSwitch, OUTPUT);
    }

    void TongleSwitch(bool state);
    void RelayOnOFF(bool state = true);

    bool IsRelayOn() { return RelayState; }
    bool IsSwitchOn() { return SwitchState; }
    void SetSwitchState(bool state = true)
    {
        SwitchState = state;
    }

    // SwitchOnOffRelay will operate and update status  of Input Switch
    void SwitchOnOffRelay(bool relayonoff, bool inputmode, bool switchmode = NULL)
    {
        if (inputmode && switchmode != IsSwitchOn())
        {

            RelayOnOFF(relayonoff);
            SetSwitchState(switchmode);
        }
        else
            RelayOnOFF(relayonoff);
    }
};

#endif
