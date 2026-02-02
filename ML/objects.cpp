/*
may not need this
an object class that helps define the 
    relative distance of objects nearby the robot
*/

enum DistanceState { FAR, MID, CLOSE };

struct StateKey {
  DistanceState front;
  DistanceState left;
  DistanceState right;
};

struct BrainCell {
  StateKey state;
  float weight[5];
  int score[5];
};
