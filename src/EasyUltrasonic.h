/*
  EasyUltrasonic.h - Simple library for HC-SR04 style ultrasonic sensors.
  Just give it the TRIG pin and the ECHO pin, then call readDistance().

  Works on Arduino (Uno, Nano, Mega...), ESP32, ESP8266, Raspberry Pi Pico.
  MIT License.
*/

#ifndef EASY_ULTRASONIC_H
#define EASY_ULTRASONIC_H

#include <Arduino.h>

// Units you can ask for
enum DistanceUnit {
  MM,     // millimetres
  CM,     // centimetres (default)
  M,      // metres
  KM,     // kilometres
  INCH,   // inches
  FEET    // feet
};

class EasyUltrasonic {
  public:
    // Create the sensor: EasyUltrasonic ultrasonic(TRIG_PIN, ECHO_PIN);
    EasyUltrasonic(uint8_t trigPin, uint8_t echoPin);

    // Optional - pins are set up automatically on the first read.
    void begin();

    // Main function. Returns distance in the chosen unit (default cm).
    // Returns -1 if no echo came back (nothing in range / wiring problem).
    float readDistance(DistanceUnit unit = CM);

    // Same thing with snake_case name, if you prefer ultrasonic.read_distance()
    float read_distance(DistanceUnit unit = CM) { return readDistance(unit); }

    // Shortcuts
    float readCM()   { return readDistance(CM); }
    float readMM()   { return readDistance(MM); }
    float readM()    { return readDistance(M); }
    float readKM()   { return readDistance(KM); }
    float readInch() { return readDistance(INCH); }

    // Average of several readings (ignores failed ones) - smoother output
    float readAverage(uint8_t samples = 5, DistanceUnit unit = CM);

    // Raw echo time in microseconds (0 = timeout)
    unsigned long readEchoTime();

    // Max wait for echo in microseconds. Default 30000 us (~5 m range).
    void setTimeout(unsigned long timeoutMicros);

    // Speed of sound changes with temperature. Default is 20 °C.
    void setTemperature(float celsius);

  private:
    uint8_t _trigPin;
    uint8_t _echoPin;
    bool _initialized;
    unsigned long _timeout;
    float _soundSpeedCmPerUs;   // ~0.0343 cm/us at 20 °C
};

#endif
