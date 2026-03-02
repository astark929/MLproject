/*
this file is specific for telling the AI 
    what actions it can take and outputs the actions
*/
#include "actions.h"
float weightsVal[3] = {0.33f, 0.33f, 0.33f};
actions options[3] = {FORWARD, RIGHT, LEFT};

void initBrain(AIBrain &brain) {

  brain.alpha = 0.1f;     // learning rate
  brain.g = 0.9f;     // future reward importance
  brain.epsilon = 0.2f;   // 20% exploration

  for (int s = 0; s < STATE_COUNT; s++) {
    for (int a = 0; a < ACTION_COUNT; a++) {
      brain.q[s][a] = 0.0f;
    }
  }
}

int encodedState(bool left, bool middle, bool right) {
  return (left << 2) | (middle << 1) | right;
}

actions chooseAction(AIBrain &brain, int state) {

  float r = random(0, 10000) / 10000.0f;

  // Exploration
  if (r < brain.epsilon) {
    return (actions)random(0, ACTION_COUNT);
  }

  // Exploitation (choose best action)
  int bestAction = 0;
  float bestValue = brain.q[state][0];

  for (int a = 1; a < ACTION_COUNT; a++) {
    if (brain.q[state][a] > bestValue) {
      bestValue = brain.q[state][a];
      bestAction = a;
    }
  }

  return (actions)bestAction;
}

void updateQ(AIBrain &brain, int state, actions action, float reward, int nextState) {

  // Find best next action value
  float maxNext = brain.q[nextState][0];
  for (int a = 1; a < ACTION_COUNT; a++) {
    if (brain.q[nextState][a] > maxNext) {
      maxNext = brain.q[nextState][a];
    }
  }

  // Q-learning update
  float oldValue = brain.q[state][action];

  brain.q[state][action] =
      oldValue +
      brain.alpha * (reward + brain.g * maxNext - oldValue);
}

void decayExploration(AIBrain &brain) {

  // Slowly reduce exploration over time
  if (brain.epsilon > 0.05f) {
    brain.epsilon *= 0.995f;
  }
}

float sumWeights(){
  float sum = 0;
  for(int i : weightsVal){
    sum += i;
  }
  return sum;
}

const char* output(actions a) {
  switch (a) {
    case FORWARD:  return "FORWARD";
    case LEFT:     return "LEFT";
    case RIGHT:    return "RIGHT";
    default:       return "STOP";
  }
}

actions choose(){
  uint16_t sum = weightsVal[0] + weightsVal[1] + weightsVal[2];
  uint16_t r = random(sum);
  if(r <= weightsVal[0]){
    return FORWARD;
  }
  else if(r <= weightsVal[0]+weightsVal[1]){
    return LEFT;
  }
  else{ //(weightsVal[0]+weightsVal[1] < r <= weightsVal[0]+weightsVal[1]+weightsVal[2]){
    return RIGHT;
  }
}
//code above is likely a dead code right now
//in other words, code that isnt being used anymore

actions choose(bool leftOpen, bool midOpen, bool rightOpen) {

    uint16_t temp[3];

    temp[FORWARD] = midOpen  ? weightsVal[FORWARD]  : 0;
    temp[LEFT]    = leftOpen ? weightsVal[LEFT]     : 0;
    temp[RIGHT]   = rightOpen? weightsVal[RIGHT]    : 0;
    /*
    above is the ternary operator
    basically its an if else statement, saying if true set
    set the temp forward placement to the forward placement in weightsVal,
    else its 0
    */
    if(leftOpen){
      temp[0] = temp[0] * .5;
    }
    if(midOpen){
      temp[0] = temp[1] * .5;
    }
    if(rightOpen){
      temp[0] = temp[3] * .5;
    }

    uint16_t sum = temp[0] + temp[1] + temp[2];

    uint16_t r = random(sum);

    if (r <= temp[FORWARD])
        return FORWARD;
    else if (r <= temp[FORWARD] + temp[LEFT])
        return LEFT;
    else
        return RIGHT;
}
//code above is likely a dead code right now
//in other words, code that isnt being used anymore
