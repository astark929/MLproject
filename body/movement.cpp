#include "movement.h"

#define forward 0
#define reverse 1

using namespace std;

movement::movement()
{
  pinMode(RightMotorDirPin1, output); 
  pinMode(RightMotorDirPin2, output); 
  pinMode(speedPinL, output);  
 
  pinMode(LeftMotorDirPin1, output);
  pinMode(LeftMotorDirPin2, output); 
  pinMode(speedPinR, output);

  pinMode(RightMotorDirPin1B, output); 
  pinMode(RightMotorDirPin2B, output); 
  pinMode(speedPinLB, output);  
 
  pinMode(LeftMotorDirPin1B, output);
  pinMode(LeftMotorDirPin2B, output); 
  pinMode(speedPinRB, output);
}


// stopArdumoto makes a motor stop
void movement::stopArdumoto(byte motor)
{
  digitalWrite(RightMotorDirPin1, forward); 
  digitalWrite(RightMotorDirPin2, forward); 
 
  digitalWrite(LeftMotorDirPin1, forward);
  digitalWrite(LeftMotorDirPin2, forward); 

  digitalWrite(RightMotorDirPin1B, forward); 
  digitalWrite(RightMotorDirPin2B, forward); 
 
  digitalWrite(LeftMotorDirPin1B, forward);
  digitalWrite(LeftMotorDirPin2B, forward);

  analogWrite(speedPinR, 0);
  analogWrite(speedPinL, 0);
  analogWrite(speedPinRB, 0);
  analogWrite(speedPinLB, 0);
  
}

void movement::stop(){
  Motor_FR(0);
  Motor_FL(0);
  Motor_BR(0);
  Motor_BL(0);

}

void movement::Forward(int speed){
  Motor_FR(speed);
  Motor_FL(speed);
  Motor_BR(speed);
  Motor_BL(speed);
}

void movement::turn(int rs, int ls){
  Motor_FR(rs);
  Motor_FL(ls);
  Motor_BR(rs);
  Motor_BL(ls);
}

void movement::Motor_FR(int motorSpeed)                          //function for driving Motor_A
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(RightMotorDirPin1, forward);                      //set pin 2 to high or FORWARD
  }
  else if (motorSpeed < 0)                            //if the motor should drive backwar (negative speed)
  {
    digitalWrite(RightMotorDirPin1, reverse);                      //set pin 1 to low or REVERSE
  }
  else                                                //if the motor should stop
  {
    digitalWrite(RightMotorDirPin1, 0);
    analogWrite(speedPinR, 0);
   }
  analogWrite(speedPinR, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered Joystick speed
}

void movement::Motor_FL(int motorSpeed)                           //function for driving the Motor_B
{
  if (motorSpeed > 0)                                  //if the motor should drive forward (positive speed)
  {
    digitalWrite(LeftMotorDirPin1, forward);                       //set pin 1 to high
  }
  else if (motorSpeed < 0)                             //if the motor should drive backward (negative speed)
  {
    digitalWrite(LeftMotorDirPin1, reverse);                       //set pin 1 to low
  }
  else                                                //STOP Motor_B
  {
    digitalWrite(LeftMotorDirPin1, 0);                              // STOP motor_B
    analogWrite(speedPinL, 0);
  }
  analogWrite(speedPinL, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered Joystick speed

}
void movement::Motor_BR(int motorSpeed)                           //function for driving the Motor_B
{
  if (motorSpeed > 0)                                  //if the motor should drive forward (positive speed)
  {
    digitalWrite(RightMotorDirPin1B, forward);                       //set pin 1 to high
  }
  else if (motorSpeed < 0)                             //if the motor should drive backward (negative speed)
  {
    digitalWrite(RightMotorDirPin1B, reverse);                       //set pin 1 to low
  }
  else                                                //STOP Motor_B
  {
    digitalWrite(RightMotorDirPin1B, 0);                              // STOP motor_B
    analogWrite(speedPinRB, 0);
  }
  analogWrite(speedPinRB, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered Joystick speed

}

void movement::Motor_BL(int motorSpeed)                           //function for driving the Motor_B
{
  if (motorSpeed > 0)                                  //if the motor should drive forward (positive speed)
  {
    digitalWrite(LeftMotorDirPin1B, forward);                       //set pin 1 to high
  }
  else if (motorSpeed < 0)                             //if the motor should drive backward (negative speed)
  {
    digitalWrite(LeftMotorDirPin1B, reverse);                       //set pin 1 to low
  }
  else                                                //STOP Motor_B
  {
    digitalWrite(LeftMotorDirPin1B, 0);                              // STOP motor_B
    analogWrite(speedPinLB, 0);
  }
  analogWrite(speedPinLB, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered Joystick speed

}
