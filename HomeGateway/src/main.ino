#include <Arduino.h>
#include "HomeServer.h"
#include "CYN_OTA.h"
#include "Config.h"

#ifdef MQTT_SUPPORT
#include "Async_MQTT_Server.h"
Async_MQTT mqttClients;
#endif
#define VERSION 1.3

HomeServer home;
void setup()
{
  Serial.begin(115200);

  // put your setup code here, to run once:
  home.SetupHomeServer();
  Serial.print("Version: ");
  Serial.println(VERSION);
  FirmwareUpdater::UpdaterInstaller();
// MQTT with Mosquitto broker. optional Home assistance. 
#ifdef MQTT_SUPPORT
  mqttClients.mqtt_setup();
#endif

}

void loop()
{
  // put your main code here, to run repeatedly:
  home.LoopHomeServer();
  FirmwareUpdater::UpdaterLooper();

#ifdef MQTT_SUPPORT
  mqttClients.mqtt_loop();
#endif

}