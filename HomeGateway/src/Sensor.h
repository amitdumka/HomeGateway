#ifndef SENSOR_H
#define SENSOR_H

class Sensor
{
public:
    static float Temp_C; //by Default get Temp in centigrate
    static float Humidity;
    static float HeatIndex;
    static bool isFarenhite;

    static float LightIntensisty;
    static bool isLightOn;
    static bool isLightDim;
    static bool isLightTooDim;
    static bool isLightTooBright;

    //Led 
    static bool RedLedState;
    static bool BlueLedState;
    static bool GreenLedState;
};

#endif

//Sensor class
// Temp DHT
float Sensor::Temp_C = 0.0; //by Default get Temp in centigrate
float Sensor::Humidity = 0.0;
float Sensor::HeatIndex = 0.0;
bool Sensor::isFarenhite = false; //TODO: Implement this for Farenhite or celsius

// Light

float Sensor::LightIntensisty = 0.0;
bool Sensor::isLightOn = false;
bool Sensor::isLightDim = false;
bool Sensor::isLightTooDim = false;
bool Sensor::isLightTooBright = false;
