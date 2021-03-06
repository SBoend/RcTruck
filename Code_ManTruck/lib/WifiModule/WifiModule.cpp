#include "WifiModule.h"

long WifiModule::LastPackageTime;   
long WifiModule::timeout;
long WifiModule::prevoiusMillis;
NRFLite Radio;

byte data_led_counter = 0;
bool IsRecieving();     

bool WifiModule::Initialize(char radioId, char wifiPinCE, char wifiPinCSN, unsigned long timeOutConfig) {
    WifiModule::timeout = timeOutConfig;
    WifiModule::prevoiusMillis = millis();
    return Radio.init(radioId, wifiPinCE, wifiPinCSN);
}

void WifiModule::Read() {
    long currentMillis = millis();

    if (!Radio.hasData() && currentMillis - WifiModule::prevoiusMillis >= WifiModule::timeout) 
        WifiModule::EmergencyStop();
    else 
        WifiModule::prevoiusMillis = WifiModule::ReadData();   
}

long WifiModule::ReadData() {
    if (data_led_counter != 5)
        data_led_counter++; 
    else {
        Hardware::controlCenter.StatusDataIncomming();
        data_led_counter = 0;
    }

    Radio.readData(&SebosRcSteering::RemoteData);

    if (SebosRcSteering::HasGearData()) {
        WifiModule::SwitchGears();
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
    Hardware::controlCenter.StatusHold(true);
}
