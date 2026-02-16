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
#include "movement.h"
#include <SoftwareSerial.h>
//check the above library, it may be only for arduino uno

using namespace std;

SoftwareSerial espSerial(10, 11); //initalizing ports to communicate with esp
movement m;

void setup(){
  //motor_start();
  sensor_start();
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
  espSerial.begin(115200); //esp communication

}

void loop(){
  unsigned long start = millis();

  /*
  input method or script that uses the inputs of the sensors
  and then sends them to the esp
  */


  while(!espSerial.available()){
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
/*
void motor_start(){
  pinMode(RightMotorDirPin1, output); 
  pinMode(RightMotorDirPin2, output); 
  pinMode(speedPinL, output);  
 
  pinMode(LeftMotorDirPin1, output);
  pinMode(LeftMotorDirPin2, output); 
  pinMode(speedPinR, output);
  pinMode(RightMotorDirPin1B, output); 
  pinMode(RightMotorDirPin2B, output); 
  pinMode(speedPinLB, output);  
 
  pinMode(LeftMotorDirPin1B, output);
  pinMode(LeftMotorDirPin2B, output); 
  pinMode(speedPinRB, output);
}
*/
void sensor_start(){
  pinMode(Trig_PIN, output); 
  pinMode(Echo_PIN,input);
  //ultra sonic

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  //line detector

}

void line(){
  String senstr="";
  int linecount = 0;
  int s0 = !digitalRead(sensor1);
  int s1 = !digitalRead(sensor2);
  int s2 = !digitalRead(sensor3);
  int s3 = !digitalRead(sensor4);
  int s4 = !digitalRead(sensor5);
  int sensorvalue=32;
  sensorvalue +=s0*16+s1*8+s2*4+s3*2+s4;
  senstr = String(sensorvalue,BIN);
  senstr = senstr.substring(1,6);
  
  /*
  Serial.print(senstr);
  Serial.print("\t");
  these are debugger statements right now
  */

  for(int count: senstr){
    if(count == '1'){
      linecount++;
    }
  }
  if(linecount == 1){
    espSerial.print("1 line");
  }
  else if(linecount == 2){
    espSerial.print("2 line");
  }
  else if(linecount == 3){
    espSerial.print("3 line");
  }
  else{
    espSerial.print("0 line");
  }

}
//for the line sensing



