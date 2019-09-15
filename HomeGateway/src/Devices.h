#ifndef DEVICES_H
#define DEVICES_H

// TODO:   Version 2.0 is started from Here , and Witty Cloud Based 
// Creating Devices List Supported and thier structer so can be used for any thing

class RGBLed
{
    public:
     bool RedLedState, GreenLedState, BlueLedState;
     int RedLedPin, GreenLedPin, BlueLedPin;
    
     RGBLed(int r, int g, int b );
    //void setLedState(bool r, bool g, bool b);
   // void setAnalogColor(float r, float g, float b);

};

class NodeMCU
{

};

class ESP32DevKit1_0{

};
class WittyCloud{};



#endif


RGBLed::RGBLed(int r, int g ,int b)
{
    RedLedPin=r, BlueLedPin=b, GreenLedPin=g;

}