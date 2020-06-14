#include <SPI.h>  
#include "RF24.h"  

RF24 myRadio (8, 10); 
int data;
int yPin = A1;



void setup() {
  Serial.begin(9600);
  delay(1000);
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.setDataRate( RF24_250KBPS ) ; 

  pinMode(yPin, INPUT);
}
void loop() {
  data = analogRead(yPin);
  myRadio.stopListening(); 
  myRadio.openWritingPipe( 0xF0F0F0F0AA); 
  myRadio.write(&data, sizeof(data)); 
  Serial.print("\nSent:");
  Serial.println(data);
}
 
