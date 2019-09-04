#include <Arduino.h>
#include "HomeServer.h"
#include "CYN_OTA.h"
#define VERSION 1.2 


HomeServer home;
void setup() 
{
  Serial.begin(115200);
  
  // put your setup code here, to run once:
  home.SetupHomeServer();
  Serial.print("Version: "); Serial.println(VERSION);
  FirmwareUpdater::UpdaterInstaller();

}

void loop() 
{
  // put your main code here, to run repeatedly:
  home.LoopHomeServer();
  FirmwareUpdater::UpdaterLooper();
}