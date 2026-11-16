// BasicDistance - print distance in cm
#include <SonicRuler.h>

SonicRuler ultrasonic(9, 10);   // (TRIG, ECHO)

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Distance: ");
  Serial.print(ultrasonic.readDistance(CM));
  Serial.println(" cm");
  delay(500);
}
