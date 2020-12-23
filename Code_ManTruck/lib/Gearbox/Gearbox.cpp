#include <Gearbox.h>

#define GEAR_FIRST 180
#define FREERUN_FIRST_SECOND 135
#define GEAR_SECOND 90
#define FREERUN_SECOND_THIRD 45
#define GEAR_THIRD 0

Servo gearServo;
char currentGear;

void Gearbox::Initialize(char gearChannel) {
    if (!gearServo.attached())
        gearServo.attach(gearChannel);
    
    gearServo.write(FREERUN_FIRST_SECOND); 
    currentGear = 1;   
    
#ifdef DEBUG
    Serial.println("Gearbox loaded!");
#endif
}

void Gearbox::SetGear(char gear) {
    if (currentGear == gear)
        return;

    switch (gear)
    {
        case 1:
#ifdef DEBUG
    Serial.println("Gearbox: 1. Gear");
#endif
            currentGear = gear; gearServo.write(GEAR_FIRST); break;
        case 2:
#ifdef DEBUG
    Serial.println("Gearbox: 2. Gear");
#endif
            currentGear = gear; gearServo.write(GEAR_SECOND); break;
        case 3:
#ifdef DEBUG
    Serial.println("Gearbox: 3. Gear");
#endif
            currentGear = gear; gearServo.write(GEAR_THIRD); break;
        default:
            currentGear = gear; SetFreeRun(); break;
    }
}

void Gearbox::SetFreeRun() {
#ifdef DEBUG
    Serial.println("Gearbox: Freerun");
#endif
    if (currentGear == 3)
        gearServo.write(FREERUN_SECOND_THIRD);
    else
        gearServo.write(FREERUN_FIRST_SECOND);
}

void Gearbox::ShiftUp() {
    if (currentGear == 1)
        SetGear(2);
    else if (currentGear == 2)
        SetGear(3);
}

void Gearbox::ShiftDown(){    
    if (currentGear == 3)
        SetGear(2);
    else if (currentGear == 2)
        SetGear(1);
}

void Gearbox::Status() {
    Serial.print("Gearbox is Ready: ");
    Serial.print(gearServo.attached());
    Serial.print("\tCurrentGear: ");
    Serial.print(currentGear);
    Serial.println(".");
};
