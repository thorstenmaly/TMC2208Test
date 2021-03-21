#include <main.h>

#define EN_PIN    15  // LOW: Driver enabled. HIGH: Driver disabled
#define STEP_PIN  33  // Step on rising edge

#define SERIAL_PORT Serial2 // TMC2208/TMC2224 HardwareSerial port
#define SERIAL2_TX 14
#define SERIAL2_RX 32

#define R_SENSE 0.11f // Match to your driver

TMC2208Stepper driver(&SERIAL_PORT, R_SENSE);                     // Hardware Serial

void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, SERIAL2_RX, SERIAL2_TX);
  while(!Serial);

	pinMode(EN_PIN, OUTPUT);
	pinMode(STEP_PIN, OUTPUT);

  digitalWrite(EN_PIN, LOW);      // Enable driver in hardware

  driver.begin();
  driver.toff(5);                 // Enables driver in software
  driver.rms_current(500);        // Set motor RMS current
  driver.microsteps(8);          // Set microsteps to 1/16th
  driver.pwm_autoscale(true);     // Needed for stealthChop

}

bool shaft = false;

void loop()
{

  for (uint16_t i = 10000; i>0; i--) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(50);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(50);
  }

  int16_t current_a = driver.cur_a();
  int16_t current_b = driver.cur_b();
  Serial.print("Current coil A: ");
  Serial.print(current_a);
  Serial.println(" A");

  Serial.print("Current coil B: ");
  Serial.print(current_b);
  Serial.println(" A");

  shaft = !shaft;
  driver.shaft(shaft);
  delay(1000);
  
}