#pragma once

//arduino or imported library
#include <Arduino.h>
#include <EloquentTinyML.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <iostream>
#include <random>
#include <limits>
#include <cstdlib>
#include <ctime>

//personal library


extern int posX;
extern int posY;
extern int heading;

extern int distance;

struct Packet {
  bool left;
  bool middle;
  bool right;
  bool checkpoint;
  uint8_t reward;
};