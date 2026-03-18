unsigned long time;

void setup() {
  Serial.begin(115200);   // initialise serial monitor port
  Serial2.begin(115200);  // initialise Serial1
  Serial.write("Arduino Mega Serial1 test -  for loopback test connect pin 18 to pin 19\n");
}

void loop() {
  Serial2.write("rsomething else\n");
  if (Serial2.available()>0) {// read from Serial1 output to Serial
    Serial2.write("hello there\n");
    Serial.println("IT WORKEDD");
    Serial.println(Serial2.read());
  }       
    
  if (Serial.available()>0) {       // read from Serial outut to Serial1
    int inByte = Serial.read();
    //Serial.write(inByte);     // local echo if required
    Serial2.write(inByte);
    Serial.println("returning data type");
  }
  time1(3);
}

void time1(float i){
  delay(i * 1000);
}