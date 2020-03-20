/*
 * Copyright (c) 2019 Frank Laterza
 * Email: franklaterza@gmail.com
 *
 * This file is part of RC-Controller-Code.
 *
 * RC-Controller-Code is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


// This code is for communication bewteen an Arduino Nano and a simple drive and streer rc toy. 
// The Arduino Nano takes four inputs on pins 2, 4, 7, and 8 with two pwm pins on pins 3 and 5. 
// Pin 3 is for an ESC and pin 5 is for a servo


#include <Servo.h>

#define LEFTPIN 2
#define ESPIN 3
#define RIGHTPIN 4
#define SERVOPIN 5
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
  
  ESC.attach(ESPIN,1000,2000);
  Tail.attach(SERVOPIN);
 
  
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
