#ifndef Transmission_h
#define Transmission_h

#include <Arduino.h>
#include <Servo.h>

class Transmission {
  public:
    void Initialize(char transmissionChannel);
    void SetGear(char gear);
    void SetFreeRun();
    void ShiftUp();
    void ShiftDown();
#ifdef DEBUG
    void Status();
#endif
  private:
    Servo transmissionServo;
    char gear;
};

#endif