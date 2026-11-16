/*
  EasyUltrasonic.h - Simple library for HC-SR04 ultrasonic sensors.
  Give it the TRIG and ECHO pins, then call readDistance().
  MIT License.
*/

#ifndef EASY_ULTRASONIC_H
#define EASY_ULTRASONIC_H

#include <Arduino.h>

// Units for readDistance()
enum DistanceUnit { MM, CM, M, KM, INCH, FEET };

class EasyUltrasonic {
  public:
    EasyUltrasonic(uint8_t trigPin, uint8_t echoPin);

    // Returns distance in the chosen unit (default CM).
    // Returns -1 if nothing is in range.
    float readDistance(DistanceUnit unit = CM);

  private:
    uint8_t _trigPin;
    uint8_t _echoPin;
    bool _ready;
};

#endif
