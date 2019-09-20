#include "RGBLed.h"
#include "InBuiltLed.h"


class SingleChannelEsp8266
{ // Fix Pin Devices.
    // Esp8266 pins.
    // #define ESP8266_GPIO2    2 // Blue LED.
    // #define ESP8266_GPIO4    4 // Relay control.
    // #define ESP8266_GPIO5    5 // Optocoupler input.
    // #define LED_PIN          ESP8266_GPIO2

    const int LED_I_Pin = 2;
    const int Pin_O_Relay = 4;
    const int Pin_I_OC_Input = 5;
    bool isRelayOn = false;
    bool isSwitchOn = false;

protected:
    InBuilt_LED led;

public:
    SingleChannelEsp8266()
    {
        led = InBuilt_LED(LED_I_Pin);
    }
    ~SingleChannelEsp8266()
    {
        led.~InBuilt_LED();
        free(this);
    }

    void CallInSetUp();

    void CallInSetUp()
    {
        pinMode(LED_I_Pin, INPUT);
        pinMode(Pin_I_OC_Input, INPUT);
        pinMode(Pin_O_Relay, OUTPUT);

        TongleLed(true);
        delay(1000);
        TongleLed(false);
    }

    void CallInLoop();

    // Switch on led On or Off, True for On and False for Off
    void TongleLed(bool lights = true);
    void TongleLed(bool lights = true)
    {
        led.LedOnOff(lights);
    }

    void OnOffRelay(bool relay = true);
    bool ReadInputSwitch();

    bool IsRelayOn();
    bool IsSwitchOn();
};
