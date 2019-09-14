#include "Async_MQTT_Server.h"

bool Async_MQTT::isMQTTBrokerConnected = false;
AsyncMqttClient Async_MQTT::mqttClient;

#ifdef NODEMCU
Ticker Async_MQTT::mqttReconnectTimer;
//    static Ticker wifiReconnectTimer;
#endif

#ifdef ESP32
TimerHandle_t Async_MQTT::mqttReconnectTimer;
//    static TimerHandle_t wifiReconnectTimer;
#endif

//TODO: Impelemetation check
void Async_MQTT::connectToMqtt()
{
    Serial.println("Connecting to MQTT...");
    mqttClient.connect();
}
//TODO: Impelemetation check
void Async_MQTT::onMqttConnect(bool sessionPresent)
{
    isMQTTBrokerConnected = true;

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

    uint16_t packetIdSubTG = mqttClient.subscribe(Topic_Temp_GET, 2);
    Serial.print("Subscribing at QoS 2, packetId: ");
    Serial.println(packetIdSubTG);

    uint16_t packetIdSubHG = mqttClient.subscribe(Topic_Humidity_GET, 2);
    Serial.print("Subscribing at QoS 2, packetId: ");
    Serial.println(packetIdSubHG);

    uint16_t packetIdSubSG = mqttClient.subscribe(Topic_SensorData_GET, 2);
    Serial.print("Subscribing at QoS 2, packetId: ");
    Serial.println(packetIdSubSG);

    mqttClient.publish(Topic_Temp, 0, true, String(Tempatures::sensorData.Temp_C).c_str());
    mqttClient.publish(Topic_Temp_GET, 0, true, String(Tempatures::sensorData.Temp_C).c_str());
    mqttClient.publish(Topic_Humidity, 0, true, String(Tempatures::sensorData.Humidity).c_str());
    mqttClient.publish(Topic_Humidity_GET, 0, true, String(Tempatures::sensorData.Humidity).c_str());
    mqttClient.publish(Topic_HeatIndex, 0, true, String(Tempatures::sensorData.HeatIndex).c_str());
    mqttClient.publish(Topic_SensorData_GET,0,true, ToJsonObject(Tempatures::sensorData.Temp_C, Tempatures::sensorData.Humidity, Tempatures::sensorData.HeatIndex).c_str());
}

//TODO: Impelemetation check
void Async_MQTT::onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
    isMQTTBrokerConnected = false;
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

    TopicHandler(topic, payload); // Handel Device topic
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
    mqttClient.setCredentials(MQTT_USERNAME, MQTT_PASSWORD); // Username and password for MQTT Broker to connect.

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
void Async_MQTT::TopicHandler(char *topic, char *payload)
{
    if (topic == Topic_Temp && (payload == "GET" || payload == "get"))
    {
        Publish(Topic_Temp, String(Tempatures::sensorData.Temp_C).c_str()); //TODO: Final Check.
    }
    else if (topic == Topic_Temp_GET)
    {
        Publish(Topic_Temp, String(Tempatures::sensorData.Temp_C).c_str()); //TODO: Final Check.
    }
    else if (topic == Topic_HeatIndex && (payload == "GET" || payload == "get"))
    {
        Publish(Topic_HeatIndex, String(Tempatures::sensorData.HeatIndex).c_str()); //TODO: Final Check.
    }
    else if (topic == Topic_Humidity && (payload == "GET" || payload == "get"))
    {
        Publish(Topic_Humidity, String(Tempatures::sensorData.Humidity).c_str()); //TODO: Final Check.
    }
    else if (topic == Topic_Humidity_GET)
    {
        Publish(Topic_Humidity_GET, String(Tempatures::sensorData.Humidity).c_str()); //TODO: Final Check.
    }
    else if (topic == Topic_SensorData && payload == "GET" || payload == "get")
    {
        Publish(Topic_Temp, String(Tempatures::sensorData.Temp_C).c_str());         //TODO: Final Check.
        Publish(Topic_Humidity, String(Tempatures::sensorData.Humidity).c_str());   //TODO: Final Check.
        Publish(Topic_HeatIndex, String(Tempatures::sensorData.HeatIndex).c_str()); //TODO: Final Check.
    }
    else if (topic == Topic_SensorData_GET)
    {
        Publish(Topic_SensorData_GET, ToJsonObject( Tempatures::sensorData.Temp_C, Tempatures::sensorData.Humidity, Tempatures::sensorData.HeatIndex).c_str());
    }
    else
        BasicHandler(topic);
}

void Async_MQTT::Publish(char *topic, const char *message)
{

    mqttClient.publish(topic, 0, true, message);
}

void Async_MQTT::Subscribe(char *topic)
{

    Serial.print("Subscribing at QoS 2, packetId: ");
    Serial.println(mqttClient.subscribe(topic, 2));
}

String Async_MQTT::ToJsonObject(float temp, float hum, float hindex)
{
    String jobj = "{ \"temp\":\"" + String(temp) + "\", \"humidity\":\"" + String(hum) + "\", \"heatindex\":\"" + String(hindex) + "\"}";
    return jobj;
}