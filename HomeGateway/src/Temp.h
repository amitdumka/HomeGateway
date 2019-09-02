#ifndef TEMP_H
#define TEMP_H

#include <Adafruit_Sensor.h>
#include <dht.h>
#include <Arduino.h>
#include <Hash.h>
//#include <DHT.h>

class Tempatures
{

private:
    // int DHTPin;
    // int DHTType;
    //Default:
    int DHTPin = D4;
    int DHTType = DHT11;

    DHT *dht; //(5, 11);

public:
    float Temp_C;
    float Humidity;
    float HeatIndex;

    Tempatures(int pin, int senType);
    float readDHTHumidity();

    float readDHTTemperature();

    float readDHTHeatIndex();

    float ReadDHTSenor();
};

#endif