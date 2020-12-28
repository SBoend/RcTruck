#ifndef Engine_h
#define Engine_h

#include <Arduino.h>

class Engine {
    public:
        /* RPWM & R_EN und LPWM & L_EN For FreeRunMode changed in program code) */
        static void Initialize(byte RPWM, byte LPWM, byte R_EN, byte L_EN);
        static void SetSpeed(byte speed);
        static void EmergencyStop();
        static void SetDirection(char direction);
        static void SetBreak(byte brakePower);
        static void SetFreeRun();
#ifdef DEBUG
        static string Status();
#endif
    private:
        static byte getMaxValueFromPercent(byte speed);
        static void MoveForward();
        static void MoveBackward();
};

#endif