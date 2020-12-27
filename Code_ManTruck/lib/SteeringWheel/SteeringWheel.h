#ifndef SteeringWheel_h
#define SteeringWheel_h

#include <Arduino.h>
#include <Servo.h>

class SteeringWheel {
  public:
    static void Initialize(char steeringChannel);
    static void SetSteering(byte angleToSet);
    static void SetCenter();
#ifdef DEBUG
    static void Status();
#endif
  private:
    static Servo steeringServo;
    static byte angle;
};

#endif