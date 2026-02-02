#ifndef ACTIONS_H
#define ACTIONS_H
enum Action {
  FORWARD = 0,
  BACKWARD,
  LEFT,
  RIGHT,
  STOP,
  ACTION_COUNT
};

struct AIBrain {
  float weight[ACTION_COUNT];
  int score[ACTION_COUNT];
};

void initBrain(AIBrain &brain);


#endif