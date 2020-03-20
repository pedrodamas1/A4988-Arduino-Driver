/*
 * Created and maintained by RadishLogic.com
 * https://www.radishlogic.com/arduino/use-c-class-arduino-ide-without-creating-library/
 */

// On a4988 board - order of pins: MS1, MS2, MS3, STEP, DIR

#include "a4988_class.cpp"

//# define MS1_pin = 2;
//# define MS2_pin = 3;
//# define MS3_pin = 4;
//# define STP_pin = 5;
//# define DIR_pin = 6;

/*
 *  BLINKER CLASS VARIABLES DECLARATION
 */
Driver nema17 = Driver(2, 3, 4, 5, 6);

void setup() {
  Serial.begin(9600);
  nema17.initialize();
  delay(2000);
  nema17.set_mode(4);
  delay(2000);
  nema17.change_direction();
  delay(2000);
  nema17.set_speed(10);
  delay(2000);
  nema17.turn_steps(200);
  delay(2000);
  nema17.turn_revs(2);
  delay(2000);
  Serial.println(nema17.RPM);
}

void loop() {

}
