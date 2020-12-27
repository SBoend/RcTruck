#include "Transmission.h"

#define GEAR_FIRST 180
#define GEAR_SECOND 90
#define GEAR_THIRD 0
#define FREERUN_FIRST_SECOND 135
#define FREERUN_SECOND_THIRD 45

Servo Transmission::transmissionServo;
char Transmission::currentGear;

void Transmission::Initialize(char gearChannel) {
    if (!Transmission::transmissionServo.attached())
        Transmission::transmissionServo.attach(gearChannel);
    
    Transmission::transmissionServo.write(FREERUN_FIRST_SECOND); 
    Transmission::currentGear = 1;   
    
#ifdef DEBUG
    Serial.println("Transmissions loaded!");
#endif
}

void Transmission::SetGear(char gear) {
    if (Transmission::currentGear == gear)
        return;

    switch (gear)
    {
        case 1:
#ifdef DEBUG
    Serial.println("Transmissions: 1. Gear");
#endif
            Transmission::currentGear = gear; Transmission::transmissionServo.write(GEAR_FIRST); break;
        case 2:
#ifdef DEBUG
    Serial.println("Transmissions: 2. Gear");
#endif
            Transmission::currentGear = gear; Transmission::transmissionServo.write(GEAR_SECOND); break;
        case 3:
#ifdef DEBUG
    Serial.println("Transmissions: 3. Gear");
#endif
            Transmission::currentGear = gear; Transmission::transmissionServo.write(GEAR_THIRD); break;
        default:
            Transmission::currentGear = 0; Transmission::SetFreeRun(); break;
    }
}

void Transmission::SetFreeRun() {
#ifdef DEBUG
    Serial.println("Transmissions: Freerun");
#endif
    if (currentGear == 3)
        Transmission::transmissionServo.write(FREERUN_SECOND_THIRD);
    else
       Transmission::transmissionServo.write(FREERUN_FIRST_SECOND);
}

void Transmission::ShiftUp() {
    if (Transmission::currentGear == 1)
        SetGear(2);
    else if (Transmission::currentGear == 2)
        SetGear(3);
}

void Transmission::ShiftDown(){    
    if (Transmission::currentGear == 3)
        Transmission::SetGear(2);
    else if (Transmission::currentGear == 2)
        Transmission::SetGear(1);
}

#ifdef DEBUG
void Transmission::Status() {
    Serial.print("Transmission is Ready: ");
    Serial.print(Transmission::transmissionServo.attached());
    Serial.print("\tCurrentGear: ");
    Serial.print(Transmission::currentGear);
    Serial.println(".");
};
#endif