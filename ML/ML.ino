/*
{
  this file is mainly for the whole thinking process of the AI
    how the AI thinks, by having weighted values for each actions it can perform
    then applies a random number to help decide the action it should take
    when the an action is performed, the AI will give itself a score based on the actions
    if performed well, higher score, if it didnt do well, low score.

  after each actions, the weighted values will change the weighted values 
    which affect the values of each actions.
    another way to change the values for each actions is the previous stored data 

  believe we are using the NodalMCU esp8266 12e

  rule of thumb:
  global ram: 
  < 60% → good
  60–75% → caution
  75% → crashes, resets, weird bugs

  IRAM usage	    Status
  < 70%	          Excellent (very stable)
  70–80%	        Good
  80–85%	        Caution
  85–90%	        Risky
  > 90%	          Crash-prone

  as of running this, we have:
  global used 39480 / 80192 bytes (49%)
  IRAM used 59223 / 65536 bytes (90%)
  flash used 403152 / 1048576 bytes (38%)

  esp needs 3.3V to run
}
*/
#include <ESP8266WiFi.h>

//personal library / threaded classes
#include "mem.h"
#include "other.h"
#include "states.h"

#include "actions.h"

#include "variables.h"

mem m;
states s;

int confidence = 0;

void setup(){
  randomSeed(analogRead(A0));
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  Serial.begin(115200);  //communication to arduino
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
/*
{
  for the loop in a circle
  robot checks
    if the robot made the same turn from the past 4 actions
    if the distance is the same from the past 4 actions
    checks the states of each action [0,1,0] ... etc
    skews or factors the states with the least amount of actions 
}
*/
void loop(){
  /*
  order for ai
  waits for response, does thinking, sends data
  */
  if (Serial.available() >= 2) { 
  //waits until the arduino sends information
    //String message = Serial.readStringUntil('>');

    byte packet1 = Serial.read();
    byte score   = Serial.read();

    bool left       = (packet1 >> 7) & 1;
    bool middle     = (packet1 >> 6) & 1;
    bool right      = (packet1 >> 5) & 1;
    bool checkpoint = (packet1 >> 4) & 1;

    if(left && middle && right){
      Serial.write("BACKWARDS");
    }
    else{
      srand(static_cast<unsigned int>(time(0)));
      Serial.write(output(choose(left, middle, right))); 
      //how it thinks ^
  }
  //the readstringuntil command will read charcater by character


}}

  //serial inputs
  //limit action method
  //line sensor (1 line = checkpoint; 2 lines = start; 3 lines = end);
  /*

  if(right == true && left == true && middle == true){
    brain.output(2); //backwards
  }
  if(right == true || left == true || middle == true){
    for(int i : action){
      if(i == 1){
        action[i] = action[i]*.5;
      }
    }
  }
  */
  //output(range(random(.01, sum())));
  



/*
void loop_test(){
  Action action = chooseAction(brain);

  // Arduino executes movement...

  int reward = scoreAction(collision, stuck, progress);
  updateBrain(brain, action, reward);

  maybeSaveBrain();

}
*/



/*
{
  inputs:
  states = binary numbers for objects; 0 for no objects, 1 for objects
  ex: [0,1,0] = [L, C, R] = object in the center
  score: the score it currently has 

  idea for learning: equation:
  new_value = old_value + learning_rate * (reward − old_value)
  putting it into theory code
  mem.cpp{
    int actionValue[state][action]; 
    //the state and action the robot is in rn and what actions it can take
  }
  main{
    action = chooseAction(state);
    //chooses an action based on the states (or paths avalible) 

    execute(action);
    int reward = getReward(); //from arduino

    actionValue[state][action] += alpha * (reward - actionValue[state][action]);

    
  }
  the idea of choice could be:
    if (random() < 0.1) explore();
    else pick highest value;



  may need to use this?
  const char* output(Action a) {
    switch (a) {
      case FORWARD: return "FORWARD";
      case BACKWARD: return "BACKWARD";
      case LEFT: return "LEFT";
      case RIGHT: return "RIGHT";
      case STOP: return "STOP";
    }
    return "STOP";
  }

  avoid IRAM_ATTR:: such as :
  void IRAM_ATTR myFunc() { ... }
  to lower the IRAM

  may need this for input? unsure:
  static char buffer[64];
  int len = Serial.readBytesUntil('\n', buffer, sizeof(buffer) - 1);
  buffer[len] = '\0';
}
*/
bool readPacket(Packet &p) {
  if (Serial.available() >= 2) {
    byte header = Serial.read();
    p.reward = Serial.read();

    p.left       = (header >> 7) & 1;
    p.middle     = (header >> 6) & 1;
    p.right      = (header >> 5) & 1;
    p.checkpoint = (header >> 4) & 1;

    return true;
  }
  return false;
}
