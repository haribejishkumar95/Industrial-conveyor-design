#include<Arduino.h>

boolean START; //START BUTTON
boolean ESTOP;


//MAIN SWITCHES INTIALIZED
const int start = 0;
const int estop = 1;

//Pins of IR sensor 
#define s1 2
#define s2 3
#define s3 4
#define s4 5


//Pins for communication with other arduino
#define s1out 6
#define s2out 7
#define s3out 8
#define s4out 9



#define SYSTEM 13// HIGH = SYSTEM ON



 


void setup() {
  //INPUT PINS(sensors and buttons) 
  pinMode(start, INPUT);
  pinMode(estop, INPUT);
  pinMode(SYSTEM, OUTPUT);

  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  pinMode(s3,INPUT);
  pinMode(s4,INPUT);
  

  pinMode(s1out, OUTPUT);
  pinMode(s2out, OUTPUT);
  pinMode(s3out, OUTPUT);
  pinMode(s4out, OUTPUT);
}

void loop() {
  START = digitalRead(start);
  ESTOP = digitalRead(estop);
  if(START == HIGH && ESTOP == LOW){

    digitalWrite(SYSTEM, HIGH);
    
    
  }
  if(digitalRead(s1) == HIGH){
    digitalWrite(s1out, HIGH);
  }
  else{
    digitalWrite(s1out,LOW);
  }
  
  if(digitalRead(s2) == HIGH){
    digitalWrite(s2out, HIGH);
  }
  else{
    digitalWrite(s2out,LOW);
  }

  if(digitalRead(s3) == HIGH){
    digitalWrite(s3out, HIGH);
  }
  else{
    digitalWrite(s3out,LOW);
  }

  if(digitalRead(s4) == HIGH){
    digitalWrite(s4out, HIGH);
  }
  else{
    digitalWrite(s4out,LOW);
  }

  
}