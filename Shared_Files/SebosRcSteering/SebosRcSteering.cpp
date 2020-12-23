#include <SebosRcSteering.h>

DataPackage SebosRcSteering::RemoteData;
// Steering    
    void SebosRcSteering::SetSteering(char v) { RemoteData.Steering = v; }
    void SebosRcSteering::SetThrottle(char v) { RemoteData.Throttle = v; }
// Gears
    void SebosRcSteering::SetGear(char gear)  { RemoteData.Gear = gear & 0b0000011; }
    void SebosRcSteering::SetClutch()         { RemoteData.Gear = 0b0000100; }
    void SebosRcSteering::SetShiftUp()        { RemoteData.Gear = 0b0001000; }
    void SebosRcSteering::SetShiftDown()      { RemoteData.Gear = 0b0001100; }
    void SebosRcSteering::SetShiftReverse()   { RemoteData.Gear = 0b0010001; }
    void SebosRcSteering::SetShiftForward()   { RemoteData.Gear = 0b0010000; }
    bool SebosRcSteering::HasGearData()       { return RemoteData.Gear;}
    bool SebosRcSteering::GetShiftReverse()   { return RemoteData.Gear & 0b0010001; }
    bool SebosRcSteering::GetShiftForward()   { return RemoteData.Gear & 0b0010000; }
    bool SebosRcSteering::GetClutch()         { return RemoteData.Gear & 0b0000100; }
    bool SebosRcSteering::GetShiftUp()        { return RemoteData.Gear & 0b0001000; }
    bool SebosRcSteering::GetShiftDown()      { return RemoteData.Gear & 0b0001100; }
    char SebosRcSteering::GetGear()           { return RemoteData.Gear & 0b0000011; }