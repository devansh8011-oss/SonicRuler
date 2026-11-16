#include "EasyUltrasonic.h"

EasyUltrasonic::EasyUltrasonic(uint8_t trigPin, uint8_t echoPin)
  : _trigPin(trigPin), _echoPin(echoPin), _ready(false) {}

float EasyUltrasonic::readDistance(DistanceUnit unit) {
  // Set up pins on first use
  if (!_ready) {
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
    _ready = true;
  }

  // Send a 10 microsecond pulse on TRIG
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  // Time how long ECHO stays HIGH (give up after 30 ms, about 5 m)
  unsigned long duration = pulseIn(_echoPin, HIGH, 30000UL);
  if (duration == 0) return -1;

  // Sound travels ~0.0343 cm per microsecond; divide by 2 for there and back
  float cm = duration * 0.0343 / 2.0;

  switch (unit) {
    case MM:   return cm * 10.0;
    case M:    return cm / 100.0;
    case KM:   return cm / 100000.0;
    case INCH: return cm / 2.54;
    case FEET: return cm / 30.48;
    default:   return cm;
  }
}
