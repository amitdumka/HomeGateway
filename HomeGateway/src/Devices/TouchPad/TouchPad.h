#ifndef TOUCHPAD_H
#define TOUCHPAD_H

#include <Wire.h>
#include <TTP229.h>
#include <Arduino.h>

class TouchPad
{
private: bool isINTBased=false;
protected:
    int Pin_SDO=0;
    int Pin_SDL=0;
    int Key=0;
    unsigned int DTA;
  static  int PressedKey = 0;
    int KeyCount = 16;
    TTP229 touchPad;

public:
    TouchPad(int sdo, int sdl);
    TouchPad(int sdo, int sdl, int keycount);
    TouchPad(int sdo, int sdl, int keycount, int mode);


    //void CallInSetUp();
    void CallInLoop();

    int GetKey();
    bool IsKeyDown(byte key);
    bool IsKeyUp(byte key);
    bool IsKeyPress(byte key);
    int KeyPressed();
    uint16_t ReadKeys();
    //Version 2
    void SetUpTouchPad();
    // Int handlers section
    static void Handler();
    void Int_TouchPad();

    void KeyHandler(int presskey);

};

#endif
