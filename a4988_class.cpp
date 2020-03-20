/*
 * DRIVER CLASS DEFINITION
 */

#include <Arduino.h>

class Driver {
  
  private:
  
    byte MS1_pin, MS2_pin, MS3_pin, STP_pin, DIR_pin;
    bool DIR = true;
    int dt = 800;
    int mode = 1; // Choose from 1 to 5
    String modeNames[5] = { "full", "half", "quarter", "eight", "sixteenth"};
    int modes[5][3] = {{0,0,0}, {1,0,0}, {0,1,0}, {1,1,0}, {1,1,1}}; // MS1 MS3 MS3

  public:
  
    float RPM = 0.0;
    
    Driver(byte MS1_pin, byte MS2_pin, byte MS3_pin, byte STP_pin, byte DIR_pin) {
      this->MS1_pin = MS1_pin;
      this->MS2_pin = MS2_pin;
      this->MS3_pin = MS3_pin;
      this->STP_pin = STP_pin;
      this->DIR_pin = DIR_pin;

      Serial.println("     ");
      Serial.println("Welcome to the a4988 driver!");
      Serial.println("[OK!] Create driver object.");
    }

    // Initialize the pins - OK
    void initialize () {
      pinMode(MS1_pin, OUTPUT); digitalWrite(MS1_pin, LOW);
      pinMode(MS2_pin, OUTPUT); digitalWrite(MS2_pin, LOW);
      pinMode(MS3_pin, OUTPUT); digitalWrite(MS3_pin, LOW);
      pinMode(STP_pin, OUTPUT); digitalWrite(STP_pin, LOW);
      pinMode(DIR_pin, OUTPUT); digitalWrite(DIR_pin, LOW);

      Serial.println("[OK!] Initialize pins.");
    }

    // Change mode of the motor - OK
    void set_mode(int mode) {
      this->mode = mode;
      
      digitalWrite(this->MS1_pin, modes[mode][0]);
      digitalWrite(this->MS2_pin, modes[mode][1]);
      digitalWrite(this->MS3_pin, modes[mode][2]);

      Serial.println("[OK!] Mode changed to: " + modeNames[mode]);
    }

    // Change direction of the motor - OK
    void change_direction() {
      
      this->DIR = !this->DIR;
      
      digitalWrite(DIR_pin, this->DIR);
      Serial.println("[OK!] Motors direction reversed from " + String(!this->DIR) + " to " + String(this->DIR) );
    }

    // Set the speed of the motor - OK
    void set_speed(float RPM) {
      
      this->RPM = RPM;
      
      int dt = 60.0*1000000.0 / (2.0*RPM*200.0*pow(2.0,mode));
      this->dt = dt;
      
      Serial.println("[OK!] Speed changed to: " + String(RPM) + " RPM." );
      Serial.println("      Time steps changed to: " + String(dt) + " microseconds." );
    }

    // Move by a certain number of steps - OK
    void turn_steps(int steps) {
      Serial.println("[OK!] Start turning " + String(steps) + " steps.");
      
      for (int i=0; i<steps; i++) {
        digitalWrite(this->STP_pin, HIGH);
        delayMicroseconds(this->dt); // 800 
        digitalWrite(this->STP_pin, LOW);
        delayMicroseconds(this->dt); // 800
      }
      Serial.println("[OK!] Finish turning " + String(steps) + " steps.");
    }

    // Move by a certain number of revolutions - OK
    void turn_revs(float revs) {
      Serial.println("[OK!] Start turning " + String(revs) + " revolutions.");

      int steps = revs*200*pow(2,mode);
      Serial.println("Steps: " + String(steps));
      for (int i=0; i<steps; i++) {
        digitalWrite(STP_pin, HIGH);
        delayMicroseconds(this->dt); // 800 
        digitalWrite(STP_pin, LOW);
        delayMicroseconds(this->dt); // 800
      }
      Serial.println("[OK!] Finish turning " + String(revs) + " revolutions.");
    }


    // Then calculate shear stress, shear rate and viscosity
    // Load cell requires calibration
    

};
