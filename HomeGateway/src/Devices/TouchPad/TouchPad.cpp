#include "TouchPad.h"

//Variables and Fields .
int TouchPad::PressedKey = 0;
// Constructors
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
TouchPad::TouchPad(int sdo, int sdl, int keycount, int mode){
  // Use this Constructors to use for attachInterrupt
  Pin_SDL = sdl;
  Pin_SDO = sdo;
  KeyCount = keycount;
  isINTBased=true;
}

//Member functions
//Call In Loop function.
void TouchPad::CallInLoop()
{
  touchPad.readKeys();
  yield();
  ESP.wdtFeed();
}
//Call in Setup

int TouchPad::GetKey()
{
  return touchPad.getKey();
}

bool TouchPad::IsKeyDown(byte key) {
  return touchPad.isKeyDown(key);
}

bool TouchPad::IsKeyUp(byte key) {
  return touchPad.isKeyUp(key);
}

bool TouchPad::IsKeyPress(byte key) {
  return touchPad.isKeyPress(key);
}

/// Returns which key is pressed.
int TouchPad::KeyPressed()
{
  for (int i = 0; i < KeyCount; i++)
  {
    if (touchPad.isKeyPress(i))
    return i;
  }
}

uint16_t TouchPad::ReadKeys() {
  return touchPad.readKeys();
}

//Int Handler
void TouchPad::Handler()
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

void TouchPad::KeyHandler(int presskey){
  //TODO: Implement Based on your Requirement here.
  //TODO: You can implement by using call back function
  Serial.print("Key is pressed: "); serial.pritln(presskey);
}

void TouchPad::SetUpTouchPad(){
  if(isINTBased){
    pinMode(Pin_SDO, INPUT_PULLUP);
    pinMode(Pin_SDL, OUTPUT);
    digitalWrite(Pin_SDO, HIGH);
    digitalWrite(Pin_SDL, HIGH);
    attachInterrupt(digitalPinToInterrupt(Pin_SDO), this->Handler, RISING);
    Serial.println();
    Serial.println("Start Key 16 Captive Touch Pad...");
    }
    else
    {
    pinMode(Pin_SDO, INPUT_PULLUP);
    pinMode(Pin_SDL, OUTPUT);
  }
}
