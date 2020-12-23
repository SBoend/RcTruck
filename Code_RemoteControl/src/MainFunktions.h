#ifndef MainFunctions_h
#define MainFunctions_h

#include <Arduino.h>

class MainFunktions {
    public:
        void ReadSerial();
    private:
        void handleKeyPress(String inputString);
};

#endif