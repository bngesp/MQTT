

#include <Wire.h>

void setup() {
  Wire.begin(4);        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  Wire.onReceive(ecoute);
}

void loop() {
  //Wire.requestFrom(8, 6);    // request 6 bytes from slave device #8
}

void ecoute(){
   while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }

  delay(500);
}

