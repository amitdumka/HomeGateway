#ifndef TEMPATURES_H
#define TEMPATURES_H

#include <Adafruit_Sensor.h>
#include <dht.h>
#include <Arduino.h>
#include <Hash.h>
//#include <DHT.h>

class Sensor
{
public:
    static float Temp_C; //by Default get Temp in centigrate
    static float Humidity;
    static float HeatIndex;

}; 

class Tempatures
{

private:
    //Default:
    int DHTPin = D4;     //Default pin for NodeMCU
    int DHTType = DHT11; //Default Type DHT11

    DHT *dht;

public:
    static Sensor sensorData;
    static Sensor sensorOldData;  //TODO: use to tally with old publish data
    Tempatures(int pin, int senType);

    float readDHTHumidity();
    float readDHTTemperature(bool isFahrenheit = false);
    float readDHTHeatIndex(bool isFahrenheit = false);
    float ReadDHTSensor(bool isFahrenheit = false);
    bool isSensorDataChanged();
    void UpdateLatestData();
};

#endif