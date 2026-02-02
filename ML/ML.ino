/*
this file is mainly for the whole thinking process of the AI
  how the AI thinks, by having weighted values for each actions it can perform
  then applies a random number to help decide the action it should take
  when the an action is performed, the AI will give itself a score based on the actions
  if performed well, higher score, if it didnt do well, low score.

after each actions, the weighted values will change the weighted values 
  which affect the values of each actions.
  another way to change the values for each actions is the previous stored data 

believe we are using the NodalMCU esp8266 12e
*/
#include <Arduino.h>
#include <EloquentTinyML.h>
#include "mem.h"
#include "actions.h"
#include <EEPROM.h>

AIBrain brain;
int confidence = 0;

void setup(){

}
/*
void setup_test() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);

  if (!memoryExists()) {
    Serial.println("No AI memory found. Initializing...");
    initBrain(brain);
    saveBrain(brain);
    markMemoryValid();
  } else {
    Serial.println("AI memory loaded.");
    loadBrain(brain);
  }
}
*/

void loop(){
  
}

/*
void loop_test(){
  Action action = chooseAction(brain);

  // Arduino executes movement...

  int reward = scoreAction(collision, stuck, progress);
  updateBrain(brain, action, reward);

  maybeSaveBrain();

}
*/

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


void learning(AIBrain &ai, Action action, int reward){
  const float learningRate = 0.1;

  ai.score[action] += reward;
  ai.weight[action] += learningRate * reward;

  // Prevent zero or negative probability
  if (ai.weight[action] < 0.01) {
    ai.weight[action] = 0.01;
  }
}


int scoring(bool collision, bool stuck, bool progress){
  if (collision) return -5;
  if (stuck) return -3;
  if (progress) return 2;
  return 1;
}

String output(Action a) {
  switch (a) {
    case FORWARD: return "FORWARD";
    case BACKWARD: return "BACKWARD";
    case LEFT: return "LEFT";
    case RIGHT: return "RIGHT";
    case STOP: return "STOP";
  }
  return "STOP";
}
