#ifndef ACTIONS_H
#define ACTIONS_H

#include "variables.h"

#pragma once

#define STATE_COUNT 8        // 3 obstacle bits = 8 states
#define ACTION_COUNT 3       // FORWARD, BACKWARD, LEFT, RIGHT, STOP

enum actions : uint8_t {
  FORWARD = 0,
  RIGHT,
  LEFT
};

extern float weightsVal[3];
extern actions options[3];

/*
bindary version of actions
00 = forward
01 = right
00 = left
11 = backwards
*/

struct AIBrain {
  int16_t weight[ACTION_COUNT];
  int score[ACTION_COUNT];
  int16_t q[STATE_COUNT][ACTION_COUNT];
  int alpha;   // learning rate
  int g;   // discount factor
  int epsilon; // exploration rate
};

    void initBrain(AIBrain &brain);
    int encodedState(bool left, bool middle, bool right);
    actions chooseAction(AIBrain &brain, int state);
    actions choose(bool leftOpen, bool midOpen, bool rightOpen);
    void updateQ(AIBrain &brain, int state, actions action, float reward, int nextState);
    void decayExploration(AIBrain &brain);
    char output(actions a);
    float sumWeights();
    actions choose();


#endif