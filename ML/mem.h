#ifndef MEM_H
#define MEM_H
#pragma once

#include <EEPROM.h>
#include <Arduino.h>
#include "actions.h"

void initMemory();
bool memoryExists();

void saveBrain(const AIBrain &brain);
void loadBrain(AIBrain &brain);

#endif
