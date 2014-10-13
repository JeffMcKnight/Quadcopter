#include <NewPing.h>


/*
PWM Generator 

 Most Arduinos have an on-board LED you can control. On the Uno and
 Leonardo, it is attached to digital pin 13. If you're unsure what
 pin the on-board LED is connected to on your Arduino model, check
 the documentation at http://arduino.cc
 
 This example code is in the public domain.
 
 modified 8 May 2014
 by Scott Fitzgerald
 modified by Jeff McKnight
 */
#include <SoftwareSerial.h>
#include <Servo.h> 

#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200

int loopDelay = 100;  // [msec]
int potpin = 0;  // analog pin used to connect the potentiometer
int servo_pin_port_bow = 13;
int servo_pin_starboard_bow = 10;
int servo_pin_port_stern = 11;
int servo_pin_starboard_stern = 12;
int val_min = 0 * 1000;
int val_max = 2 * 1000;
int val_range = val_max - val_min;
int val_step = val_range/100;
int val = val_min;    // variable to set the PWM high time 
int high_us = val + val_min;

Servo myservo;  // create servo object to control a servo 
NewPing sonar(TRIGGER_PIN, ECHO_PIN);

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial.println("Hello Console. Starting PWM");
  myservo.attach(servo_pin_port_bow);  // attaches the servo on pin 13 to the servo object 
  
}

// the loop function runs over and over again forever
void loop() {
  measureDistance();
  adjustPwm();
  delay(loopDelay);  // waits for the servo to get there 
  Serial.println();
}

void adjustPwm(){
  Serial.print("\t++ adjustPwm() -- val: ");
  Serial.print(val);
  if ((val < val_min) || (val > val_max)) {
    val_step = - val_step;
  } 
  myservo.writeMicroseconds(val);                  // sets the servo position according to the scaled value 
  val = (val + val_step);
}

void measureDistance(){
//  int uS = sonar.ping();
  int distanceInch = sonar.ping_in();
  Serial.print("\t++ measureDistance() -- distanceInch: ");
  Serial.print(distanceInch);
  Serial.print(" in");}

