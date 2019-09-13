#ifndef ASYNC_MQTT_SERVER_H
#define ASYNC_MQTT_SERVER_H

#include "Config.h"
#include "Util.h"
#include <AsyncMqttClient.h>
#include <Arduino.h>
#include <Ticker.h>

// #ifdef NODEMCU
// #include <ESP8266WiFi.h>
// #endif

#ifdef ESP32
#include <WiFi.h>
extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}
#endif

class Async_MQTT
{
private:

    static String MQTT_Client_ID;

    // Basic Topic
    //topic to subscribe to request for software version (Generic Device, MAC Addr, Filename.ino)
    const char *swVerTopic = "/MQTT_Client_ID+SwVerCommand";
    char swVerThisDeviceTopic[50];

    //topic to publish request for software version
    const char *swVerConfirmTopic = "/MQTT_Client_ID/SwVerConfirm";

    String clientName;
    const char *THIS_GENERIC_DEVICE = "esp8266"; //TODO: This need to be set Based on Board Select. Need to be implemented
    String swVersion;

    void setClientDetails();

    static AsyncMqttClient mqttClient;
    //  static WiFiEventHandler wifiConnectHandler;
    // static WiFiEventHandler wifiDisconnectHandler;

#ifdef NODEMCU
    static Ticker mqttReconnectTimer;
    //    static Ticker wifiReconnectTimer;
#endif

#ifdef ESP32
    static TimerHandle_t mqttReconnectTimer;
#endif
    
    static void connectToMqtt();
    
    static void onMqttPublish(uint16_t packetId);

    static void onMqttConnect(bool sessionPresent);
    static void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);

    static void onMqttSubscribe(uint16_t packetId, uint8_t qos);
    static void onMqttUnsubscribe(uint16_t packetId);
    static void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);

    static void TopicHandler(char *topic, char *paylod);
    static void BasicHandler(char *topic);

public:
    static bool isMQTTBrokerConnected;
    void mqtt_loop();
    void mqtt_setup();
    static void Publish(char *topic, const char *message);
    static void Subscribe(char *topic);
};

#endif
