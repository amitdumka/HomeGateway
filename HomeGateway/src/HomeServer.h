#ifndef HOMESERVER_H
#define HOMESERVER_H

#include "Config.h"

//TODO:  Make This libaray so it can be used by Different board
//TODO: Make the board pin and i2c port fixed so just wiring is enough  and feature of HomeServer
// can added by plugin concept. So it can be extended from its original

#include <ESPWiFi.h>
#include <ESPHTTPClient.h>
#include <JsonListener.h>

#include "Util.h" //ESP8266/Witty/NodeMCU

// time
#include <time.h>      // time() ctime()
#include <sys/time.h>  // struct timeval
#include <coredecls.h> // settimeofday_cb()

#include "SSD1306Wire.h"
#include "OLEDDisplayUi.h"
#include "Wire.h"
#include "OpenWeatherMapCurrent.h"
#include "OpenWeatherMapForecast.h"
#include "WeatherStationFonts.h"
#include "WeatherStationImages.h"

#include <Arduino.h>
#include <Hash.h>

#include "Tempatures.h"
#include "Async_MQTT_Server.h"

#define DeviceType WittyBoard;

//Cofig Section ; Later should be move to config for better visiblity and readbillity

#define SDC D2; // Pin For oled Display
#define SDA D1; // Pin For Oled Display

#define DHTPin D4;  // DHT Sensor Pin is connected to Board Read pin.
#define DHTType 11; // Type of Sensor , DHT11 or DHT22

//Time Zone Setting
#define TZ 5.5   // (utc+) TZ in hours  5.5 is for India, Change based on your location
#define DST_MN 0 // use 60mn for summer time in some countries
#define TZ_MN ((TZ)*60)
#define TZ_SEC ((TZ)*3600)
#define DST_SEC ((DST_MN)*60)

// Setup
const int UPDATE_INTERVAL_SECS = 20 * 60; // Update every 20 minutes

//Config Section Ends here

class HomeServer
{

private:
    // flag changed in the ticker function every 10 minutes
    bool readyForWeatherUpdate = false;
    String lastUpdate = "--";
    long timeSinceLastWUpdate = 0;
    long timeDHTUpdate = 2000 * 60;

    SSD1306Wire *display; //(HomeServer::I2C_DISPLAY_ADDRESS, HomeServer::SDA_Pin, SDC_Pin);
    OLEDDisplayUi *ui;    //(&display);

    OpenWeatherMapCurrent currentWeatherClient;
    OpenWeatherMapForecast forecastClient;

    //declaring prototypes
    void drawProgress(OLEDDisplay *display, int percentage, String label);
    void updateData(OLEDDisplay *display);
    void setReadyForWeatherUpdate();
#ifdef MQTT_SUPPORT
    void PublishSensorData();
#endif
    static void drawDateTime(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y);
    static void drawCurrentWeather(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y);
    static void drawForecast(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y);
    static void drawForecastDetails(OLEDDisplay *display, int x, int y, int dayIndex);
    static void drawHeaderOverlay(OLEDDisplay *display, OLEDDisplayUiState *state);
    static void drawCurrentRoomTemp(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y);

    // Add frames
    // this array keeps function pointers to all frames
    // frames are the single views that slide from right to left

    FrameCallback frames[4] = {drawDateTime, drawCurrentRoomTemp, drawCurrentWeather, drawForecast};

    int numberOfFrames = 4;

    OverlayCallback overlays[1] = {drawHeaderOverlay};
    int numberOfOverlays = 1;

    static const int SDC_Pin = SDC;
    static const int SDA_Pin = SDA;
    // Display Settings
    static const int I2C_DISPLAY_ADDRESS = 0x3c; // Update based on your OLED Device

    static Tempatures temp;
    static const int DHT_Pin = DHTPin;
    static const int DHT_Type = DHTType;

    // OpenWeatherMap Settings
    static String OPEN_WEATHER_MAP_APP_ID;      //= "59043edc370e0751a311f35e1d2266ec";
    static String OPEN_WEATHER_MAP_LOCATION_ID; //= "1272237"; //Dumka
    static String OPEN_WEATHER_MAP_LANGUAGE;    //= "en";
    static const uint8_t MAX_FORECASTS = 4;

    static const boolean IS_METRIC = true; // Make is True for celsius and false for Fahrenheit.

    // Adjust according to your language
    static const String WDAY_NAMES[7];   //= {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    static const String MONTH_NAMES[12]; // = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

    static time_t now;

    static OpenWeatherMapCurrentData currentWeather;
    static OpenWeatherMapForecastData forecasts[MAX_FORECASTS];

public:
    HomeServer();
    void SetupHomeServer();
    void LoopHomeServer();
};

#endif

time_t HomeServer::now = time(nullptr);
Tempatures HomeServer::temp = Tempatures(DHT_Pin, DHT_Type);

