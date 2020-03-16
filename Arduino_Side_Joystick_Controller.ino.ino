// DualMotorShield.pde
// -*- mode: C++ -*-
//
// Shows how to run 2 simultaneous steppers
// using the Itead Studio Arduino Dual Stepper Motor Driver Shield
// model IM120417015
// This shield is capable of driving 2 steppers at 
// currents of up to 750mA
// and voltages up to 30V
// Runs both steppers forwards and backwards, accelerating and decelerating
// at the limits.
//
// Copyright (C) 2014 Mike McCauley
// $Id:  $

#include <AccelStepper.h>

// The X Stepper pins
#define STEPPER1_DIR_PIN 3
#define STEPPER1_STEP_PIN 2
// The Y stepper pins
#define STEPPER2_DIR_PIN 5
#define STEPPER2_STEP_PIN 4

// Define some steppers and the pins the will use
AccelStepper stepper1(AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, STEPPER2_STEP_PIN, STEPPER2_DIR_PIN);
#define ANALOG_IN_X A0
#define ANALOG_IN_Y A1


void setup()
{  
    Serial.begin(115200);
    stepper1.setMaxSpeed(10000.0);
    stepper1.setAcceleration(100.0);
    stepper2.setMaxSpeed(10000.0);
    stepper2.setAcceleration(100.0);
}

String analog_in = "0.0000";
float val_x = 0.0;
float val_y = 0.0;
int stepsPerRevolution = 400;

void loop()
{
//  while (Serial.available() == 0){}
//  analog_in_x = Serial.readStringUntil('\n');
//  while (Serial.available() == 0){}
//  analog_in_y = Serial.readStringUntil('\n');
//  int analog_in_x = analogRead(ANALOG_IN_X);
//  int analog_in_y = analogRead(ANALOG_IN_Y);
  
//  Serial.println(analog_in_x);
  if (Serial.available() > 0){
    analog_in = Serial.readStringUntil('\n');
  }

  int index_1 = analog_in.indexOf('X'); 
  int index_2 = analog_in.length();
  val_x = analog_in.substring(0,index_1).toFloat();
  val_y = analog_in.substring(index_1+1,index_2-1).toFloat();
  
  stepper1.setSpeed(val_x*1024);
  stepper1.run();
  stepper2.setSpeed(val_y*1024);
  stepper2.run();
  //Serial.println("X:" + String(val_x) + "             Y:" + String(val_y));
  //Serial.println(index_2);
  delay(2);
  
  
}
