#ifndef DEVICES_H
#define DEVICES_H

#include <Arduino.h>
#include "Devices/RGBLed.h"
#include "Devices/InBuiltLed.h"
#include "Devices/WittyCloud.h"
#include "Devices/RelaySwitch.h"
#include "Devices/SingleChannelESP8266.h"


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

#endif