OpenWeatherMapCurrentData HomeServer::currentWeather = OpenWeatherMapCurrentData();
OpenWeatherMapForecastData HomeServer::forecasts[MAX_FORECASTS];

// Adjust according to your language
const String HomeServer::WDAY_NAMES[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
const String HomeServer::MONTH_NAMES[12] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

// OpenWeatherMap Settings
String HomeServer::OPEN_WEATHER_MAP_APP_ID = "59043edc370e0751a311f35e1d2266ec";
String HomeServer::OPEN_WEATHER_MAP_LOCATION_ID = "1272237"; //Dumka
String HomeServer::OPEN_WEATHER_MAP_LANGUAGE = "en";

void HomeServer::SetupHomeServer()
{
    Serial.println();
    // initialize dispaly
    display->init();
    display->clear();
    display->display();

    //display.flipScreenVertically();
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->setContrast(255);

    if (!WiFi.isConnected())
    {
        Serial.println("Wifi is not connected");
        delay(500);
        Serial.print(".");
        display->clear();
        display->drawString(64, 10, "Connecting to WiFi");
        display->drawXbm(46, 30, 8, 8, 1 % 3 == 0 ? activeSymbole : inactiveSymbole);
        display->drawXbm(60, 30, 8, 8, 2 % 3 == 1 ? activeSymbole : inactiveSymbole);
        display->drawXbm(74, 30, 8, 8, 3 % 3 == 2 ? activeSymbole : inactiveSymbole);
        display->display();

        CallWiFiManager(false);
    }
    else
        Serial.println("Wifi connected..");

    // Get time from network time service
    configTime(TZ_SEC, DST_SEC, "pool.ntp.org");

    ui->setTargetFPS(30);

    ui->setActiveSymbol(activeSymbole);
    ui->setInactiveSymbol(inactiveSymbole);

    // You can change this to
    // TOP, LEFT, BOTTOM, RIGHT
    ui->setIndicatorPosition(BOTTOM);

    // Defines where the first frame is located in the bar.
    ui->setIndicatorDirection(LEFT_RIGHT);

    // You can change the transition that is used
    // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_TOP, SLIDE_DOWN
    ui->setFrameAnimation(SLIDE_LEFT);

    ui->setFrames(frames, numberOfFrames);

    ui->setOverlays(overlays, numberOfOverlays);

    // Inital UI takes care of initalising the display too.
    ui->init();

    Serial.println("");
    delay(3000);
    updateData(display);
}
void HomeServer::LoopHomeServer()
{

    if (millis() - timeSinceLastWUpdate > (1000L * UPDATE_INTERVAL_SECS))
    {
        setReadyForWeatherUpdate();
        timeSinceLastWUpdate = millis();
    }

    if (readyForWeatherUpdate && ui->getUiState()->frameState == FIXED)
    {
        updateData(display);
    }

    int remainingTimeBudget = ui->update();

    if (remainingTimeBudget > 0)
    {
        // You can do some work here
        // Don't do stuff if you are below your
        // time budget.
        delay(remainingTimeBudget);
    }
    if ((millis() - timeSinceLastWUpdate) > timeDHTUpdate)
    {
        temp.ReadDHTSensor(Board::isFahrenheit);
        timeSinceLastWUpdate = millis();
    }
}

HomeServer::HomeServer()
{
    display = new SSD1306Wire(HomeServer::I2C_DISPLAY_ADDRESS, HomeServer::SDA_Pin, SDC_Pin);
    ui = new OLEDDisplayUi(display);
}

void HomeServer::drawProgress(OLEDDisplay *display, int percentage, String label)
{
    display->clear();
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->setFont(ArialMT_Plain_10);
    display->drawString(64, 10, label);
    display->drawProgressBar(2, 28, 124, 10, percentage);
    display->display();
}

void HomeServer::updateData(OLEDDisplay *display)
{
    if (WiFi.isConnected())
    {
        drawProgress(display, 0, "WiFi Connected....");
        drawProgress(display, 05, WiFi.localIP().toString());
    }
    else
    {
        drawProgress(display, 1, "Wifi is not connected");
    }
    drawProgress(display, 10, "Updating time...");
    drawProgress(display, 20, " Updating Room Temp...");
    temp.ReadDHTSensor(Board::isFahrenheit);
    delay(400);
    drawProgress(display, 30, "Updating weather...");
    currentWeatherClient.setMetric(IS_METRIC);
    currentWeatherClient.setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
    currentWeatherClient.updateCurrentById(&currentWeather, OPEN_WEATHER_MAP_APP_ID, OPEN_WEATHER_MAP_LOCATION_ID);
    drawProgress(display, 50, "Updating forecasts...");
    forecastClient.setMetric(IS_METRIC);
    forecastClient.setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
    uint8_t allowedHours[] = {12};
    forecastClient.setAllowedHours(allowedHours, sizeof(allowedHours));
    forecastClient.updateForecastsById(forecasts, OPEN_WEATHER_MAP_APP_ID, OPEN_WEATHER_MAP_LOCATION_ID, MAX_FORECASTS);
    readyForWeatherUpdate = false;
    drawProgress(display, 100, "Done...");

#ifdef MQTT_SUPPORT
    PublishSensorData(); // Publish to MQTT Broker .
#endif

    delay(1000);
}

void HomeServer::drawDateTime(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    HomeServer::now = time(nullptr);
    struct tm *timeInfo;
    timeInfo = localtime(&HomeServer::now);
    char buff[16];
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->setFont(ArialMT_Plain_10);
    String date = WDAY_NAMES[timeInfo->tm_wday];
    sprintf_P(buff, PSTR("%s, %02d/%02d/%04d"), WDAY_NAMES[timeInfo->tm_wday].c_str(), timeInfo->tm_mday, timeInfo->tm_mon + 1, timeInfo->tm_year + 1900);
    display->drawString(64 + x, 5 + y, String(buff));
    display->setFont(ArialMT_Plain_24);
    sprintf_P(buff, PSTR("%02d:%02d:%02d"), timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
    display->drawString(64 + x, 15 + y, String(buff));
    display->setTextAlignment(TEXT_ALIGN_LEFT);
}

void HomeServer::drawCurrentWeather(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->drawString(64 + x, 38 + y, HomeServer::currentWeather.description);

    display->setFont(ArialMT_Plain_24);
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    String temp = String(HomeServer::currentWeather.temp, 1) + (IS_METRIC ? "°C" : "°F");
    display->drawString(60 + x, 5 + y, temp);

    display->setFont(Meteocons_Plain_36);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->drawString(32 + x, 0 + y, HomeServer::currentWeather.iconMeteoCon);
}

void HomeServer::drawForecast(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    drawForecastDetails(display, x, y, 0);
    drawForecastDetails(display, x + 44, y, 1);
    drawForecastDetails(display, x + 88, y, 2);
}

void HomeServer::drawForecastDetails(OLEDDisplay *display, int x, int y, int dayIndex)
{
    time_t observationTimestamp = forecasts[dayIndex].observationTime;
    struct tm *timeInfo;
    timeInfo = localtime(&observationTimestamp);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->setFont(ArialMT_Plain_10);
    display->drawString(x + 20, y, WDAY_NAMES[timeInfo->tm_wday]);

    display->setFont(Meteocons_Plain_21);
    display->drawString(x + 20, y + 12, forecasts[dayIndex].iconMeteoCon);
    String temp = String(forecasts[dayIndex].temp, 0) + (IS_METRIC ? "°C" : "°F");
    display->setFont(ArialMT_Plain_10);
    display->drawString(x + 20, y + 34, temp);
    display->setTextAlignment(TEXT_ALIGN_LEFT);
}

void HomeServer::drawHeaderOverlay(OLEDDisplay *display, OLEDDisplayUiState *state)
{
    HomeServer::now = time(nullptr);
    struct tm *timeInfo;
    timeInfo = localtime(&HomeServer::now);
    char buff[14];
    sprintf_P(buff, PSTR("%02d:%02d"), timeInfo->tm_hour, timeInfo->tm_min);

    display->setColor(WHITE);
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->drawString(0, 54, String(buff));
    display->setTextAlignment(TEXT_ALIGN_RIGHT);
    String temp = String(currentWeather.temp, 1) + (IS_METRIC ? "°C" : "°F");
    display->drawString(128, 54, temp);
    display->drawHorizontalLine(0, 52, 128);
}

void HomeServer::setReadyForWeatherUpdate()
{
    Serial.println("Setting readyForUpdate to true");
    readyForWeatherUpdate = true;
}

void HomeServer::drawCurrentRoomTemp(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    String humd = "Humidity : " + String(temp.sensorData.Humidity, 1) + "% HI :" + String(temp.sensorData.HeatIndex, 1) + "°C";
    display->drawString(64 + x, 38 + y, humd);

    display->setFont(ArialMT_Plain_24);
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    String temp1 = String(temp.sensorData.Temp_C, 1) + (IS_METRIC ? "°C" : "°F");
    display->drawString(60 + x, 5 + y, temp1);

    display->setFont(Meteocons_Plain_36);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->drawString(32 + x, 0 + y, currentWeather.iconMeteoCon);
}

#ifdef MQTT_SUPPORT
void HomeServer::PublishSensorData()
{
    if (temp.isSensorDataChanged())
    {
        temp.UpdateLatestData();
        Async_MQTT::Publish(Topic_Temp, (String(temp.sensorData.Temp_C) + " C").c_str());
        Async_MQTT::Publish(Topic_Humidity, (String(temp.sensorData.Humidity) + " %").c_str());
        Async_MQTT::Publish(Topic_HeatIndex, (String(temp.sensorData.HeatIndex) + " C").c_str());
    }
#endif
}