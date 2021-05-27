/*
NAME: Harikrishnan Bejishkumar
SUBJECT: Automatic bottling machine 
This program is C program that gives an idea about how the conveyor system works. The design specifications are not met at the time of 
structuring this code.The main parts in the design are the following: */

#include<Arduino.h>

#include <Stepper.h>
#include <Q2HX711.h>

boolean systemstate;

uint8_t s1state; 
uint8_t s2state; 
uint8_t s3state; 
uint8_t s4state; 

uint8_t s1count = 0;
uint8_t s3count = 0;
uint8_t s2count = 0;
uint8_t product = 0;
uint8_t s4count = 0;

//MOTOR PINS INITIALIZED
const int m1 = 3;
const int m2 = 5;//enable pin from l298n for speed control, in1 and in2 is short to vcc and gnd for clockwise spin
const int m3 = 6;
const int m5 = 9;


//INPUTS FROM OTHER ARDUINO
const int SYSTEM = 1;//system on pin

const int s1 = 2;//sensor 1
const int s2 = 4;//sensor 2
const int s3 = 10;//sensor 3
const int s4 = 11;//sensor 4

//A0 is sensor 5(Checkweigher sensor) pin.

Stepper Rejectarm(200, 7, 8, 12, 13);
uint8_t calibration = 100;

const byte adc_data = 10; // Load cell data 
const byte adc_clk = 11;//Load cell clock

Q2HX711 hx711(adc_data, adc_clk);

void setup() {
  Serial.begin(9600);//SERIAL CONNECTION IS SET
  //OUTPUT PINS(motors)  
  pinMode( m1, OUTPUT);
  pinMode( m2, OUTPUT);
  pinMode( m3, OUTPUT);//WEIGHT CONVEYOR
  pinMode( m5, OUTPUT);

  //INPUT PINS FROM OTHER ARDUINO
  pinMode(SYSTEM, INPUT);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(A0,INPUT);//checkweigher sensor
}

void loop() {
 
  systemstate = digitalRead(SYSTEM);
  s1state = digitalRead(s1);
  
  
  
  
  
  while(systemstate){
    s4state = digitalRead(s4);
    if(s4state == HIGH){
    s4count++;
   }
    sensor2();
    sensor3();
    qc();
    
    digitalWrite(m2, HIGH);
    digitalWrite(m5, HIGH);  
      
   if(s1count > s2count || ((s1count == s2count) &&(s3count < s2count)) ||s1count == 1){
    product ++;
    digitalWrite(m1, HIGH);
    }
    else{
      digitalWrite(m1,LOW);
    }
    
  }
  
}
void sensor2(){
  s2state = digitalRead(s2);
  if(s2state == HIGH){
    s2count++;
  }
}

void sensor3(){
  s3state = digitalRead(s3);
  if(s3state == HIGH){
    s3count++ ;// A product has gone through
  }
  
}

void qc(){
  int i = 0;
  uint16_t weight = 0;
  uint32_t current= millis();
  uint32_t previous = 0;
  
  if(s3count > s4count && analogRead(A0) > 255){
    while((current - previous) > 50){
      previous = current;
      digitalWrite(m3, LOW);
      weight = (hx711.read()/calibration);
    } 
    digitalWrite(m3, HIGH);
    current = millis();
    previous = 0;
    
  }
  if(5 < weight < 1){
    Rejectarm.setSpeed(100);
    Rejectarm.step(25);
    while((current - previous) > 200){
      previous = current;
      
    } 
     Rejectarm.step(-25);
  }
  
  
}