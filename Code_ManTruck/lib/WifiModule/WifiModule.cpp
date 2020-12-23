#include <WifiModule.h>

SebosRcSteering protokoll; 
NRFLite Radio;

long LastPackageTime;   
unsigned long timeout;

bool IsRecieving();     

bool WifiModule::Initialize(Gearbox mainGearbox, char radioId, char wifiPinCE, char wifiPinCSN, unsigned long timeOutConfig) {
    gearbox = mainGearbox;
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
    Radio.readData(&protokoll.RemoteData);

    if (protokoll.HasGearData()) {
        SwitchGears();
    }

    return millis();
}

void WifiModule::SwitchGears() {
    if (protokoll.GetShiftReverse()) {
        // TODO: CHANGE MOTOR DIRECTION
        gearbox.SetGear(1);
    } else if (protokoll.GetShiftForward()) {
        // TODO: CHANGE MOTOR DIRECTION
        gearbox.SetGear(1);
        return;
    } else if (protokoll.GetClutch()) {
        gearbox.SetFreeRun();
    } else if (protokoll.GetShiftUp()) {
        gearbox.ShiftUp();
    } else if (protokoll.GetShiftDown()) {
        gearbox.ShiftDown();
    } else {
        gearbox.SetGear(protokoll.GetGear());
    } 
}

void WifiModule::EmergencyStop() {
    gearbox.SetFreeRun();
}
