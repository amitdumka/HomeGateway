#ifndef UTIL_H
#define UTIL_H

//TODO:Make Lib name changes to proper name

//#include <FS.h> //this needs to be first, or it all crashes and burns...
//#include <ArduinoJson.h> //https://github.com/bblanchon/ArduinoJson
//#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino
//#include <DNSServer.h>
//#include <ESP8266WebServer.h>
#include <WiFiManager.h>

class Board
{
public:
  static const double Device_Id;
  static const String Activation_Code;

  static bool isFahrenheit; //=false; //Default celsius

  static bool isAPOn;
  static bool isAPRequired;
  static const String AP_Name;
  static const char *SSID;
  static const char *password;
  static const char *Host;

  static bool wifiConnected;

  //start-block2
  static const IPAddress _IP;
  static const IPAddress _GW;
  static const IPAddress _SN;
};

// const String ConfigFileName = "/config.json";

bool CallWiFiManager(bool isNew);

String macToStr(const uint8_t *mac);

//bool ReadConfigFile();
//bool saveConfiguration();
//void printFile(const char *filename);
//bool saveRelayConfiguration(String sName, int value, String sName2, bool value2);

bool StringCompare(char *a, char *b)
{
  if (strcmp(a, b) > 0)
    return false;
  else
    return true;
}

#endif