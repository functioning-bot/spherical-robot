#include <Servo.h> 
#include <Wire.h> 
#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h> 

#define CE_PIN 1 
#define CSN_PIN 0 

const unit64_t pipe=0xE8E8F0F0E1LL; 
RF24 radio(CE_PIN, CSN_PIN); 
int joystick[2]; 

Servo servo_1; 
Servo servo_2; 

//mg996r servo motor initalizations 
int servo_1_pin=9; 
int servo_2_pin=10; 
int mapped_position; 
int d=2; 
int S_low=40; 
int S_mid=90; 
int S_high=140; 

//l298n motor driver initializations 
int enA = 6; 
int in1 = 4; 
int in2 = 3; 
int enB = 5; 
int in3 = 8; 
int in4 = 7; 
int mapped_value; 
int M_low=0; 
int M_high=255; 

//nrf24l01 variables initializations 
//motor speed and direction 
int JoystickLeft_var=512;               
//servo angle 
int JoystickRight_var=512;                    
int JS_low=0; 
int JS_mid=512; 
int JS_high=1023; 

void setup() 
{ 
  Wire.begin(); 
  Serial.begin(115200); 

  //mg996r setup 
  servo_1.attach(servo_1_pin); 
  servo_2.attach(servo_2_pin); 

  // l298 setup 
  pinMode(enA, OUTPUT); 
  pinMode(enB, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 

  initialize(); 
  radio.begin(); 
  radio.openReadingPipe(1,pipe); 
  radio.startListening(); 
  delay(2000); 
} 

void motion_front(int Left_var) 
{ 
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH);   
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
  mapped_value=map(Left_var,JS_mid,JS_high,M_low,M_high); 
  analogWrite(enA, mapped_value);  
  analogWrite(enB, mapped_value);  
  delay(20);  
} 

void motion_back(int Left_var) 
{ 
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW);   
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
  mapped_value=map(Left_var,JS_mid,JS_low,M_low,M_high); 
  analogWrite(enA, mapped_value);  
  analogWrite(enB, mapped_value);  
  delay(20);  
} 

void motor_motion_stop() 
{ 
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW);   
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW);  
} 

void motion_right(int Right_var) 
{ 
  mapped_position=map(Right_var,JS_mid,JS_high,S_mid,S_high); 
  servo_1.write(mapped_position); 
  servo_2.write(180-mapped_position);  
} 

void motion_left(int Right_var) 
{ 
  mapped_position=map(Right_var,JS_mid,JS_low,S_mid,S_low); 
  servo_1.write(mapped_position); 
  servo_2.write(180-mapped_position);   
} 

void servo_motion_stop() 
{ 
  servo_1.write(S_mid); 
  servo_2.write(S_mid); 
} 

void initialize() 
{ 
  int var; 
  for(var=JS_low;var<JS_high;var+=1) 
  { 
  } 
  if(var>514) 
  { 
    motion_right(var); 
    delay(d); 
  } 
  else if(var<510) 
  { 
    motion_left(var); 
    delay(d); 
  } 
  else  
  { 
    servo_motion_stop(); 
    delay(d); 
  }   

  for(var=JS_high;var>JS_low;var-=1) 
  { 
    if(var>514) 
    { 
      motion_right(var); 
      delay(d); 
    } 
    else if(var<510) 
    { 
      motion_left(var); 
      delay(d); 
    } 
    else  
    { 
      servo_motion_stop(); 
      delay(d); 
    } 
  } 

  for(var=JS_low;var<JS_mid;var+=1) 
  { 
    if(var>514) 
    { 
      motion_right(var); 
      delay(d); 
    } 
    else if(var<510) 
    { 
      motion_left(var); 
      delay(d); 
    } 
    else  
    { 
      servo_motion_stop(); 
      delay(d); 
    }     
  } 
} 

void servo_write(int t) 
{ 
  servo_1.write(t); 
  servo_2.write(180-t); 
  delay(5);   
} 

void servo_motion( int angle) 
{ 
  int curr,temp; 
  curr=servo_1.read(); 
  if (curr<angle) 
  { 
    for(temp=servo_1.read();temp<angle;temp++) 
      servo_write(temp); 
  } 
  if (curr>angle) 
  { 
    for(temp=servo_1.read();temp>angle;temp--) 
      servo_write(temp);           
  } 
} 

void servo_motion_right(int JoystickRight) 
{ 
  int desti=map(JoystickRight,JS_mid,JS_high,S_mid,S_high); 
  servo_motion(desti); 
} 

void servo_motion_left( int JoystickRight) 
{ 
  int desti=map(JoystickRight,JS_mid,JS_low,S_mid,S_low); 
  servo_motion(desti);   
} 

void loop() 
{      
  while(radio.available()) 
  { 
    radio.read(joystick,sizeof(joystick)); 
    JoystickRight_var=joystick[0]; 
    JoystickLeft_var=joystick[1]; 

    if(JoystickRight_var>514) 
      servo_motion_right(JoystickRight_var); 
    else if(JoystickRight_var<510) 
      servo_motion_left(JoystickRight_var); 
    else  
    { 
      servo_motion_stop(); 
      delay(5); 
    } 

    if(JoystickLeft_var>514) 
      motion_front(JoystickLeft_var); 
    else if(JoystickLeft_var<510) 
      motion_back(JoystickLeft_var); 
    else  
      motor_motion_stop(); 
  }  
}
