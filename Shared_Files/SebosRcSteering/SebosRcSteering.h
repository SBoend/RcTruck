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
        void SetSteering(char v);
        void SetThrottle(char v);
    // Gears
        void SetGear(char gear);
        void SetClutch();
        void SetShiftUp();
        void SetShiftDown();
        void SetShiftReverse();
        void SetShiftForward();
        bool HasGearData();
        bool GetShiftReverse();
        bool GetShiftForward();
        bool GetClutch();
        bool GetShiftUp();
        bool GetShiftDown();
        char GetGear();
    private: 
};


#endif