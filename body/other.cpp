#include "other.h"

using namespace std; 

other::other(){
  pinMode(red, output);
  pinMode(blue, output);
  pinMode(green, output);
}

void other::lightup(char s, int v){
  switch(s){
    case 'r':
      analogWrite(red, v);
      analogWrite(green, 0);
      analogWrite(blue, 0);
      break;

    case 'b':
      analogWrite(red, 0);
      analogWrite(green, 0);
      analogWrite(blue, v);
      break;

    case 'g':
      analogWrite(red, 0);
      analogWrite(green, v);
      analogWrite(blue, 0);
      break;
    
    default:
      analogWrite(red, 0);
      analogWrite(green, 0);
      analogWrite(blue, 0);
      break;
  }
}