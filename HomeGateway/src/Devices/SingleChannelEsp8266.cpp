#include "SingleChannelESP8266.h"

    SingleChannelEsp8266::SingleChannelEsp8266()
    {
        led = InBuilt_LED(LED_I_Pin);
    }
    SingleChannelEsp8266::~SingleChannelEsp8266()
    {
        led.~InBuilt_LED();
        free(this);
    }


    void SingleChannelEsp8266::CallInSetUp()
    {
        pinMode(LED_I_Pin, INPUT);
        pinMode(Pin_I_OC_Input, INPUT);
        pinMode(Pin_O_Relay, OUTPUT);

        TongleLed(true);
        delay(1000);
        TongleLed(false);
    }

    void SingleChannelEsp8266::CallInLoop(){}

    // Switch on led On or Off, True for On and False for Off
    
    void SingleChannelEsp8266::TongleLed(bool lights = true)
    {
        led.LedOnOff(lights);
    }

    void SingleChannelEsp8266::OnOffRelay(bool relay = true){}
    bool SingleChannelEsp8266::ReadInputSwitch(){}

    bool SingleChannelEsp8266::IsRelayOn(){}
    bool SingleChannelEsp8266::IsSwitchOn(){}