#include <APDS9950.h>
#include <Wire.h>

// Global Variables
APDS9950 apds = APDS9950();


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9950 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9950 init!"));
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (apds.enablePower()) {
    Serial.println("Power enabled");
  }
  
  delay(1000);
  uint8_t a;
  a = apds.getMode();
  Serial.println(a, HEX);
  delay(1000);
  
  if (apds.disablePower()) {
    Serial.println("Power disabled");
  }
  delay(1000);
  
  a = apds.getMode();
  Serial.println(a, HEX);
  Serial.println();
  delay(1000);
}

