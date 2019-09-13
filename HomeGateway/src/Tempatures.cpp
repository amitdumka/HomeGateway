#include "Tempatures.h"

//Sensor class
float Sensor::Temp_C = 0.0; //by Default get Temp in centigrate
float Sensor::Humidity = 0.0;
float Sensor::HeatIndex = 0.0;
bool Sensor::isFarenhite=false; //TODO: Implement this for Farenhite or celsius 


//Temp class
Tempatures::Tempatures(int pin, int senType)
{
    DHTPin = pin;
    DHTType = senType;
    dht = new DHT(DHTPin, DHTType);
    dht->begin();
    
}
//isFahrenheit
float Tempatures::ReadDHTSensor(bool isFahrenheit)
{
    sensorData.Humidity = dht->readHumidity();
    sensorData.Temp_C = dht->readTemperature(isFahrenheit);
    if (isnan(sensorData.Humidity) || isnan(sensorData.Temp_C))
    {
        Serial.println("Failed to read from DHT sensor!");
        return -999.99;
    }
    else
    {
        sensorData.HeatIndex = dht->computeHeatIndex(sensorData.Temp_C, sensorData.Humidity, isFahrenheit); // Compute heat index in isFahrenheit
        Serial.print("sensorData.Humidity: ");
        Serial.println(sensorData.Humidity);
        Serial.print("Temp: ");
        Serial.println(sensorData.Temp_C);
        Serial.print("Heat Index: ");
        Serial.println(sensorData.HeatIndex);

        return sensorData.Temp_C;
    }
}

float Tempatures::readDHTHumidity()
{
    sensorData.Humidity = dht->readHumidity();
    if (isnan(sensorData.Humidity))
    {
        Serial.println("Failed to read from DHT sensor!");
        return -999.99;
    }
    else
    {
        Serial.println(sensorData.Humidity);
        return sensorData.Humidity;
    }
}

float Tempatures::readDHTTemperature(bool isFahrenheit)
{
    sensorData.Temp_C = dht->readTemperature(isFahrenheit);

    if (isnan(sensorData.Temp_C))
    {
        Serial.println("Failed to read from DHT sensor!");
        return -999.99;
    }
    else
    {
        Serial.println(sensorData.Temp_C);
        return sensorData.Temp_C;
    }
}

// isFahrenheit is true for Fahrenheit
float Tempatures::readDHTHeatIndex(bool isFahrenheit)
{
    readDHTHumidity();
    readDHTTemperature();
    sensorData.HeatIndex = dht->computeHeatIndex(sensorData.Temp_C, sensorData.Humidity, isFahrenheit); // Compute heat index in Celsius
    return sensorData.HeatIndex;
}

bool Tempatures::isSensorDataChanged()
{
    if (sensorData.HeatIndex != sensorOldData.HeatIndex || sensorData.Humidity != sensorOldData.Humidity || sensorData.Temp_C != sensorOldData.Temp_C)
        return true;
    else
        return false;
}

void Tempatures::UpdateLatestData()
{
    sensorOldData.HeatIndex = sensorData.HeatIndex;
    sensorOldData.Humidity = sensorData.Humidity;
    sensorOldData.Temp_C = sensorData.Temp_C;
}