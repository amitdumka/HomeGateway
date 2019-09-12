#include "Async_MQTT_Server.h"


//TODO: Impelemetation check
void Async_MQTT::connectToMqtt()
{
    Serial.println("Connecting to MQTT...");
    mqttClient.connect();
}
//TODO: Impelemetation check
void Async_MQTT::onMqttConnect(bool sessionPresent)
{
    Serial.println("Connected to MQTT.");
    Serial.print("Session present: ");
    Serial.println(sessionPresent);

    uint16_t packetIdSubT = mqttClient.subscribe(Topic_Temp, 2);
    Serial.print("Subscribing at QoS 2, packetId: ");
    Serial.println(packetIdSubT);

    uint16_t packetIdSubH = mqttClient.subscribe(Topic_Humidity, 2);
    Serial.print("Subscribing at QoS 2, packetId: ");
    Serial.println(packetIdSubH);

    uint16_t packetIdSubHI = mqttClient.subscribe(Topic_HeatIndex, 2);
    Serial.print("Subscribing at QoS 2, packetId: ");
    Serial.println(packetIdSubHI);


    mqttClient.publish("cymostate", 0, true, "0.0c");
    
}

//TODO: Impelemetation check
void Async_MQTT::onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
    Serial.println("Disconnected from MQTT.");

    if (reason == AsyncMqttClientDisconnectReason::TLS_BAD_FINGERPRINT)
    {
        Serial.println("Bad server fingerprint.");
    }

    if (WiFi.isConnected())
    {
#ifdef NODEMCU
        mqttReconnectTimer.once(2, connectToMqtt);
#endif

#ifdef ESP32
        xTimerStart(mqttReconnectTimer, 0);
#endif
    }
}
//TODO: Impelemetation check
void Async_MQTT::onMqttSubscribe(uint16_t packetId, uint8_t qos)
{
    Serial.println("Subscribe acknowledged.");
    Serial.print("  packetId: ");
    Serial.println(packetId);
    Serial.print("  qos: ");
    Serial.println(qos);
}
//TODO: Impelemetation check
void Async_MQTT::onMqttUnsubscribe(uint16_t packetId)
{
    Serial.println("Unsubscribe acknowledged.");
    Serial.print("  packetId: ");
    Serial.println(packetId);
}

//TODO:: check use and implementation
void Async_MQTT::onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
    Serial.println("Publish received.");
    Serial.print("  topic: ");
    Serial.println(topic);
    Serial.print("  qos: ");
    Serial.println(properties.qos);
    Serial.print("  dup: ");
    Serial.println(properties.dup);
    Serial.print("  retain: ");
    Serial.println(properties.retain);
    Serial.print("  len: ");
    Serial.println(len);
    Serial.print("  index: ");
    Serial.println(index);
    Serial.print("  total: ");
    Serial.println(total);
}

//TODO: Impelemetation check
void Async_MQTT::onMqttPublish(uint16_t packetId)
{
    Serial.println("Publish acknowledged.");
    Serial.print("  packetId: ");
    Serial.println(packetId);
}
//TODO: Impelemetation check
void Async_MQTT::mqtt_setup()
{
    //Serial.begin(115200);
    Serial.println();
    Serial.println("Starting MQTT Client ....");

#ifdef ESP32
  
    mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt));
   
#endif

    mqttClient.onConnect(onMqttConnect);
    mqttClient.onDisconnect(onMqttDisconnect);

    mqttClient.onSubscribe(onMqttSubscribe);
    mqttClient.onUnsubscribe(onMqttUnsubscribe);

    mqttClient.onMessage(onMqttMessage);
    mqttClient.onPublish(onMqttPublish);

    mqttClient.setServer(MQTT_HOST, MQTT_PORT);

    //TODO: using this way we can pass class method as calbackfuntion instead of making static. check the scope
    //mqttClient.onConnect(std::bind(&Async_MQTT::l,this));

#if ASYNC_TCP_SSL_ENABLED
    mqttClient.setSecure(MQTT_SECURE);
    if (MQTT_SECURE)
    {
        mqttClient.addServerFingerprint((const uint8_t[])MQTT_SERVER_FINGERPRINT);
    }
#endif

    
    //connectToWifi();
    connectToMqtt();

}

//TODO: Impelemetation check
void Async_MQTT::mqtt_loop()
{
}


void Async_MQTT::setClientDetails()
{
    clientName = THIS_GENERIC_DEVICE;
    clientName += '-';
    uint8_t mac[6];
    WiFi.macAddress(mac);
    clientName += macToStr(mac);

    sprintf(swVerThisDeviceTopic, "/MQTT_Client_ID/%s/SwVerCommand", macToStr(mac).c_str());

    swVersion = THIS_GENERIC_DEVICE;
    swVersion += ',';
    swVersion += macToStr(mac);

    Serial.print("Client Name : ");
    Serial.println(clientName);
    Serial.print("SW Version : ");
    Serial.println(swVersion);

}

void Async_MQTT::BasicHandler(char *topic)
{

}

//Handle message and do operations
void Async_MQTT::TopicHandler( char *topic , char *paylod)
{
    if(topic==Topic_Temp){
        Publish(Topic_Temp,"0.0c"); //TODO: Final Check.
    }

}


void Async_MQTT::Publish(char *topic, char *message){

    mqttClient.publish(topic, 0, true, message);
}
    
void Async_MQTT::Subscribe(char *topic){

    Serial.print("Subscribing at QoS 2, packetId: ");
    Serial.println(mqttClient.subscribe(topic, 2));
}
