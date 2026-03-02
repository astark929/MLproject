#ifndef MEM_H
#define MEM_H
#pragma once

#include "variables.h"


class mem {
  public:
    void initMemory();
    bool memoryExists();

    //void saveBrain(const AIBrain &brain);
    //void loadBrain(AIBrain &brain);
    void initQ();
    //actions chooseAction(int state);
    //void updateQ(int state, actions action, float reward, int nextState);
  private: 
    //float Q[STATE_COUNT][ACTION_COUNT];
    //float alpha;
    //float g;
};


#endif
