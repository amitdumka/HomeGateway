#include "TouchPad.h"

int sdo=D7;
int sdl=D8

TouchPad tp(sdo, sdl,16,1);
void setup() {
  // put your setup code here, to run once:
  //tp= TouchPad(sdo, sdl,16,1);
  tp.SetUpTouchPad();

}

void loop() {
  // put your main code here, to run repeatedly:
  tp.CallInLoop();
}
