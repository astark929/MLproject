/*
this file is specific for telling the AI 
    what actions it can take and outputs the actions
*/
#include <iostream>
#include "actions.h"
using namespace std;


void initBrain(AIBrain &brain) {
  for (int i = 0; i < ACTION_COUNT; i++) {
    brain.weight[i] = 1.0;   // equal preference (may need to do 1.0f)
    brain.score[i] = 0;
  }
}