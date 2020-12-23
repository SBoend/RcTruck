#ifndef MainFunctions_h
#define MainFunctions_h

#include <CarMovement.h>
#include <Arduino.h>
#include <ReadSpektrumDX3E.h>
#include <Transmission.h>
#include <WifiModule.h>
#include <SteeringWheel.h>

class MainFunktions {
    public:
        void RemoteControl();
        void HandleKeyPress(String inputString);
        CarMovement myMotor;
        ReadSpektrumDX3E readRemote;
        Transmission transmission;
        WifiModule wifiModule;
        SteeringWheel steeringWheel;
        bool ToggleRemote;
    private:
};

#endif