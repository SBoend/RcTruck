#ifndef WifiModule_h
#define WifiModule_h

#include <Arduino.h>
#include <SPI.h>
#include <NRFLite.h>
#include <SebosRcSteering.h>
#include <Transmission.h>
#include <SteeringWheel.h>

const static uint8_t RADIO_ID = 0;             // Our radio's id.
const static uint8_t PIN_RADIO_CE = A3;
const static uint8_t PIN_RADIO_CSN = 10;

class WifiModule {
    public:
        bool Initialize(Transmission transmission, SteeringWheel steering, char radioId = RADIO_ID, char wifiPinCE = PIN_RADIO_CE, char wifiPinCSN = PIN_RADIO_CSN, unsigned long timeOutConfig = 1000ul);
        void TryRemoteLoop();
    private:
        void SwitchGears();
        void EmergencyStop();
        unsigned long ReadData();

        SebosRcSteering protokoll; 
        NRFLite Radio;      
        Transmission transmission;
        SteeringWheel steeringWheel;

        long LastPackageTime;   
        long timeout;   
};

#endif