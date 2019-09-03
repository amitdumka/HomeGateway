
//#include <ArduinoJson.h> //https://github.com/bblanchon/ArduinoJson
#include "Util.h"
//Change this based on requirement

// Unqiue Id. Can be used to know different devices on network
const double Board::Device_Id = 67861;
const String Board::AP_Name = "Amit_IOT_" + String(Board::Device_Id);
const String Board::Activation_Code = "Att01@24";

// Temp
bool Board::isFahrenheit=false; //Default celsius

//Change Before Flashing
const char *Board::SSID = "AMIT_IOT";
const char *Board::password = "12345678";
const char *Board::Host = "Amit_IOT";

bool Board::wifiConnected = false;

//AP Config  Check is required now.
bool Board::isAPOn = false;
bool Board::isAPRequired = false;

//Static IP . Check for use if it used or not With WifiManager
const IPAddress Board::_IP = IPAddress(192, 168, 5, 1);
const IPAddress Board::_GW = IPAddress(192, 168, 5, 1);
const IPAddress Board::_SN = IPAddress(255, 255, 255, 0);

//CallWifiManager to connect wifi
bool CallWiFiManager(bool isNew)
{
    Serial.println("WiFi Manager is started...");
    WiFiManager wifiManager;
    if (isNew)
        wifiManager.resetSettings(); //reset settings - for testing
    wifiManager.setAPStaticIPConfig(Board::_IP, Board::_GW, Board::_SN);
    wifiManager.setTimeout(360);

    if (!wifiManager.autoConnect(Board::AP_Name.c_str()))
    {
        Serial.println("failed to connect and hit timeout");
        delay(3000);
        //reset and try again, or maybe put it to deep sleep
        ESP.reset();
        delay(5000);
    }
    //if you get here you have connected to the WiFi
    Serial.println("local ip");
    Serial.println(WiFi.localIP());

    Board::wifiConnected = true;
    return true;
}

// /**Reading Config File*/
// bool ReadConfigFile()
// {
//     Serial.println("\nmounting FS for reading ");
//     if (SPIFFS.begin())
//     {
//         Serial.println("mounted file system");
//         if (SPIFFS.exists(ConfigFileName))
//         {
//             Serial.println("reading config file");
//             // Open file for reading
//             File configFile = SPIFFS.open(ConfigFileName, "r");
//             StaticJsonDocument<512> doc;
//             // Deserialize the JSON document
//             DeserializationError error = deserializeJson(doc, configFile);
//             if (error)
//                 Serial.println(F("Failed to read file, using default configuration"));
//             // Copy values from the JsonDocument to the Config
//             for (int i = 0; i < WeMo::NoOfRelay; i++)
//             {
//                 WeMo::RelayStatus[i] = doc[WeMo::RelayNames[i]] | 0;
//                 WeMo::isRelayOn[i] = doc[WeMo::RelayNames[i] + WeMo::RelayPins[i]] | false;
//             }
//             Serial.println("values set");
//             // Close the file (Curiously, File's destructor doesn't close the file)
//             configFile.close();
//             return true;
//         }
//         else
//         {
//             Serial.println("Config File not found...");
//             return false;
//         }
//     }
//     else
//     {
//         Serial.println("Failed To read and mount Filesystem..");
//         return false;
//     }

// } // end of ReadConfigFile

// // Saves the configuration to a file
// bool saveConfiguration()
// {
//     Serial.println("mounting FS...for saving");
//     if (SPIFFS.begin())
//     {
//         Serial.println("mounted file system");
//         if (SPIFFS.exists(ConfigFileName))
//         {
//             SPIFFS.remove(ConfigFileName);
//         }
//         File file = SPIFFS.open(ConfigFileName, "w");
//         if (!file)
//         {
//             Serial.println(F("Failed to create file"));
//             return false;
//         }
//         StaticJsonDocument<256> doc;
//         for (int i = 0; i < WeMo::NoOfRelay; i++)
//         {
//             doc[WeMo::RelayNames[i]] = WeMo::RelayStatus[i];
//             doc[WeMo::RelayNames[i] + WeMo::RelayPins[i]] = WeMo::isRelayOn[i];
//         }

//         // Serialize JSON to file
//         if (serializeJson(doc, file) == 0)
//         {
//             Serial.println(F("Failed to write to file"));
//             return false;
//         }
//         Serial.println("file saved");
//         // Close the file
//         file.close();
//         return true;
//     }
//     else
//     {
//         Serial.println("mounted file system failed");
//         return false;
//     }
// }

// // Prints the content of a file to the Serial
// void printFile(const char *filename)
// {
//     if (SPIFFS.begin())
//     {
//         if (SPIFFS.exists(ConfigFileName))
//         {
//             File file = SPIFFS.open(filename, "r");
//             if (!file)
//             {
//                 Serial.println(F("Failed to read file"));
//                 return;
//             }
//             // Extract each characters by one by one
//             while (file.available())
//             {
//                 Serial.print((char)file.read());
//             }
//             Serial.println();
//             // Close the file
//             file.close();
//         }
//         else
//         {
//             Serial.println("File doesnt exisit");
//         }
//     }
//     else
//     {
//         Serial.println("File sys mounting failed");
//     }
// }

// //Saving Spefic Setting
// bool saveRelayConfiguration(String sName, int value, String sName2, bool value2)
// {
//     //TODO: Have to  make specific value  either one or two. need to check with retroSwitch
//     Serial.println("mounting FS...for saving");
//     if (SPIFFS.begin())
//     {
//         Serial.println("mounted file system");
//         if (!SPIFFS.exists(ConfigFileName))
//         {
//             Serial.println("File Doesnt exist...");
//         }
//         File file = SPIFFS.open(ConfigFileName, "w");
//         if (!file)
//         {
//             Serial.println(F("Failed to create file"));
//             return false;
//         }
//         StaticJsonDocument<256> doc;
//         doc[sName] = value;
//         doc[sName2] = value2;
//         // Serialize JSON to file
//         if (serializeJson(doc, file) == 0)
//         {
//             Serial.println(F("Failed to write to file"));
//             return false;
//         }
//         Serial.println("file saved");
//         // Close the file
//         file.close();
//         return true;
//     }
//     else
//     {
//         Serial.println("mounted file system failed");
//         return false;
//     }
// }
