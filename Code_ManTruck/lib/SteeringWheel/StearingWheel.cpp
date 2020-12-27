#include "SteeringWheel.h"

#define MAX_LEFT 180
#define CENTER 90
#define MAX_RIGHT 0

Servo SteeringWheel::steeringServo;
byte SteeringWheel::angle;

void SteeringWheel::Initialize(char steeringChannel) {
    if (!SteeringWheel::steeringServo.attached())
        SteeringWheel::steeringServo.attach(steeringChannel);
    
    SteeringWheel::steeringServo.write(CENTER); 
    SteeringWheel::angle = 0;   
    
#ifdef DEBUG
    Serial.println("Steering loaded!");
#endif
}

void SteeringWheel::SetSteering(byte angleToSet) {
    if (angleToSet ==  128)
        SteeringWheel::angle = 0;
    else if (angleToSet > 128) 
        SteeringWheel::angle = map (angleToSet, 128, 255, 0, 90);
    else 
        SteeringWheel::angle = map (angleToSet, 128, 0, 0, -90);

    angleToSet = map(angleToSet, 0, 255, MAX_RIGHT, MAX_LEFT);
    if (SteeringWheel::steeringServo.attached())
        SteeringWheel::steeringServo.write(angleToSet);
}

void SteeringWheel::SetCenter() {
    SteeringWheel::SetSteering(128);
}

#ifdef DEBUG
void SteeringWheel::Status() {
    Serial.print("SteeringWheel is Ready: ");
    Serial.print(SteeringWheel::steeringServo.attached());
    Serial.print("\tCurrent Angle: ");
    Serial.print(SteeringWheel::angle);
    Serial.println(".");
};
#endif