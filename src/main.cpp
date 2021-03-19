#include <main.h>

#define EN_PIN    33  // LOW: Driver enabled. HIGH: Driver disabled
#define STEP_PIN  27  // Step on rising edge
#define DIR_PIN 12    // Direction

#define SERIAL_PORT Serial1 // TMC2208/TMC2224 HardwareSerial port
#define R_SENSE 0.11f // Match to your driver

TMC2208Stepper driver(&SERIAL_PORT, R_SENSE);                     // Hardware Serial


void setup()
{

	// Prepare pins
	pinMode(EN_PIN, OUTPUT);
	pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  digitalWrite(EN_PIN, LOW);      // Enable driver in hardware

  driver.begin();
  driver.toff(5);                 // Enables driver in software
  driver.rms_current(600);        // Set motor RMS current
  driver.microsteps(16);          // Set microsteps to 1/16th

  driver.pwm_autoscale(true);     // Needed for stealthChop

}

bool shaft = false;

void loop()
{

  for (uint16_t i = 5000; i>0; i--) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(160);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(160);
  }
  shaft = !shaft;
  driver.shaft(shaft);
  
}