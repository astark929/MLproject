#ifndef SENSORS_H
#define SENSORS_H
#pragma once

#include "variable.h"

extern SoftwareSerial espSerial;

class sensors {
  public:
    sensors::sensors();
    float getdistance();
    void line();
    bool espAvailable();
    int espRead();
    void Sangle(int a);
    bool lidar_left();
    void lidar_right();
    String lidar_detect();
    
  private:
    //SoftwareSerial espSerial(10, 11); //initalizing ports to communicate with esp
};

#endif