<h1 align="center">EasyUltrasonic</h1>

<p align="center">
  <b>The simplest way to use an HC-SR04 ultrasonic sensor with Arduino.</b><br>
  Two pins in, one function, distance out.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/version-1.0.0-blue" alt="Version">
  <img src="https://img.shields.io/badge/platform-Arduino%20%7C%20ESP32%20%7C%20ESP8266-00979D" alt="Platform">
  <img src="https://img.shields.io/badge/license-MIT-green" alt="License">
</p>

---

## Table of Contents

- [Overview](#overview)
- [Installation](#installation)
- [Wiring](#wiring)
- [Quick Start](#quick-start)
- [API Reference](#api-reference)
- [Distance Units](#distance-units)
- [Examples](#examples)
- [Troubleshooting](#troubleshooting)
- [Library Structure](#library-structure)
- [License](#license)

---

## Overview

No `pinMode()`, no `pulseIn()`, no maths. Create the sensor with its **TRIG** and **ECHO** pins and call `readDistance()` with the unit you want.

```cpp
EasyUltrasonic ultrasonic(9, 10);         // TRIG, ECHO
float d = ultrasonic.readDistance(CM);    // that's it
```

**Works with:** HC-SR04, HC-SR04P and similar sensors, on Arduino Uno, Nano, Mega, ESP32, ESP8266, Raspberry Pi Pico and other Arduino-compatible boards.

---

## Installation

### Arduino IDE
1. Download [`EasyUltrasonic.zip`](EasyUltrasonic.zip), or click **Code → Download ZIP**.
2. Open **Sketch → Include Library → Add .ZIP Library…** and select the file.
3. Examples appear under **File → Examples → EasyUltrasonic**.

### PlatformIO
```ini
lib_deps =
    https://github.com/devansh8011-oss/EasyUltrasonic.git
```

---

## Wiring

| HC-SR04 | Arduino | ESP32 |
|---|---|---|
| VCC | 5V | 5V (VIN) |
| TRIG | D9 | GPIO5 |
| ECHO | D10 | GPIO18 (through divider) |
| GND | GND | GND |

> ⚠️ **ESP32 / 3.3 V boards:** the HC-SR04 ECHO pin outputs 5 V. Use a voltage divider (1 kΩ + 2 kΩ) on ECHO, or use the 3.3 V-compatible HC-SR04P.

---

## Quick Start

```cpp
#include <EasyUltrasonic.h>

EasyUltrasonic ultrasonic(9, 10);   // (TRIG, ECHO)

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Distance: ");
  Serial.print(ultrasonic.readDistance(CM));
  Serial.println(" cm");
  delay(500);
}
```

Open the Serial Monitor at **9600 baud**.

---

## API Reference

### Constructor

```cpp
EasyUltrasonic(uint8_t trigPin, uint8_t echoPin);
```

| Parameter | Description |
|---|---|
| `trigPin` | Pin connected to TRIG |
| `echoPin` | Pin connected to ECHO |

```cpp
EasyUltrasonic ultrasonic(9, 10);
```

### `readDistance()`

```cpp
float readDistance(DistanceUnit unit = CM);
```

Takes one measurement and returns the distance in the unit you choose. If you leave the unit out, it returns centimetres.

**Returns:** the distance, or **`-1`** if nothing is in range (about 2 cm – 400 cm).

```cpp
float d1 = ultrasonic.readDistance();       // cm (default)
float d2 = ultrasonic.readDistance(M);      // metres
float d3 = ultrasonic.readDistance(INCH);   // inches
```

---

## Distance Units

| Unit | Code |
|---|---|
| Millimetres | `ultrasonic.readDistance(MM)` |
| Centimetres | `ultrasonic.readDistance(CM)` |
| Metres | `ultrasonic.readDistance(M)` |
| Kilometres | `ultrasonic.readDistance(KM)` |
| Inches | `ultrasonic.readDistance(INCH)` |
| Feet | `ultrasonic.readDistance(FEET)` |

---

## Examples

### Print every unit
```cpp
#include <EasyUltrasonic.h>

EasyUltrasonic ultrasonic(9, 10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("mm: ");   Serial.println(ultrasonic.readDistance(MM));
  Serial.print("cm: ");   Serial.println(ultrasonic.readDistance(CM));
  Serial.print("m: ");    Serial.println(ultrasonic.readDistance(M), 3);
  Serial.print("km: ");   Serial.println(ultrasonic.readDistance(KM), 6);
  Serial.print("inch: "); Serial.println(ultrasonic.readDistance(INCH));
  Serial.print("feet: "); Serial.println(ultrasonic.readDistance(FEET));
  Serial.println("----");
  delay(1000);
}
```

### Handle "out of range"
```cpp
#include <EasyUltrasonic.h>

EasyUltrasonic ultrasonic(9, 10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  float distance = ultrasonic.readDistance(CM);

  if (distance == -1) {
    Serial.println("Nothing in range");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}
```

### Obstacle alert with an LED
```cpp
#include <EasyUltrasonic.h>

EasyUltrasonic ultrasonic(9, 10);

void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  float distance = ultrasonic.readDistance(CM);
  digitalWrite(13, (distance > 0 && distance < 20) ? HIGH : LOW);
  delay(100);
}
```

### Two sensors
```cpp
#include <EasyUltrasonic.h>

EasyUltrasonic front(9, 10);
EasyUltrasonic back(5, 6);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Front: "); Serial.print(front.readDistance(CM));
  delay(30);   // stop one sensor hearing the other's echo
  Serial.print(" cm | Back: "); Serial.print(back.readDistance(CM));
  Serial.println(" cm");
  delay(300);
}
```

---

## Troubleshooting

| Problem | Fix |
|---|---|
| Always `-1` | Check TRIG/ECHO aren't swapped, and VCC/GND are connected |
| Jumpy readings | Aim at a flat, hard surface |
| ESP32 misbehaves | Add a voltage divider on ECHO |
| Two sensors interfere | Add `delay(30)` between readings |

---

## Library Structure

```
EasyUltrasonic/
├── examples/
│   ├── AllUnits/AllUnits.ino
│   └── BasicDistance/BasicDistance.ino
├── src/
│   ├── EasyUltrasonic.cpp
│   └── EasyUltrasonic.h
├── keywords.txt
├── library.properties
├── LICENSE
└── README.md
```

---

## License

Released under the [MIT License](LICENSE).

<p align="center">
  Made by <a href="https://github.com/devansh8011-oss">Devansh</a>
</p>
