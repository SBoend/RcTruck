#include <Arduino.h>
#include <Wire.h>
#include "Control_Center.h"

bool Control_Center::readyStatus = false;
bool Control_Center::readyLeds = false;
byte Control_Center::ledsWord = 0xff;
byte Control_Center::statusWord = 0xe7;  

void Control_Center::WriteStatus() {
    byte fehler = 4;
    Wire.beginTransmission(ADDR_STATUS);
    Wire.write(Control_Center::statusWord);
    fehler = Wire.endTransmission();
    Control_Center::readyStatus = (fehler != 4);

    fehler = 4;
    Wire.beginTransmission(ADDR_LIGHTS);
    Wire.write(Control_Center::ledsWord);
    fehler = Wire.endTransmission();
    Control_Center::readyLeds = (fehler != 4);
}        

void Control_Center::StatusOn(bool aktiv) { 
    if (aktiv) 
        SET_LED_ON(Control_Center::statusWord, STATUS_L_G);
    else 
        Control_Center::statusWord = 0xe7; 
    
    Control_Center::WriteStatus();
}

void Control_Center::StatusReady(bool aktiv) {    
    if (aktiv) { 
        SET_LED_ON(Control_Center::statusWord, STATUS_L_Y);
        SET_RELAY_ON(Control_Center::statusWord, STATUS_R_1);
        SET_RELAY_ON(Control_Center::statusWord, STATUS_R_2);
    } else {
        SET_LED_OFF(Control_Center::statusWord, STATUS_L_Y);
        SET_RELAY_OFF(Control_Center::statusWord, STATUS_R_1);
        SET_RELAY_OFF(Control_Center::statusWord, STATUS_R_2);
    }
    Control_Center::WriteStatus();
}

void Control_Center::StatusHold(bool aktiv){
    if (aktiv) { 
        SET_LED_ON(Control_Center::statusWord, STATUS_L_R);
        SET_LED_OFF(Control_Center::statusWord, STATUS_L_Y);
        SET_RELAY_OFF(Control_Center::statusWord, STATUS_R_1);
    } else {
        SET_LED_OFF(Control_Center::statusWord, STATUS_L_R);
    }
    Control_Center::WriteStatus();
}

void Control_Center::StatusDataIncomming(){
    if (Control_Center::statusWord & STATUS_L_R)
        SET_LED_OFF(Control_Center::statusWord, STATUS_L_R);
    else 
        SET_LED_ON(Control_Center::statusWord, STATUS_L_R);

    Control_Center::WriteStatus();
}

void Control_Center::Initialize() {
    byte fehler = 4;
    Wire.begin();
    Wire.setClock(400000L);
    Wire.beginTransmission(ADDR_LIGHTS);
    fehler = Wire.endTransmission();
    Control_Center::readyLeds = (fehler != 4);

    fehler = 4;
    Wire.beginTransmission(ADDR_STATUS);
    fehler = Wire.endTransmission();
    Control_Center::readyStatus = (fehler != 4);

    Control_Center::WriteStatus();    
}
#ifdef DEBUG
void Control_Center::Status() {
    Serial.print("Controllcenter Status: ");
    Serial.print(Control_Center::readyStatus);
    Serial.print("\tValue: ");
    Serial.print(Control_Center::statusWord);
    Serial.print("\tLights: ");
    Serial.print(Control_Center::readyLeds);
    Serial.print("\tValue: ");
    Serial.print(Control_Center::ledsWord);
    Serial.println(".");
}
#endif
