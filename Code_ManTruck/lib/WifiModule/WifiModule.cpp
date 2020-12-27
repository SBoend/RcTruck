#include "WifiModule.h"

long LastPackageTime;   
unsigned long timeout;
NRFLite Radio;

bool IsRecieving();     

bool WifiModule::Initialize(
        char radioId, char wifiPinCE, char wifiPinCSN, unsigned long timeOutConfig) {
    timeout = timeOutConfig;
    return Radio.init(radioId, wifiPinCE, wifiPinCSN);
}

void WifiModule::TryRemoteLoop() {
    unsigned long previousMillis = millis();
    unsigned long currentMillis = millis();
    do {
        currentMillis = millis();
        if (Radio.hasData())
            previousMillis = ReadData();        

    } while (currentMillis - previousMillis >= timeout);
    EmergencyStop();
}

unsigned long WifiModule::ReadData() {
    Radio.readData(&SebosRcSteering::RemoteData);

    if (SebosRcSteering::HasGearData()) {
        SwitchGears();
    }

    Hardware::steeringWheel.SetSteering(SebosRcSteering::RemoteData.Steering);
    Hardware::engine.SetSpeed(SebosRcSteering::RemoteData.Throttle);
    return millis();
}

void WifiModule::SwitchGears() {
    if (SebosRcSteering::GetShiftReverse()) {
        Hardware::engine.SetDirection('R');
        Hardware::transmission.SetGear(1);
    } else if (SebosRcSteering::GetShiftForward()) {
        Hardware::engine.SetDirection('F');
        Hardware::transmission.SetGear(1);
        return;
    } else if (SebosRcSteering::GetClutch()) {
        Hardware::transmission.SetFreeRun();
    } else if (SebosRcSteering::GetShiftUp()) {
        Hardware::transmission.ShiftUp();
    } else if (SebosRcSteering::GetShiftDown()) {
        Hardware::transmission.ShiftDown();
    } else {
        Hardware::transmission.SetGear(SebosRcSteering::GetGear());
    } 
}

void WifiModule::EmergencyStop() {
    Hardware::engine.SetSpeed(0);
    Hardware::transmission.SetFreeRun();
    Hardware::steeringWheel.SetCenter();
}
