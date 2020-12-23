#include <Arduino.h>
#include <MainFunktions.h>

#define SERVO_STEER     15  // A1
#define SERVO_GEAR      16  // A2

#define MOTOR_R_EN      5
#define MOTOR_L_EN      6
#define MOTOR_LPWM      7
#define MOTOR_RPWM      8

#define BUTTON_RESET    9

#define PIN_RADIO_CE    22  // A3
#define PIN_RADIO_CSN   10

#define RC_STEERING     25  // A6 
#define RC_THROTTLE     26  // A7
#define RC_AUX          14  // A0

MainFunktions mainFunktions;
ReadSpektrumDX3E readRemote;
SteeringWheel steeringWheel;
Transmission transmission;
WifiModule wifiModule;

bool wifiIsReady = false;
int cnt = 0;

void setup() {
  Serial.begin(9600);

  transmission.Initialize(SERVO_GEAR);
  steeringWheel.Initialize(SERVO_STEER);

  wifiIsReady = wifiModule.Initialize(transmission, steeringWheel);

#ifdef ENABLE_REMOTE
  readRemote.Initialize(RC_STEERING, RC_THROTTLE, RC_AUX);
#endif
}

//Repeat execution
void loop() {
  if (Serial.available()) {
    mainFunktions.HandleKeyPress(Serial.readString());  
  }
  
  if (wifiIsReady)
    wifiModule.TryRemoteLoop();

#ifdef ENABLE_REMOTE
  if (mainFunc.IsReady())
    RemoteControl();
#endif
}

void MainFunktions::HandleKeyPress(String inputString) {
    for (unsigned int cnt = 0U; cnt <= inputString.length(); cnt++) {
        char input = inputString.charAt(cnt);
        // STEERING
        if (input == 'W' || input == 'w')
            myMotor.Forward(); 
        else if (input == 'S'|| input == 's')
            myMotor.Backward();
        else if (input == 'A'|| input == 'a')
            myMotor.Left();
        else if (input == 'Q'|| input == 'q')
            myMotor.MoreLeft();
        else if (input == 'D'|| input == 'd')
            myMotor.Right();
        else if (input == 'E'|| input == 'e')
            myMotor.MoreRight();
        else if (input == 'X'|| input == 'x')
            myMotor.FullStop();
        else if (input == 'Y'|| input == 'y')
            myMotor.PrintStatus();
        else if (input == 'R'|| input == 'r')
            myMotor.Accelerate();
        else if (input == 'F'|| input == 'f')
            myMotor.Brake();
        else if (input == 'm' || input == 'M') {
            readRemote.Read();
        }
        // GEARBOX
        else if (input == '1')
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
    
    if (inputString.toInt() > 0 && inputString.toInt() < 100) {  
        int motorSpeed = inputString.toInt();
        Serial.println(motorSpeed);
        myMotor.SetSpeedBoth(motorSpeed);
    }
}

void MainFunktions::RemoteControl() {
  if (!readRemote.IsReady()) {
#ifdef DEBUG
  Serial.println("REMOTE NOT READY");
#endif
    return;
  }

  readRemote.Read();
  transmission.SetGear(readRemote.Gear);
  if(readRemote.Turning != 0)
  {
      if (readRemote.Turning == 1)
          myMotor.Left(); 
      else if (readRemote.Turning == 2)
          myMotor.Right();

      myMotor.SetSpeedBoth(readRemote.Angle);
  }  
  else if (readRemote.Direction != 0)
  {
      if (readRemote.Direction == 1)
          myMotor.Backward();
      else if (readRemote.Direction == 2)
          myMotor.Forward();

      myMotor.SetSpeedBoth(readRemote.Speed);
  }
}
