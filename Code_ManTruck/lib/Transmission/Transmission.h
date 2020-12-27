#ifndef Transmission_h
#define Transmission_h

#include <Arduino.h>
#include <Servo.h>

class Transmission {
  public:
    static void Initialize(char transmissionChannel);
    static void SetGear(char gear);
    static void SetFreeRun();
    static void ShiftUp();
    static void ShiftDown();
#ifdef DEBUG
    static void Status();
#endif
  private:
    static Servo transmissionServo;
    static char currentGear;
};

#endif