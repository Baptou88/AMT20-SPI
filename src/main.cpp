#include <Arduino.h>

#include <AMT203-v.h>
#define ENC_CS 23
AMT203V amt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  
  while (!amt.begin(SCK,MISO,MOSI,10))
  {
    Serial.println("Init failed");
    delay(500);
  }
  Serial.println("Init success");
  
}

void loop() {
  
  Serial.println(amt.getPos());
  delay(1000);
  
}