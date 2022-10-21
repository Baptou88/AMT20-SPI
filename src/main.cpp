#include <Arduino.h>

#include <AMT203-v.h>

AMT203V amt(SCK,MISO,MOSI,10);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //SPI.begin();
  while (!amt.begin())
  {
    Serial.println("Init failed");
    delay(500);
  }
  Serial.println("Init success");
  
}

void loop() {
  
  Serial.println(amt.getPos());
  delay(100);
  
  if (Serial.available())
  {
    if (Serial.read()=='r')
    {
      amt.reset();
      Serial.println("reset");
    }
    
  }
  
}