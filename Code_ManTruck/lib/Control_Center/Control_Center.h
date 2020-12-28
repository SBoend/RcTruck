#ifndef CONTROL_CENTER_h
#define CONTROL_CENTER_h

#define SET_LED_ON(byte, bit) ((byte) |= (1UL << (bit)))
#define SET_LED_OFF(byte,bit) ((byte) &= ~(1UL << (bit)))

#define SET_RELAY_ON(byte,bit) ((byte) &= ~(1UL << (bit)))
#define SET_RELAY_OFF(byte, bit) ((byte) |= (1UL << (bit)))


#define ADDR_STATUS  0x20
#define STATUS_L_G   0
#define STATUS_L_Y   1
#define STATUS_L_R   2
#define STATUS_R_1   3
#define STATUS_R_2   4

#define ADDR_LIGHTS  0x21
#define LIGHTS_POSITION     0
#define LIGHTS_BRAKE        1
#define LIGHTS_DAYLIGHT     2
#define LIGHTS_NIGHTLIGHT   3
#define LIGHTS_HIGH_BEAM    4
#define LIGHTS_REVERSE      5
#define LIGHTS_TURN_RIGHT   6
#define LIGHTS_TURN_LEFT    7

class Control_Center {
    private:
        static bool readyStatus;
        static bool readyLeds;
        static byte ledsWord;
        static byte statusWord;        
        static void WriteStatus();
    public:
        static void StatusOn(bool aktiv);
        static void StatusReady(bool aktiv);
        static void StatusHold(bool aktiv);
        static void StatusDataIncomming();
        static void Initialize();
#ifdef DEBUG
        Status();
#endif
};


#endif