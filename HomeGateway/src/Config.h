#ifndef CONFIG_H
#define CONFIG_H

//Config
//Features Config
#define MQTT_SUPPORT ;
#define InBuilt_Temp_Sensor 1; // Adding DHT Sensor

// Board Config
//#define WittyBoard ;          // Witty CLoud Board
#define NODEMCU ;               // NodeMCU Dev kit
//#define ESP32DevKit ;         // ESP32 Based Dev Kit
//#define ESP32 ;




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

#define MQTT_HOST IPAddress(192, 168, 11, 18)

// MQTT Broker Auth 
#define MQTT_USERNAME "mqtt_c" 
#define MQTT_PASSWORD "Dumka@@2654"



//Topic 
#define Topic_HeatIndex "cymostate/heatindex" 
#define Topic_Temp  "cymostate/tempature" 
#define Topic_Humidity "cymostate/humidity" 
#define Topic_SensorData "cymostate/sensordata" 
#define Topic_DeviceName "cymostate/device/name" 
#define Topic_DeviceType "cymostate/device/devicetype" 
#define Topic_DeviceCategory "cymostate/device/category" 

//end config

#endif