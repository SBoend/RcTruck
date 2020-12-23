#ifndef Gearbox_h
#define Gearbox_h

#include <Arduino.h>
#include <Servo.h>

class Gearbox {
  public:
    void Initialize(char gearChannel);
    void SetGear(char gear);
    void SetFreeRun();
    void ShiftUp();
    void ShiftDown();
    void Status();
  private:
    Servo gearServo;
    int gear;
};

#endif