#include <Servo.h>

#define LEFTPIN 2
#define RIGHTPIN 4
#define FORWARDPIN 7
#define BACKWARDPIN 8

Servo ESC;
Servo Tail;

bool leftState, rightState, forwardState, backwardState;
int Speed = 40;
int tailPos = 0;
int Trim = 30;
int tail = 95;

void setup() {

  Serial.begin(9600);
  
  pinMode(LEFTPIN, INPUT);
  pinMode(RIGHTPIN, INPUT);
  pinMode(FORWARDPIN, INPUT);
  pinMode(BACKWARDPIN, INPUT);
  
  ESC.attach(3,1000,2000);
  Tail.attach(5);
 
  
}

void loop() {

  readVals();
  conditions();
  printVals();
  
}



void readVals(){
  leftState = digitalRead(LEFTPIN);
  rightState = digitalRead(RIGHTPIN);
  forwardState = digitalRead(FORWARDPIN);
  backwardState = digitalRead(BACKWARDPIN);
}


void conditions(){
  
  if(forwardState==1){
    Speed = (Speed > 180) ? 180 : Speed+=4;}
  else if(backwardState==1){
    Speed = (Speed < 0) ? 0 : Speed-=20;}
  else{
    Speed = (Speed < 0) ? 0 : Speed-=5;}

  if(leftState==1){
    tailPos = 90-Trim;}
  else if(rightState==1){
    tailPos = 90+Trim;}
  else{
    tailPos = tail;}


  ESC.write(Speed);
  Tail.write(tailPos);
  
  
}



void printVals(){
  Serial.print("Left State :  ");
  Serial.print(leftState);
  Serial.print(",  Right State :  ");
  Serial.print(rightState);
  Serial.print(",  Forward State :  ");
  Serial.print(forwardState);
  Serial.print(",  Backward State :  ");
  Serial.println(backwardState);
}
