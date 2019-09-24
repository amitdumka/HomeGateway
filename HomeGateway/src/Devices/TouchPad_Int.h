#ifndef TOUCHPAD_INT_H
#define TOUCHPAD_INT_H

#include <Wire.h>
//#include <TTP229.h>
#include <Arduino.h>


class TouchPad_Int
{
private:
    static int Pin_SDO;
    static int Pin_SDL;

    static int Key;       //  Key 1 to 16 (No Key=0 is optional)
    static boolean Touch; //1=On 0=Off
    static boolean In;
    static unsigned int DTA;
    static unsigned int DTB;

public:
    TouchPad_Int(int sdo, int sdl);
    void SetUpTouchPad();
    void CallInLoop()
    {
        yield();
        ESP.wdtFeed();
    }
    void Int_Handler();
};




#endif



void TouchPad_Int::Int_Handler()
{
    //TODO: Check if it requried to be static ;

    digitalWrite(Pin_SDL, HIGH);
    detachInterrupt(digitalPinToInterrupt(Pin_SDO)); //Stop Int

    Serial.println();
    Serial.println("Int Pino L->H");

    DTA = 0;
    Key = 0;

    delayMicroseconds(93);
    digitalWrite(Pin_SDO, LOW);
    delayMicroseconds(10);

    pinMode(Pin_SDO, INPUT);

    //------------------------
    for (int i = 0; i < 17; i++) //Read 17 Bits for Safe
    {
        digitalWrite(Pin_SDL, HIGH);
        delayMicroseconds(1);
        digitalWrite(Pin_SDL, LOW);
        delayMicroseconds(1);
        In = digitalRead(Pin_SDO);
        if (Key == 0 && In == 0)
        {
            Key = i + 1;
        }
        DTA |= In << i;
    }

    digitalWrite(Pin_SDL, HIGH);
    delayMicroseconds(2);

    //------------------------
    if (DTB != DTA && DTA != 131071)
    {
        DTB = DTA;
        //Serial.println(DTA,BIN);
        //Serial.println(DTA,HEX);
        //Serial.println(DTA,DEC);
        Serial.println(Key);
        Serial.println("Touch 1");
        Touch = 1;
    }
    else
    {
        //Key=0;// Optional
        Serial.println("Touch 0");
        DTB = 0;
        Touch = 0;
    }

    attachInterrupt(digitalPinToInterrupt(Pin_SDO), this->Int_Handler, RISING); //Restart Int for new Key
}

void TouchPad_Int::SetUpTouchPad()
{

    pinMode(Pin_SDO, INPUT_PULLUP);
    pinMode(Pin_SDL, OUTPUT); //
    digitalWrite(Pin_SDO, HIGH);
    digitalWrite(Pin_SDL, HIGH);

    attachInterrupt(digitalPinToInterrupt(Pin_SDO), this->Int_Handler, RISING);

    Serial.println();
    Serial.println("Start Key 16");
}

