// BasicDistance - print distance in cm every half second
#include <EasyUltrasonic.h>

#define TRIG_PIN 9
#define ECHO_PIN 10

EasyUltrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

void setup() {
  Serial.begin(115200);
}

void loop() {
  float distance = ultrasonic.readDistance();   // cm by default

  if (distance < 0) {
    Serial.println("Out of range");
  } else {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}
