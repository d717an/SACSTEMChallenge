/*
  Stepper Test Rig

  ** DESIGNED FOR ARDUINO MEGA 2560 **

  Backwards movement:   650 to 1023
  Forward movement:     450 to 0

  AccelStepper Description
  http://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html
  
*/

#include <AccelStepper.h>

// Define some steppers and the pins the will use
#define X_STEP_PIN 2
#define X_DIR_PIN 3
#define Y_STEP_PIN 4
#define Y_DIR_PIN 5
AccelStepper x_step(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper y_step(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);

int sel_sw_pin = 53;
bool sel_sw_val = 1;
int x_pot_pin = A0;
int y_pot_pin = A1;
int x_pot_val;
int y_pot_val; 
float x_spd;
float y_spd;
float minMtrSpd = 5;
float maxMtrSpd = 500;


void setup() {
  
  Serial.begin(115200);

  y_step.setMaxSpeed(maxMtrSpd);
  y_step.setAcceleration(100.0);
  y_step.moveTo(100);

  x_step.setMaxSpeed(maxMtrSpd);
  x_step.setAcceleration(100.0);
  x_step.moveTo(100);

  pinMode(sel_sw_pin, INPUT_PULLUP);  
}

void loop() {

  sel_sw_val = digitalRead(sel_sw_pin);

  if (sel_sw_val==1) {
    // Use potentiometers to set motor speed 
  
    // read the potentiometers
    x_pot_val = analogRead(x_pot_pin);
    y_pot_val = analogRead(y_pot_pin);
  
    if (1) {
      Serial.print("sel_sw: ");
      Serial.print(sel_sw_val);
      Serial.print("  x_pot: ");
      Serial.print(x_pot_val);
      Serial.print("  x_spd: ");
      Serial.print(x_spd);
      Serial.print("  y_pot: ");
      Serial.print(y_pot_val);
      Serial.print("  y_spd: ");
      Serial.print(y_spd);
      Serial.print("\n");
    }
  
    if (x_pot_val > 650) {
      x_spd = map(x_pot_val, 650, 1023, -minMtrSpd, -maxMtrSpd);    
    } else if (x_pot_val < 450) {
      x_spd = map(x_pot_val, 450, 0, minMtrSpd, maxMtrSpd);
    } else {
      x_spd = 0;
    }
  
    if (y_pot_val > 650) {
      y_spd = map(y_pot_val, 650, 1023, -minMtrSpd, -maxMtrSpd);    
    } else if (y_pot_val < 450) {
      y_spd = map(y_pot_val, 450, 0, minMtrSpd, maxMtrSpd);
    } else {
      y_spd = 0;
    }

  } else {
    // Use RPI Joystick Commands to set motor speed
    
    // (code needed here)
    x_spd = 0;
    y_spd = 0;    
  }  

  // Send motor commands
  x_step.setSpeed(x_spd);
  x_step.runSpeed();
  y_step.setSpeed(y_spd);
  y_step.runSpeed();
  
}
