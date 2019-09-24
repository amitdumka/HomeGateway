#ifndef TOUCHPAD_H
#define TOUCHPAD_H

#include <Wire.h>
#include <TTP229.h>
#include <Arduino.h>

class TouchPad16 : public TouchPad
{

private:
    //TODO: Merge this two class as much possible so dont have to bother much. 
public:
    void Handler();
    void Int_TouchPad();
    void Loopper();
    void KeyHandler(int presskey);

};

class TouchPad
{

protected:
    static int Pin_SDO;
    static int Pin_SDL;

    static int Key;       //  Key 1 to 16 (No Key=0 is optional)
    static boolean Touch; //1=On 0=Off
    static boolean In;
    static unsigned int DTA;
    static unsigned int DTB;

    int P_Address;
    int PressedKey = 0;

    TTP229 touchPad;
    int KeyCount = 16;

public:
    TouchPad(int sdo, int sdl);
    TouchPad(int sdo, int sdl, int keycount);

    void CallInSetUp();
    void CallInLoop();

    int GetKey()
    {
        return touchPad.getKey();
    }

    bool IsKeyDown(byte key) { return touchPad.isKeyDown(key); }
    bool IsKeyUp(byte key) { return touchPad.isKeyUp(key); }
    bool IsKeyPress(byte key) { return touchPad.isKeyPress(key); }

    /// Returns which key is pressed.
    int KeyPressed()
    {
        for (int i = 0; i < KeyCount; i++)
        {
            if (touchPad.isKeyPress(i))
                return i;
        }
    }

    uint16_t ReadKeys() { return touchPad.readKeys(); }

    //Version 2

    void SetUpTouchPad();
    static void Int_Handler();
};

#endif

int TouchPad::Key = 0;       //  Key 1 to 16 (No Key=0 is optional)
boolean TouchPad::Touch = 0; //1=On 0=Off
boolean TouchPad::In;
unsigned int TouchPad::DTA = 0;
unsigned int TouchPad::DTB = 0;

void TouchPad::CallInLoop()
{
    touchPad.readKeys();

    //Static call interput based
    yield();
    ESP.wdtFeed();
}

TouchPad::TouchPad(int sdo, int sdl)
{
    Pin_SDL = sdl;
    Pin_SDO = sdo;
}
TouchPad::TouchPad(int sdo, int sdl, int keycount)
{
    Pin_SDL = sdl;
    Pin_SDO = sdo;
    KeyCount = keycount;
}

//Int Handler
void TouchPad16::Handler()
{
    digitalWrite(Pin_SDL, HIGH);
    detachInterrupt(digitalPinToInterrupt(Pin_SDO)); //Stop Int
    Serial.println();
    Serial.println("Int Pino L->H");
    DTA = 0;
    Key = 0;
    delayMicroseconds(93);
    digitalWrite(Pin_SDO, LOW); // Is it possible to write if in input pullup mode 
    delayMicroseconds(10);
    pinMode(Pin_SDO, INPUT);

    //Read 17 Bits for Safe

    DTA=ReadKeys();  // Store 17 Bit in bitmap
    PressedKey= KeyPressed();  // Returns and store which is pressed.
    KeyHandler(PressedKey);
    
    attachInterrupt(digitalPinToInterrupt(Pin_SDO), this->Handler, RISING);//Restart Int for new Key

}

void TouchPad16::KeyHandler(int presskey){
    //TODO: Implement Based on your Requirement here. 
    //TODO: You can implement by using call back function
}
//Call in Setup()
void TouchPad16::Int_TouchPad()
{

    pinMode(Pin_SDO, INPUT_PULLUP);
    pinMode(Pin_SDL, OUTPUT);

    digitalWrite(Pin_SDO, HIGH);
    digitalWrite(Pin_SDL, HIGH);

    attachInterrupt(digitalPinToInterrupt(Pin_SDO), this->Handler, RISING);
    Serial.println();
    Serial.println("Start Key 16 Captive Touch Pad...");
}
//Call in Loop , it is Lopper
void TouchPad16::Loopper()
{
    yield();
    ESP.wdtFeed();
}