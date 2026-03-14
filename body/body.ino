/*
this is going to be the main body of the AI
the point of the body should be:
- take in information from the sensors
- communicate with the brain (the ai)
- executes the actions the AI wants to do
- should be able to move forward, backwards, left, right, stop
- (potential) may need a wifi module to stream the data 
  to an external source (a laptop)

*/

#include "variable.h"
#include "sensors.h"
#include "movement.h"
//check the above library, it may be only for arduino uno

using namespace std;

movement m;
sensors s;

int left, middle, right = 0;

void setup(){
  /*
  esp ports 10 and 11 
  10 -> esp TX    recieves info
  11 -> esp RX    takes info
  use espSerial.print to have the esp communicate with arduino
    and vise versa
  also you can use ports 1 and 0 to communicate with the esp;
    however, it's not ideal because its typically reserverd for
    another kind of communication
  
  */
  Serial.begin(9600); //communicating with USB for debugging

}

void loopa(){
  /*
  order for arduino
  detects new inputs -> waits for esp response -> 
  -> executes response -> sends new data 
  */
  unsigned long start = millis();

  /*
  input method or script that uses the inputs of the sensors
  and then sends them to the esp
  */
  left, middle, right = 0;

  s.Sangle(135);
  if(s.getdistance() > 7.5){  //put it greather than a length to help it determine the distance to check to see if there is an object
    left = 1;
  }
  s.Sangle(90);
  if(s.getdistance() > 7.5){ 
    middle = 1;
  }
  s.Sangle(45);
  if(s.getdistance() > 7.5){ 
    right = 1;
  }

  int score, left, middle, right, checkpoint = 0;

  byte packet1 = 0;

  packet1 |= (left << 7);
  packet1 |= (middle << 6);
  packet1 |= (right << 5);
  packet1 |= (checkpoint << 4);

  Serial.write(packet1);
  Serial.write(score);

  while(!s.espAvailable()){
    //waits for esp response
    //the while statement will skip once there is data
    //  for the esp
    if (millis() - start > 100) {
        // timeout after 100ms
        break;
    }
    //if the arduino does not respond after a certain amount of time, 
    //it escapes the loop

  }
  /*
  recieves information from the esp and 
    executes decisions that the esp created
  */
  if(s.espAvailable() > 0){
    char command = s.espRead();     // read one byte
    executeAction(command);       // run movement
  }

}

void loop(){
  executeAction('f');
  Serial.println("forward");
  time(2);

  executeAction('b');
  Serial.println("backwards");
  time(2);

  executeAction('l');
  Serial.println("left");
  time(1.75);

  executeAction('r');
  Serial.println("right");
  time(1.75);
  
  executeAction('s');
  Serial.println("stopping");
  time(2);
}


void executeAction(char a) {
    switch(a) {
        case 'f': m.Forward(100); break;
        case 'l': m.turn(-100, 100); break;
        case 'r': m.turn(100, -100); break;
        case 'b': m.Forward(-100); break;
        case 's': m.stop(); break; 
    }
}

void time(float t){
  delay((unsigned long)(t*1000));
}
