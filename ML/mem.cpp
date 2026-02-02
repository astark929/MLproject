
/*
this file is meant to create a file

reads a file and uses the contents inside of it

updates the file based on the data actions the AI decides  
    and the weighted values that influences the AI's decision
    and the data the AI recieves

ensure that there is a way the AI is able to read specific parts of the file
    that it can distinguish, so it can see what worked 
    and what didnt work based on the obstacles presented
*/
#include "mem.h"
#include <EEPROM.h>

#define EEPROM_SIZE 128
#define BRAIN_ADDR  0
#define MAGIC_ADDR  100
#define MAGIC_VALUE 0x42

void initMemory() {
  EEPROM.begin(EEPROM_SIZE);
}
//initially creates a storage for memory

bool memoryExists() {
  return EEPROM.read(MAGIC_ADDR) == MAGIC_VALUE;
}

void saveBrain(const AIBrain &brain) {
  EEPROM.put(BRAIN_ADDR, brain);
  EEPROM.write(MAGIC_ADDR, MAGIC_VALUE);
  EEPROM.commit();
}
/*
saves the actions the ai did into a memory storage
try to use this periotically and/or 
only when used when the AI is going to turn off
*/

void maybeSaveBrain(AIBrain &brain) {
  static unsigned long lastSave = 0;

  if (millis() - lastSave > 10000) {
    saveBrain(brain);
    lastSave = millis();
  }
}
//periotically saves the memory

void loadBrain(AIBrain &brain) {
  EEPROM.get(BRAIN_ADDR, brain);
}
// loads the memory to read

void clearMemory() {
  EEPROM.write(MAGIC_ADDR, 0x00);  // invalidate memory
  EEPROM.commit();
}
//helps clear out the memory of the ai

void wipeEEPROM() {
  for (int i = 0; i < EEPROM_SIZE; i++) {
    EEPROM.write(i, 0xFF);
  }
  EEPROM.commit();
}
// only use when the ai cannot wipe the memory correctly

/*
IMPORTANT NOTE
the memory for the ai converts the data into a non volatile memory, EEPROM, the flash drive,
converting the data into a byte array

when turning off and back on retains memory

when updating code, the memory does not typically get deleted
*/

/*
theoretical example on how to save
save periotically or when shutdown

unsigned long lastSave = 0;

void maybeSaveBrain() {
  if (millis() - lastSave > 10000) { // every 10s
    saveBrain(brain);
    lastSave = millis();
  }
}

*/

/*
determining the memory size of the esp
sizeof(AIBrain)
---------------------------------------------
#define MAX_EXPERIENCES 20

struct Experience {
  Action action;
  int reward;
};

struct Memory {
  Experience history[MAX_EXPERIENCES];
  int index;
};
---------------------------------------------
struct ActionStats {
  int timesChosen;
  int totalReward;
};

struct Brain {
  ActionStats stats[ACTION_COUNT];
};

*/
