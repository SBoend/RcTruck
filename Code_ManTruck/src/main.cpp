#include <Arduino.h>
#include <Bounce2.h>
#include "Hardware.h"
#include "WifiModule.h"
#include "Engine.h"
#include "SteeringWheel.h"
#include "Transmission.h"

#define SET_BIT(byte, bit) ((byte) |= (1UL << (bit)))
#define CLEAR_BIT(byte,bit) ((byte) &= ~(1UL << (bit)))

#define SERVO_STEER     15  // A1
#define SERVO_GEAR      16  // A2

#define MOTOR_R_EN      5
#define MOTOR_L_EN      6
#define MOTOR_RPWM      7
#define MOTOR_LPWM      8

#define BUTTON_RESET    9

#define PIN_RADIO_CE    22  // A3
#define PIN_RADIO_CSN   10

#define RC_STEERING     25  // A6 
#define RC_THROTTLE     26  // A7
#define RC_AUX          14  // A0

#define BLOCK_SCL       15  // A4
#define BLOCK_SDA       16  // A5

#define STATUS_DISPLAY  0x21
#define STATUS_B0_L_G   0
#define STATUS_B1_L_Y   1
#define STATUS_B2_L_R   2
#define STATUS_B3_R_1   3
#define STATUS_B4_R_2   4


Bounce bounce = Bounce();

byte status_Value = 0xff;

bool wifiIsReady = false;
WifiModule wifi;
int cnt = 0;

void WriteStatus() {
  Wire.beginTransmission(STATUS_DISPLAY);
  Wire.write(status_Value);
  Wire.endTransmission();
}

void setup() {
  CLEAR_BIT(status_Value, STATUS_B0_L_G);
  Wire.begin();  
  WriteStatus();
  
  Serial.begin(9600);

  bounce.attach( BUTTON_RESET, INPUT_PULLUP );
  bounce.interval(100); // interval in ms
  
  Hardware::transmission.Initialize(SERVO_GEAR);
  Hardware::steeringWheel.Initialize(SERVO_STEER);
  Hardware::engine.Initialize(MOTOR_RPWM, MOTOR_LPWM, MOTOR_R_EN, MOTOR_L_EN);

  wifiIsReady = wifi.Initialize();

  if (wifiIsReady) {
    CLEAR_BIT(status_Value, STATUS_B1_L_Y);
    SET_BIT(status_Value, STATUS_B3_R_1);
    SET_BIT(status_Value, STATUS_B4_R_2);
  } else {
    SET_BIT(status_Value, STATUS_B1_L_Y);
    CLEAR_BIT(status_Value, STATUS_B3_R_1);
    CLEAR_BIT(status_Value, STATUS_B4_R_2);
  }

  WriteStatus();
#ifdef ENABLE_REMOTE
  readRemote.Initialize(RC_STEERING, RC_THROTTLE, RC_AUX);
#endif
}

//Repeat execution
void loop() {
#ifdef DEBUG
  if (Serial.available()) {
    HandleKeyPress(Serial.readString());  
  }
#endif

  WriteStatus();
  
  if (wifiIsReady) {
    CLEAR_BIT(status_Value, STATUS_B1_L_Y);
    SET_BIT(status_Value, STATUS_B3_R_1);
    SET_BIT(status_Value, STATUS_B4_R_2);
  } else {
    SET_BIT(status_Value, STATUS_B1_L_Y);
    CLEAR_BIT(status_Value, STATUS_B3_R_1);
    CLEAR_BIT(status_Value, STATUS_B4_R_2);
  }
 
  bounce.update();
  if (bounce.changed() && bounce.read() == LOW)
  {
    wifi.EmergencyStop();
    wifiIsReady = false;
  } 
  
  if (wifiIsReady)
    wifi.Read();


#ifdef ENABLE_REMOTE
  if (mainFunc.IsReady())
    RemoteControl();
#endif
}

#ifdef DEBUG
void HandleKeyPress(String inputString) {
    for (unsigned int cnt = 0U; cnt <= inputString.length(); cnt++) {
        char input = inputString.charAt(cnt);
        // // STEERING
        // if (input == 'W' || input == 'w')
        //     myMotor.Forward(); 
        // else if (input == 'S'|| input == 's')
        //     myMotor.Backward();
        // else if (input == 'A'|| input == 'a')
        //     myMotor.Left();
        // else if (input == 'Q'|| input == 'q')
        //     myMotor.MoreLeft();
        // else if (input == 'D'|| input == 'd')
        //     myMotor.Right();
        // else if (input == 'E'|| input == 'e')
        //     myMotor.MoreRight();
        // else if (input == 'X'|| input == 'x')
        //     myMotor.FullStop();
        // else if (input == 'Y'|| input == 'y')
        //     myMotor.PrintStatus();
        // else if (input == 'R'|| input == 'r')
        //     myMotor.Accelerate();
        // else if (input == 'F'|| input == 'f')
        //     myMotor.Brake();
        // else if (input == 'm' || input == 'M') {
        //     readRemote.Read();
        // }
        // GEARBOX
        // else
        if (input == '1')
            transmission.SetGear(1);
        else if (input == '2')
            transmission.SetGear(2);
        else if (input == '3')
            transmission.SetGear(3);
        else if (input == '+')
            transmission.ShiftUp();
        else if (input == '-')
            transmission.ShiftDown();
    }
}
#endif

#ifdef ENABLE_REMOTE
void RemoteControl() {
  if (!readRemote.IsReady()) {
#ifdef DEBUG
  Serial.println("REMOTE NOT READY");
#endif
    return;
  }

  readRemote.Read();
  transmission.SetGear(readRemote.Gear);
//   if(readRemote.Turning != 0)
//   {
//       if (readRemote.Turning == 1)
//           myMotor.Left(); 
//       else if (readRemote.Turning == 2)
//           myMotor.Right();

//       myMotor.SetSpeedBoth(readRemote.Angle);
//   }  
//   else if (readRemote.Direction != 0)
//   {
//       if (readRemote.Direction == 1)
//           myMotor.Backward();
//       else if (readRemote.Direction == 2)
//           myMotor.Forward();

//       myMotor.SetSpeedBoth(readRemote.Speed);
//   }
}
#endif
