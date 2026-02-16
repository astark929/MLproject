#ifndef SENSORS_H
#define SENSORS_H
#pragma once

#include <Arduino.h>
#include <Servo.h>
#include "variable.h"
#include <SoftwareSerial.h>

extern SoftwareSerial espSerial;

class sensors {
  public:
    sensors::sensors();
    float getdistance();
    void line();
    bool espAvailable();
    int espRead();
    
  private:
    //SoftwareSerial espSerial(10, 11); //initalizing ports to communicate with esp
};

#endif
