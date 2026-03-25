#ifndef ENVIORMENT_H
#define ENVIORMENT_H

#include "actions.h"

struct SimResult {
  int nextState;
  float reward;
};

SimResult simulateStep(int currentState, actions action);

#endif