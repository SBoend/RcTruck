#ifndef MainFunctions_h
#define MainFunctions_h

#include <CarMovement.h>
#include <Arduino.h>
#include <ReadSpektrumDX3E.h>
#include <Gearbox.h>

class MainFunktions {
    public:
        void ReadSerial();
        void RemoteControl();
        CarMovement myMotor;
        ReadSpektrumDX3E readRemote;
        Gearbox gearbox;
        bool ToggleRemote;
    private:
        void handleKeyPress(String inputString);
};

#endif