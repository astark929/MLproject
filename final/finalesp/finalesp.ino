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
AIBrain brain;
SoftwareSerial swSer(14, 12); 

int confidence = 0;
int lastState = -1;
actions lastAction;
bool hasLast = false;

void setup(){
  randomSeed(analogRead(A0));
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  Serial.begin(115200);  //communication to arduino
  swSer.begin(115200); //communication to esp    

  initBrain(brain);
}

void loop(){
  /*
  order for ai
  waits for response, does thinking, sends data
  */
  if (swSer.available() >= 2) { 
  //waits until the arduino sends information
    //String message = Serial.readStringUntil('>');

    byte packet1 = swSer.read(); 
    float reward = (float)((int8_t)swSer.read());
    Serial.println(reward);   

    bool left       = (packet1 >> 7) & 1;
    bool middle     = (packet1 >> 6) & 1;
    bool right      = (packet1 >> 5) & 1;
    bool checkpoint = (packet1 >> 4) & 1;

    int currentState = encodedState(left, middle, right);

    if (hasLast) {
      updateQ(brain, lastState, lastAction, reward, currentState);
      decayExploration(brain);
    }

    
    actions action = chooseAction(brain, currentState);
    swSer.write(output(action));
    Serial.println(output(action));
    //creates a decision, then sends it to the arduino

    // Store for next iteration
    lastState = currentState;
    lastAction = action;
    hasLast = true;

  }
  Serial.println("Communication with ESP failed");
}

/*
      srand(static_cast<unsigned int>(time(0)));
      Serial.write(output(choose(left, middle, right))); 
      //how it originally thinks  
*/

bool readPacket(Packet &p) {
  if (swSer.available() >= 2) {
    byte header = swSer.read();
    p.reward = swSer.read();

    p.left       = (header >> 7) & 1;
    p.middle     = (header >> 6) & 1;
    p.right      = (header >> 5) & 1;
    p.checkpoint = (header >> 4) & 1;

    return true;
  }
  return false;
}

