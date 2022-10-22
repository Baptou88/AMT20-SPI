#include <Arduino.h>

#include <AMT203-v.h>


AMT203V amt(SCK,MISO,MOSI,AMT_CS); //check platformio.ini file to see where is define AMT_CS


void setup() {
  // put your setup code here, to run once:
  delay(100);
  Serial.begin(115200);

  pinMode(18, OUTPUT);
  digitalWrite(18,HIGH);

  
  //SPI.begin();
  
  Serial.println("CS pins: " + (String)AMT_CS);
  while (!amt.begin())
  {
    Serial.println("Init failed");
    delay(500);
  }
  Serial.println("Init success");
  
}

void loop() {
  
  int16_t value = amt.getPos();
  if (value == -1)
  {
    Serial.write("Error obtaining position.\n");
     Serial.write("Reset Arduino to restart program.\n");
  } else {
    Serial.println("pos: " + String(value));
  }
  
  delay(100);
  
  if (Serial.available())
  {
    if (Serial.read()=='r')
    {
      amt.reset();
      Serial.println("reset");
    }
    
  }
  delay(100);
}