#ifndef SebosRcSteering_h
#define SebosRcSteering_h

struct DataPackage {
    char FromRadioId;
    char ServoValue;
    char Steering;
    char Throttle;
    char Gear;
};

class SebosRcSteering {
    public:
        static DataPackage RemoteData;
    // Steering    
        static void SetSteering(char v);
        static void SetThrottle(char v);
    // Gears
        static void SetGear(char gear);
        static void SetClutch();
        static void SetShiftUp();
        static void SetShiftDown();
        static void SetShiftReverse();
        static void SetShiftForward();
        static bool HasGearData();
        static bool GetShiftReverse();
        static bool GetShiftForward();
        static bool GetClutch();
        static bool GetShiftUp();
        static bool GetShiftDown();
        static char GetGear();
    private: 
};


#endif