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
#include <SoftwareSerial.h>
//check the above library, it may be only for arduino uno

using namespace std;

movement m;
sensors s;

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

void loop(){
  unsigned long start = millis();

  /*
  input method or script that uses the inputs of the sensors
  and then sends them to the esp
  */


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
    
    m.Forward(100); //testing purposes

  }
  /*
  recieves information from the esp and 
    executes decisions that the esp created
  */

}




