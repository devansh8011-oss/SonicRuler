// AllUnits - print the distance in every unit
#include <EasyUltrasonic.h>

EasyUltrasonic ultrasonic(9, 10);   // (TRIG, ECHO)

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("mm: ");     Serial.println(ultrasonic.readDistance(MM));
  Serial.print("cm: ");     Serial.println(ultrasonic.readDistance(CM));
  Serial.print("m: ");      Serial.println(ultrasonic.readDistance(M), 3);
  Serial.print("km: ");     Serial.println(ultrasonic.readDistance(KM), 6);
  Serial.print("inch: ");   Serial.println(ultrasonic.readDistance(INCH));
  Serial.print("feet: ");   Serial.println(ultrasonic.readDistance(FEET));
  Serial.println("----");
  delay(1000);
}
