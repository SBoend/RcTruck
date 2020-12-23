#include <SteeringWheel.h>

#define MAX_LEFT 180
#define CENTER 90
#define MAX_RIGHT 0

Servo steeringServo;
byte angle;

void SteeringWheel::Initialize(char steeringChannel) {
    if (!steeringServo.attached())
        steeringServo.attach(steeringChannel);
    
    steeringServo.write(CENTER); 
    angle = 0;   
    
#ifdef DEBUG
    Serial.println("Steering loaded!");
#endif
}

void SteeringWheel::SetSteering(byte angleToSet) {
    if (angleToSet ==  128)
        angle = 0;
    else if (angleToSet > 128) 
        angle = map (angleToSet, 128, 255, 0, 90);
    else 
        angle = map (angleToSet, 128, 0, 0, -90);

    angleToSet = map(angleToSet, 0, 255, MAX_RIGHT, MAX_LEFT);
    if (steeringServo.attached())
        steeringServo.write(angleToSet);
}

void SteeringWheel::SetCenter() {
    SetSteering(128);
}

#ifdef DEBUG
void SteeringWheel::Status() {
    Serial.print("SteeringWheel is Ready: ");
    Serial.print(steeringServo.attached());
    Serial.print("\tCurrent Angle: ");
    Serial.print(angle);
    Serial.println(".");
};
#endif