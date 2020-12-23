#ifndef WifiModule_h
#define WifiModule_h

#include <Arduino.h>
#include <SPI.h>
#include <NRFLite.h>
#include <SebosRcSteering.h>
#include <GearBox.h>

const static uint8_t RADIO_ID = 0;             // Our radio's id.
const static uint8_t PIN_RADIO_CE = A3;
const static uint8_t PIN_RADIO_CSN = 10;

class WifiModule {
    public:
        bool Initialize(Gearbox mainGearbox, char radioId = RADIO_ID, char wifiPinCE = PIN_RADIO_CE, char wifiPinCSN = PIN_RADIO_CSN , int timeOutConfig = 1000);
        void TryRemoteLoop();
    private:
        void SwitchGears();
        unsigned long ReadData();

        SebosRcSteering protokoll; 
        NRFLite Radio;      
        Gearbox gearbox;

        long LastPackageTime;   
        long timeout;   
};

#endif