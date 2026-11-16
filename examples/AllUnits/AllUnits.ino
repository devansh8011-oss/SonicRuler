// AllUnits - shows every unit, averaging and temperature compensation
#include <EasyUltrasonic.h>

EasyUltrasonic ultrasonic(9, 10);   // (TRIG, ECHO)

void setup() {
  Serial.begin(115200);
  ultrasonic.setTemperature(32);     // e.g. a hot day in Delhi
  ultrasonic.setTimeout(25000);      // optional: max range ~4 m
}

void loop() {
  Serial.print("mm: ");   Serial.print(ultrasonic.readDistance(MM));
  Serial.print(" | cm: "); Serial.print(ultrasonic.read_distance(CM));
  Serial.print(" | m: ");  Serial.print(ultrasonic.readDistance(M), 3);
  Serial.print(" | km: "); Serial.print(ultrasonic.readDistance(KM), 6);
  Serial.print(" | in: "); Serial.print(ultrasonic.readInch());
  Serial.print(" | avg cm: "); Serial.println(ultrasonic.readAverage(5));
  delay(500);
}
