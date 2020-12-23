#include <Arduino.h>
#include <MainFunktions.h>

#define BUTTON_RESET    9

#define PIN_RADIO_CE    22  // A3
#define PIN_RADIO_CSN   10

MainFunktions mainFunc;

int cnt = 0;

void setup() {
  Serial.begin(9600);
}

//Repeat execution
void loop() {
  if (Serial.available())
  {
    mainFunc.ReadSerial();
  }
}

void MainFunktions::ReadSerial()
{
  String inputString = Serial.readString();
  handleKeyPress(inputString);           
}

void MainFunktions::handleKeyPress(String inputString)
{
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
        // // GEARBOX
        // else if (input == '1')
        //     gearbox.SetGear(1);
        // else if (input == '2')
        //     gearbox.SetGear(2);
        // else if (input == '3')
        //     gearbox.SetGear(3);
        // else if (input == '+')
        //     gearbox.ShiftUp();
        // else if (input == '-')
        //     gearbox.ShiftDown();
    }
    
    if (inputString.toInt() > 0 && inputString.toInt() < 100) {  
        int motorSpeed = inputString.toInt();
        Serial.println(motorSpeed);
        // myMotor.SetSpeedBoth(motorSpeed);
    }
}
