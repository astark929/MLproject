#include "enviorment.h"

SimResult simulateStep(int currentState, actions action) {

  SimResult result;

  switch(currentState) {

    case 0: // START
      if(action == FORWARD) {
        result.nextState = 1;
        result.reward = -1;
      } else {
        result.nextState = 0;
        result.reward = -5;
      }
      break;

    case 1: // INTERSECTION
      if(action == FORWARD) {
        result.nextState = 2;  // dead end
        result.reward = -100;
      }
      else if(action == RIGHT) {
        result.nextState = 3;  // goal
        result.reward = 100;
      }
      else {
        result.nextState = 0;
        result.reward = -1;
      }
      break;

    case 2: // DEAD END
      result.nextState = 1;
      result.reward = -10;
      break;

    case 3: // GOAL
      result.nextState = 0;
      result.reward = 0;
      break;
  }

  return result;
}