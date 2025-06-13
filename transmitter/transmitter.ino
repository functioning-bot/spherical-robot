#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h> 

#define inX A0 
#define inY A1  

#define CE_PIN  7 
#define CSN_PIN 8  

const uint64_t pipe = 0xE8E8F0F0E1LL; // This is the transmit pipe to communicate the two module  

RF24 radio(CE_PIN, CSN_PIN); // Activate the Radio

// Two element array holding the Joystick readings 
int joystick[2]; 

void setup()    
{   
  Serial.begin(9600); // Opening the Serial Communication 
  radio.begin(); 
  radio.openWritingPipe(pipe); 
} 

void loop()  
{ 
  joystick[0] = analogRead(inX);  
  joystick[1] = analogRead(inY);  
  radio.write(joystick, sizeof(joystick)); 
  delay(1000); 
}
