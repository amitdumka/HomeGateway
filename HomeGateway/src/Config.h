#ifndef CONFIG_H
#define CONFIG_H

//Lib Needed for Config File
#include <Arduino.h>

//Config
//Features Config
#define MQTT_SUPPORT 
#define InBuilt_Temp_Sensor 1 // Adding DHT Sensor

// Board Config
//#define WittyBoard ;          // Witty CLoud Board
#define NODEMCU                // NodeMCU Dev kit
//#define ESP32DevKit          // ESP32 Based Dev Kit
//#define ESP32 




//MQT Config 
#if ASYNC_TCP_SSL_ENABLED
#define MQTT_SECURE true
#define MQTT_SERVER_FINGERPRINT                                                                                                \
    {                                                                                                                          \
        0x7e, 0x36, 0x22, 0x01, 0xf9, 0x7e, 0x99, 0x2f, 0xc5, 0xdb, 0x3d, 0xbe, 0xac, 0x48, 0x67, 0x5b, 0x5d, 0x47, 0x94, 0xd2 \
    }
#define MQTT_PORT 8883
#else
#define MQTT_PORT 1883 // Port Might be changed and port use with Mosquitto broker
#endif

#define MQTT_HOST IPAddress(192, 168, 11, 201)

//TODO: UserName  & Password should be provided through UI Config Web/App based. 
// A Default SSL Based username password change and recovery system is needed so can be used with App
// Web API also can be option
// MQTT Broker Auth 
#define MQTT_USERNAME "mqtt_c" 
#define MQTT_PASSWORD "Dumka@2654"



//Topic 
//TODO: need to add one more step so unique device id can be used to diff btw two devices
//temperature
#define Topic_HeatIndex "cymostate/heatindex" 
#define Topic_Temp  "cymostate/temperature"
#define Topic_Temp_GET  "cymostate/temperature/get" 
#define Topic_Humidity "cymostate/humidity" 
#define Topic_Humidity_GET "cymostate/humidity/get" 
#define Topic_SensorData "cymostate/sensordata" 
#define Topic_DeviceName "cymostate/device/name" 
#define Topic_DeviceType "cymostate/device/devicetype" 
#define Topic_DeviceCategory "cymostate/device/category" 
#define Topic_SensorData_GET "cymostate/sensordata/get"

//end config


// HomeServer Config

//Cofig Section ; Later should be move to config for better visiblity and readbillity

#define SDC D2 // Pin For oled Display
#define SDA D1 // Pin For Oled Display

#define DHT_Pin D4  // DHT Sensor Pin is connected to Board Read pin.
#define DHT_Type DHT11 // Type of Sensor , DHT11 or DHT22

//Time Zone Setting

#define TZ 5.5   // (utc+) TZ in hours  5.5 is for India, Change based on your location
#define DST_MN 0 // use 60mn for summer time in some countries
#define TZ_MN ((TZ)*60)
#define TZ_SEC ((TZ)*3600)
#define DST_SEC ((DST_MN)*60)

//end config of HomeServer

//Home Assistance Config and Constant

//end of Home Assistance

#endif