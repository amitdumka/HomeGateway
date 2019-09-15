#ifndef TEMPATURES_H
#define TEMPATURES_H

#include <Adafruit_Sensor.h>
#include <dht.h>
#include <Arduino.h>
#include <Hash.h>
//#include <DHT.h>
#include "Config.h"
#include "Sensor.h"



class Tempatures
{

private:
    //Default:
    int DHTPin = DHT_Pin;     //Default pin for NodeMCU   Make Change in config File
    int DHTType = DHT_Type;   //Default Type DHT11   Make change in config file

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