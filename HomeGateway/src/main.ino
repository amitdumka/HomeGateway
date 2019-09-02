#include <Arduino.h>
#include "HomeServer.h"

HomeServer home;
void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  home.SetupHomeServer();
}

void loop() {
  // put your main code here, to run repeatedly:
  home.LoopHomeServer();
}