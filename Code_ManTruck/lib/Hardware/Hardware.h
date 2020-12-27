#ifndef Hardware_h
#define Hardware_h

#include <Arduino.h>
#include <NRFLite.h>
#include <SPI.h>
#include "SebosEngine.h"
#include "SteeringWheel.h"
#include "Transmission.h"

#ifdef ENABLE_REMOTE
#include "ReadSpektrumDX3E.h"
#endif

class Hardware {
    public:
#ifdef ENABLE_REMOTE
        static ReadSpektrumDX3E readRemote;
#endif
        static SebosEngine engine;
        static SteeringWheel steeringWheel;
        static Transmission transmission;
    private:
};

#endif