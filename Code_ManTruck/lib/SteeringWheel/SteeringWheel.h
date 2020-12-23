#ifndef SteeringWheel_h
#define SteeringWheel_h

#include <Arduino.h>
#include <Servo.h>

class SteeringWheel {
  public:
    void Initialize(char steeringChannel);
    void SetSteering(byte angleToSet);
    void SetCenter();
#ifdef DEBUG
    void Status();
#endif
  private:
    Servo steeringServo;
    byte angle;
};

#endif