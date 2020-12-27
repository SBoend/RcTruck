#include "SebosEngine.h"

bool isReverse = false;
byte currentSpeed = 0;
byte engine_LPWM, engine_L_EN, engine_RPWM, engine_R_EN;

void SebosEngine::Initialize(byte RPWM, byte LPWM, byte R_EN, byte L_EN)
{    
    engine_RPWM = RPWM;
    engine_LPWM = LPWM;
    engine_R_EN = R_EN;
    engine_L_EN = L_EN;
    // Set Motor to 0
    pinMode(engine_RPWM,OUTPUT);
    pinMode(engine_LPWM,OUTPUT);
    pinMode(engine_R_EN,OUTPUT);
    pinMode(engine_L_EN,OUTPUT);
    
    EmergencyStop();
}

void SebosEngine::SetDirection(char direction) {
    isReverse = (direction == 'R' || direction == 'r');
}

void SebosEngine::SetSpeed(byte speed)
{
    currentSpeed = map(speed, 0, 255, 0, 100);

    if (isReverse)
        MoveBackward();
    else 
        MoveForward();
}

void SebosEngine::MoveForward() {
  digitalWrite(engine_RPWM, LOW);
  digitalWrite(engine_LPWM, HIGH);
  digitalWrite(engine_R_EN, HIGH);
  analogWrite(engine_L_EN, getMaxValueFromPercent(currentSpeed));
}

void SebosEngine::MoveBackward() {
  digitalWrite(engine_RPWM, HIGH);
  digitalWrite(engine_LPWM, LOW);
  analogWrite(engine_R_EN, getMaxValueFromPercent(currentSpeed));
  digitalWrite(engine_L_EN, HIGH);
}

void SebosEngine::EmergencyStop() {
    isReverse = false;
    digitalWrite(engine_RPWM, LOW);
    digitalWrite(engine_LPWM, LOW);
    digitalWrite(engine_R_EN, LOW);
    digitalWrite(engine_L_EN, LOW); 
}

void SebosEngine::SetBreak(byte brakePower) {
    return;
}

void SebosEngine::SetFreeRun() {
    digitalWrite(engine_R_EN, LOW);
    digitalWrite(engine_L_EN, LOW);
}

byte SebosEngine::getMaxValueFromPercent(byte speed) {
     return currentSpeed;
}