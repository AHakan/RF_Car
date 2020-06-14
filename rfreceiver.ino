#include <SPI.h>
#include <RF24.h>

RF24 myRadio (8, 10);

int data;
int enginePin = 3;

void setup() 
{
  Serial.begin(9600);
  delay(1000);
  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.setDataRate( RF24_250KBPS ) ;

  pinMode(enginePin, OUTPUT);
}
void loop() {
  myRadio.openReadingPipe(1, 0xF0F0F0F0AA); 
  myRadio.startListening(); 
  if ( myRadio.available()) 
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
    }
  }
  Serial.print("Data: ");
  Serial.println(data);
  speedfunc(data);
  delay(300);

  
}

void speedfunc(int data){
  if(data>550){
    int Speed=map(data, 550, 1023, 0, 255);
    analogWrite(enginePin, Speed);
    Serial.print("Speed: ");
    Serial.println(Speed);
  }
  else{
    analogWrite(enginePin, 0);
  }
}
