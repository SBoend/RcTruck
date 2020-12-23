#ifndef ReadSpektrumDX3E_h
#define ReadSpektrumDX3E_h
#include <Arduino.h>

class ReadSpektrumDX3E {
    public:
        void Initialize(char SteeringPin, char ThrottelPin, char AuxPin);
        void Read();
        bool IsReady();
        uint16_t Direction;
        uint16_t Turning;
        uint16_t Speed;
        uint16_t Angle;
        char Gear;
    private:
        void GetGear();
        void GetSteering();
        void GetThrottle();
        int throttel;
        int steering;
};

#endif