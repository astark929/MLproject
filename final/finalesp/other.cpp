/*
may not need this
an object class that helps define the 
    relative distance of objects nearby the robot
*/

#include "other.h"


//AIBrain brain;  //main action file methods

int posX = 0;
int posY = 0;
int heading = 0;
int distance = 0;


int other::checkpoints(bool cp, int heading, const char* a, int turnAngle){
  if(cp){
    posX = 0;
    posY = 0;
  }
  else{
    if(a = "straight"){
      posX += distance * cos(heading);
      posY += distance * sin(heading);
    }
    else if(a = "turn"){
      heading += turnAngle;
    }
  }
  return posX;
}
/*
void updateLearning(int state, int action, float reward){

    float alpha = 0.1;

    brain.q[state][action] += alpha * reward;

    if(brain.q[state][action] < 0.01){
      brain.q[state][action] = 0.01;
    }

    if(brain.q[state][action] > 10){
        brain.q[state][action] = 10;
    }
}
*/
/*
Action thinking(AIBrain &ai){
  //exploreProbability = max(0.1, 1.0 - confidence);
  float totalWeight = 0;

  for (int i = 0; i < ACTION_COUNT; i++) {
    totalWeight += ai.weight[i];
  }

  float r = random(0, 10000) / 10000.0 * totalWeight;

  float cumulative = 0;
  for (int i = 0; i < ACTION_COUNT; i++) {
    cumulative += ai.weight[i];
    if (r <= cumulative) {
      return (Action)i;
    }
  }

  return STOP; // fallback
}
*/
/*
void learning(AIBrain &ai, actions action, int reward){
  const float learningRate = 0.1;

  ai.score[action] += reward;
  ai.weight[action] += learningRate * reward;

  // Prevent zero or negative probability
  if (ai.weight[action] < 0.01) {
    ai.weight[action] = 0.01;
  }
}*/


int scoring(bool collision, bool stuck, bool progress){
  if (collision) return -5;
  if (stuck) return -3;
  if (progress) return 2;
  return 1;
}

