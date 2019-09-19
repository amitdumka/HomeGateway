/***
 *  Device.H 
 *   All Supported devices is added here 
 *   Version : 2.0
 *   Author: Amit Kumar (AKS Labs)
 *   Year : 2019
 ***/

#ifndef DEVICES_H
#define DEVICES_H

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

class InBuilt_LED
{
private:
    bool LedState = false;
    int LedPin;

public:
    ~InBuilt_LED()
    {
        free(this);
    }
    InBuilt_LED()
    {
        LedPin = D4;
        LedState = false;
    }
    InBuilt_LED(int pin, bool state = false)
    {
        LedPin = pin;
        LedState = state;
    }
    // Set State true or false of Led
    void setState(bool state) { LedState = state; }
    // Set Pin Mode to OUTPUT mode
    void setMode() { pinMode(LedPin, OUTPUT); }
    // Return state of led , true or false.
    bool  getState() {return LedState;}
    // Switch On or Off LED , true or false, and set the state
    void LedOnOff(bool onOff)
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
};

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

    void CallInSetUp(){
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
    void TongleLed(bool lights = true){
        led.LedOnOff(lights);
    }

    void OnOffRelay(bool relay = true);
    bool ReadInputSwitch();

    bool IsRelayOn();
    bool IsSwitchOn();
};


class RelaySwitch{
    protected:
    int Pin__O_Relay=0;
    int Pin_I_InputSwitch=-999;
    bool RelayState=false;
    bool SwitchState=false;
    public :
    RelaySwitch(int relayPin);
    RelaySwitch(int switchPin, int relayPin);

    void InitSwitch(){
        pinMode(Pin_O_Relay, OUTPUT);
        if(Pin_I_InputSwitch>=0)
            pinMode(Pin_I_InputSwitch,OUTPUT);
    }
    void TongleSwitch(bool state);
    void RelayOnOFF(bool state=true);
    bool IsRelayOn(){return RelayState;}
    bool IsSwitchOn(){return SwitchState;}
    void SetSwitchState(bool state=true)
    { 
        SwitchState=state;
    }
};

class InputSwitch{
    //TODO:
};

#endif
