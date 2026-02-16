#include "sensors.h"
#include <SoftwareSerial.h>

SoftwareSerial espSerial(10, 11); //initalizing ports to communicate with esp

using namespace std;


sensors::sensors(){
  pinMode(Trig_PIN, output); 
  pinMode(Echo_PIN,input);
  //ultra sonic

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  //line sensor

  espSerial.begin(115200);
  //espport = espSerial; //esp communication

}

float sensors::getdistance(){
  float time;
  float cd;

  digitalWrite(Trig_PIN, high);
  delayMicroseconds(10);
  digitalWrite(Trig_PIN, low);
  time = pulseIn(Trig_PIN, low);
  cd = time / 148.0; //calcs a distance in inch
  //cd = time / 58; // calcs a distance in cm
  return cd; //should return a value in inch
}

void sensors::line(){
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

bool sensors::espAvailable() {
    return espSerial.available();
}
int sensors::espRead() {
    return espSerial.read();
}
