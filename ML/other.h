

#ifndef OTHER_H
#define OTHER_H
#pragma once

#include "variables.h"

class other{ 
  public:
    int checkpoints(bool cp, int heading, const char* a, int turnAngle); 
    //void learning(AIBrain &ai, actions action, int reward);
    int scoring(bool collision, bool stuck, bool progress);

    
};
#endif