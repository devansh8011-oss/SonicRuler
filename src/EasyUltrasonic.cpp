#include "EasyUltrasonic.h"

EasyUltrasonic::EasyUltrasonic(uint8_t trigPin, uint8_t echoPin)
  : _trigPin(trigPin),
    _echoPin(echoPin),
    _initialized(false),
    _timeout(30000UL) {
  setTemperature(20.0);
  // NOTE: pinMode() is NOT called here on purpose. Global objects are
  // constructed before the board is fully initialised, so we set up the
  // pins in begin() (called automatically on the first read).
}

void EasyUltrasonic::begin() {
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);
  digitalWrite(_trigPin, LOW);
  _initialized = true;
}

void EasyUltrasonic::setTimeout(unsigned long timeoutMicros) {
  _timeout = timeoutMicros;
}

void EasyUltrasonic::setTemperature(float celsius) {
  // Speed of sound (m/s) ≈ 331.3 + 0.606 * T  → convert to cm/us
  _soundSpeedCmPerUs = (331.3 + 0.606 * celsius) / 10000.0;
}

unsigned long EasyUltrasonic::readEchoTime() {
  if (!_initialized) begin();

  // 10 us HIGH pulse on TRIG starts a measurement
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  // Measure how long ECHO stays HIGH (0 if timeout)
  return pulseIn(_echoPin, HIGH, _timeout);
}

float EasyUltrasonic::readDistance(DistanceUnit unit) {
  unsigned long duration = readEchoTime();
  if (duration == 0) return -1.0;   // no echo

  // Sound goes to the object and back, so divide by 2
  float cm = (duration * _soundSpeedCmPerUs) / 2.0;

  switch (unit) {
    case MM:   return cm * 10.0;
    case CM:   return cm;
    case M:    return cm / 100.0;
    case KM:   return cm / 100000.0;
    case INCH: return cm / 2.54;
    case FEET: return cm / 30.48;
    default:   return cm;
  }
}

float EasyUltrasonic::readAverage(uint8_t samples, DistanceUnit unit) {
  if (samples == 0) samples = 1;
  float total = 0;
  uint8_t good = 0;

  for (uint8_t i = 0; i < samples; i++) {
    float d = readDistance(unit);
    if (d >= 0) {
      total += d;
      good++;
    }
    delay(30);   // let old echoes die out (HC-SR04 needs ~60 ms cycle)
  }
  return good ? total / good : -1.0;
}
