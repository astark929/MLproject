#ifndef STATES_H
#define STATES_H

#include "variables.h"

#define STATE_COUNT 8   // 2^3 sensor combinations
class states{
  public:
    int encodeState(bool left, bool middle, bool right);
};

#endif