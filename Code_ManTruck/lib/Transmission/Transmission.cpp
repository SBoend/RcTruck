#include <Transmission.h>

#define GEAR_FIRST 180
#define GEAR_SECOND 90
#define GEAR_THIRD 0
#define FREERUN_FIRST_SECOND 135
#define FREERUN_SECOND_THIRD 45

Servo transmissionServo;
char currentGear;

void Transmission::Initialize(char gearChannel) {
    if (!transmissionServo.attached())
        transmissionServo.attach(gearChannel);
    
    transmissionServo.write(FREERUN_FIRST_SECOND); 
    currentGear = 1;   
    
#ifdef DEBUG
    Serial.println("Transmissions loaded!");
#endif
}

void Transmission::SetGear(char gear) {
    if (currentGear == gear)
        return;

    switch (gear)
    {
        case 1:
#ifdef DEBUG
    Serial.println("Transmissions: 1. Gear");
#endif
            currentGear = gear; transmissionServo.write(GEAR_FIRST); break;
        case 2:
#ifdef DEBUG
    Serial.println("Transmissions: 2. Gear");
#endif
            currentGear = gear; transmissionServo.write(GEAR_SECOND); break;
        case 3:
#ifdef DEBUG
    Serial.println("Transmissions: 3. Gear");
#endif
            currentGear = gear; transmissionServo.write(GEAR_THIRD); break;
        default:
            currentGear = 0; SetFreeRun(); break;
    }
}

void Transmission::SetFreeRun() {
#ifdef DEBUG
    Serial.println("Transmissions: Freerun");
#endif
    if (currentGear == 3)
        transmissionServo.write(FREERUN_SECOND_THIRD);
    else
        transmissionServo.write(FREERUN_FIRST_SECOND);
}

void Transmission::ShiftUp() {
    if (currentGear == 1)
        SetGear(2);
    else if (currentGear == 2)
        SetGear(3);
}

void Transmission::ShiftDown(){    
    if (currentGear == 3)
        SetGear(2);
    else if (currentGear == 2)
        SetGear(1);
}

#ifdef DEBUG
void Transmission::Status() {
    Serial.print("Transmission is Ready: ");
    Serial.print(transmissionServo.attached());
    Serial.print("\tCurrentGear: ");
    Serial.print(currentGear);
    Serial.println(".");
};
#endif