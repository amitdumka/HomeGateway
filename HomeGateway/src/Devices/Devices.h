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

class HumanPirSensor
{

private:
    int Pin_I_Signal = -999;

protected:
    int HumanCount;
    static int HumanCouter;

public:
    HumanPirSensor(int singP);
    bool IsHumanDetected();
    bool IsHumanEntered();
    bool IsHumanExited();
    void HumanEntyExit();
    void SignalOther();
    void StartPauseStop(int mode);
    
    void CallInSetUp();
    void CallInLoop();
};

#endif

//Device Class Templetes:

/*** 
 * Use this tempelet to create your class
  class Templete_Deivce{
      private:
      int Pin_I_Pin1;
      int Pin_O_Pin1;
      protected:
      bool IsPinReaded();
      bool IsPinWrited();

      public:
      Templete_Deivce(int pin1);
      
    void CallInSetUp();
    void CallInLoop();
  };
***/