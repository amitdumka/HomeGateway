#ifndef RELAY_SWITCH_H
#define RELAY_SWITCH_H

#include <Arduino.h>
#include "RGBLed.h"
#include "InBuiltLed.h"

//TODO: Class is due for testing

class RelaySwitch{

protected:
    
    int Pin_O_Relay = 0;  //Relay out pin where relay is connected
    int Pin_I_InputSwitch = -999; // -666 Only RelayPin is activated  , Can be used for Manaul Input for relay

    bool RelayState = false;  // Set/get relay state , is relay on or off
    bool SwitchState = false; // Set/get switch state is switch is pressed to on or off

public:

    RelaySwitch(int relayPin)
    {

        Pin_O_Relay = relayPin;
        Pin_I_InputSwitch = -666;
    }
    RelaySwitch(int relayPin, int switchPin)
    {
        Pin_O_Relay = relayPin;
        Pin_I_InputSwitch = switchPin;
    }

    void InitSwitch()
    {
        pinMode(Pin_O_Relay, OUTPUT);
        if (Pin_I_InputSwitch >= 0)
            pinMode(Pin_I_InputSwitch, OUTPUT);
    }

    void TongleSwitch(bool state);
    void RelayOnOFF(bool state = true);

    bool IsRelayOn() { return RelayState; }
    bool IsSwitchOn() { return SwitchState; }

    void SetSwitchState(bool state = true)
    {
        SwitchState = state;
    }

    // SwitchOnOffRelay will operate and update status  of Input Switch
    void SwitchOnOffRelay(bool relayonoff, bool inputmode, bool switchmode = NULL)
    {
        if (inputmode && switchmode != IsSwitchOn())
        {

            RelayOnOFF(relayonoff);
            SetSwitchState(switchmode);
        }
        else
            RelayOnOFF(relayonoff);
    }
};

#endif