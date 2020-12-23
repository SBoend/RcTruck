#ifndef MainFunctions_h
#define MainFunctions_h

#include <Arduino.h>
#include <ReadSpektrumDX3E.h>
#include <Transmission.h>
#include <WifiModule.h>
#include <SteeringWheel.h>

class MainFunktions {
    public:
        bool ToggleRemote;
        void RemoteControl();
        void HandleKeyPress(String inputString);
        ReadSpektrumDX3E readRemote;
        SteeringWheel steeringWheel;
        Transmission transmission;
        WifiModule wifiModule;
    private:
};

#endif