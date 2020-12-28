#ifndef WifiModule_h
#define WifiModule_h

#include <Arduino.h>
#include <NRFLite.h>
#include "Hardware.h"
#include "SebosRcSteering.h"
#include "Engine.h"
#include "SteeringWheel.h"
#include "Transmission.h"

const static uint8_t RADIO_ID = 0;             // Our radio's id.
const static uint8_t PIN_RADIO_CE = A3;
const static uint8_t PIN_RADIO_CSN = 10;

class WifiModule {
    public:
        static bool Initialize(
            char radioId = RADIO_ID, char wifiPinCE = PIN_RADIO_CE, char wifiPinCSN = PIN_RADIO_CSN, unsigned long timeOutConfig = 1000ul);
        static void Read();
        static void EmergencyStop();
    private:
        static void SwitchGears();
        static long ReadData();
        static long LastPackageTime;   
        static long timeout;      
        static long prevoiusMillis;  
};

#endif