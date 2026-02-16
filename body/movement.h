#ifndef MOVEMENT_H
#define MOVEMENT_H
#pragma once

#include <Arduino.h>
#include "variable.h"

class movement {
  public:
    movement::movement();

    void stopArdumoto(byte motor);
    void stop();  
    void Forward(int speed);
    void turn(int rs, int ls);
    void Motor_FR(int motorSpeed);
    void Motor_FL(int motorSpeed);
    void Motor_BR(int motorSpeed);
    void Motor_BL(int motorSpeed);


  private:
    //#define FORWARD
    //#define REVERSE

};
#endif


