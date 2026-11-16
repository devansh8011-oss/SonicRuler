<h1 align="center">EasyUltrasonic</h1>

<p align="center">
  <b>The simplest way to use an HC-SR04 ultrasonic sensor with Arduino.</b><br>
  Two pins in, distance out — in any unit you want.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/version-1.0.0-blue" alt="Version">
  <img src="https://img.shields.io/badge/platform-Arduino%20%7C%20ESP32%20%7C%20ESP8266-00979D" alt="Platform">
  <img src="https://img.shields.io/badge/license-MIT-green" alt="License">
  <img src="https://img.shields.io/badge/category-Sensors-orange" alt="Category">
</p>

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Supported Hardware](#supported-hardware)
- [Installation](#installation)
- [Wiring](#wiring)
- [Quick Start](#quick-start)
- [API Reference](#api-reference)
  - [Constructor](#constructor)
  - [begin()](#begin)
  - [readDistance()](#readdistance)
  - [read_distance()](#read_distance)
  - [readCM() / readMM() / readM() / readKM() / readInch()](#shortcut-functions)
  - [readAverage()](#readaverage)
  - [readEchoTime()](#readechotime)
  - [setTimeout()](#settimeout)
  - [setTemperature()](#settemperature)
- [Distance Units](#distance-units)
- [Using Multiple Sensors](#using-multiple-sensors)
- [Included Examples](#included-examples)
- [How It Works](#how-it-works)
- [Troubleshooting](#troubleshooting)
- [Library Structure](#library-structure)
- [Contributing](#contributing)
- [License](#license)

---

## Overview

Using an ultrasonic sensor normally means writing the same boilerplate every time: setting pin modes, sending a 10 µs trigger pulse, timing the echo with `pulseIn()`, and converting microseconds into distance.

**EasyUltrasonic** wraps all of that into one object. You give it the **TRIG** pin and the **ECHO** pin, and call `readDistance()`.

```cpp
EasyUltrasonic ultrasonic(9, 10);       // TRIG, ECHO
float cm = ultrasonic.readDistance();   // done
```

---

## Features

| | |
|---|---|
| ✅ **Two-pin setup** | Only TRIG and ECHO — no `pinMode()` needed |
| 📏 **Six units** | Millimetres, centimetres, metres, kilometres, inches, feet |
| 📊 **Averaging** | Smooth out noisy readings with `readAverage()` |
| 🌡️ **Temperature compensation** | Corrects for speed-of-sound changes with temperature |
| ⏱️ **Configurable timeout** | Limit the maximum range and keep `loop()` fast |
| 🔁 **Multiple sensors** | Create as many sensor objects as you have pins |
| 🧩 **Cross-platform** | Works on any board supported by the Arduino core |

---

## Supported Hardware

**Sensors**
- HC-SR04 (5 V)
- HC-SR04P / HC-SR04+ (3.3 V – 5 V)
- Any sensor with separate TRIG and ECHO pins using the same protocol (US-015, etc.)

**Boards**
- Arduino Uno, Nano, Mega, Leonardo, Pro Mini
- ESP32, ESP8266
- Raspberry Pi Pico (Arduino core)
- STM32, SAMD and other Arduino-compatible boards

---

## Installation

### Option 1 — Arduino IDE (ZIP)
1. Download [`EasyUltrasonic.zip`](EasyUltrasonic.zip) from this repository, or click **Code → Download ZIP**.
2. In the Arduino IDE, open **Sketch → Include Library → Add .ZIP Library…**
3. Select the downloaded file.
4. Restart the IDE. Examples appear under **File → Examples → EasyUltrasonic**.

### Option 2 — Manual
Copy the `EasyUltrasonic` folder into your Arduino libraries folder:

| OS | Path |
|---|---|
| Windows | `Documents\Arduino\libraries\` |
| macOS | `~/Documents/Arduino/libraries/` |
| Linux | `~/Arduino/libraries/` |

### Option 3 — PlatformIO
Add to your `platformio.ini`:
```ini
lib_deps =
    https://github.com/devansh8011-oss/EasyUltrasonic.git
```

### Option 4 — Arduino CLI
```bash
arduino-cli config set library.enable_unsafe_install true
arduino-cli lib install --git-url https://github.com/devansh8011-oss/EasyUltrasonic.git
```

---

## Wiring

### Arduino Uno / Nano / Mega (5 V)

| HC-SR04 Pin | Arduino Pin |
|---|---|
| VCC | 5V |
| TRIG | D9 |
| ECHO | D10 |
| GND | GND |

### ESP32 / ESP8266 / 3.3 V boards

> ⚠️ **Important:** The HC-SR04 ECHO pin outputs **5 V**, which can damage 3.3 V boards.
> Use a voltage divider on ECHO, or use the 3.3 V-compatible **HC-SR04P**.

```
HC-SR04 ECHO ──[ 1 kΩ ]──┬──── ESP32 GPIO18
                         │
                      [ 2 kΩ ]
                         │
                        GND
```

| HC-SR04 Pin | ESP32 Pin |
|---|---|
| VCC | 5V (VIN) |
| TRIG | GPIO5 |
| ECHO | GPIO18 (through divider) |
| GND | GND |

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
  Serial.print(ultrasonic.readDistance());
  Serial.println(" cm");
  delay(500);
}
```

Open the Serial Monitor at **9600 baud** to see the readings.

---

## API Reference

### Constructor

```cpp
EasyUltrasonic(uint8_t trigPin, uint8_t echoPin);
```

Creates a sensor object. Pins are configured automatically on the first reading.

| Parameter | Type | Description |
|---|---|---|
| `trigPin` | `uint8_t` | Pin connected to the sensor's TRIG |
| `echoPin` | `uint8_t` | Pin connected to the sensor's ECHO |

**Example**
```cpp
#include <EasyUltrasonic.h>

#define TRIG_PIN 9
#define ECHO_PIN 10

EasyUltrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(ultrasonic.readDistance());
  delay(500);
}
```

---

### `begin()`

```cpp
void begin();
```

Sets up the TRIG and ECHO pins. **Optional** — it is called automatically on the first reading. Call it in `setup()` if you want the pins configured immediately (for example, to hold TRIG LOW at boot).

**Example**
```cpp
#include <EasyUltrasonic.h>

EasyUltrasonic ultrasonic(9, 10);

void setup() {
  Serial.begin(9600);
  ultrasonic.begin();   // configure pins right away
}

void loop() {
  Serial.println(ultrasonic.readDistance());
  delay(500);
}
```

---

### `readDistance()`

```cpp
float readDistance(DistanceUnit unit = CM);
```

Triggers one measurement and returns the distance.

| Parameter | Type | Default | Description |
|---|---|---|---|
| `unit` | `DistanceUnit` | `CM` | One of `MM`, `CM`, `M`, `KM`, `INCH`, `FEET` |

**Returns:** distance as `float`, or **`-1`** if no echo was received (nothing in range or a wiring problem).

**Example**
```cpp
#include <EasyUltrasonic.h>

EasyUltrasonic ultrasonic(9, 10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  float cm     = ultrasonic.readDistance();       // centimetres (default)
  float meters = ultrasonic.readDistance(M);      // metres
  float inches = ultrasonic.readDistance(INCH);   // inches

  if (cm < 0) {
    Serial.println("Out of range");
  } else {
    Serial.print(cm);        Serial.print(" cm | ");
    Serial.print(meters, 3); Serial.print(" m | ");
    Serial.print(inches);    Serial.println(" in");
  }
  delay(500);
}
```

---

### `read_distance()`

```cpp
float read_distance(DistanceUnit unit = CM);
```

Identical to `readDistance()`, provided for those who prefer `snake_case` naming.

**Example**
```cpp
#include <EasyUltrasonic.h>

EasyUltrasonic ultrasonic(9, 10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(ultrasonic.read_distance(CM));
  Serial.println(" cm");
  delay(500);
}
```

---

### Shortcut Functions

```cpp
float readCM();
float readMM();
float readM();
float readKM();
float readInch();
```

One-word shortcuts for `readDistance(unit)`. Each returns `-1` if no echo was received.

| Function | Same as |
|---|---|
| `readCM()` | `readDistance(CM)` |
| `readMM()` | `readDistance(MM)` |
| `readM()` | `readDistance(M)` |
| `readKM()` | `readDistance(KM)` |
| `readInch()` | `readDistance(INCH)` |

**Example**
```cpp
#include <EasyUltrasonic.h>

EasyUltrasonic ultrasonic(9, 10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("CM: ");   Serial.println(ultrasonic.readCM());
  Serial.print("MM: ");   Serial.println(ultrasonic.readMM());
  Serial.print("M: ");    Serial.println(ultrasonic.readM(), 3);
  Serial.print("KM: ");   Serial.println(ultrasonic.readKM(), 6);
  Serial.print("Inch: "); Serial.println(ultrasonic.readInch());
  Serial.println("----");
  delay(1000);
}
```

---

### `readAverage()`

```cpp
float readAverage(uint8_t samples = 5, DistanceUnit unit = CM);
```

Takes several readings and returns their average. Failed readings are ignored. Useful for noisy environments or when the target is moving slightly.

| Parameter | Type | Default | Description |
|---|---|---|---|
| `samples` | `uint8_t` | `5` | Number of readings to average |
| `unit` | `DistanceUnit` | `CM` | Unit of the result |

**Returns:** average distance, or `-1` if every reading failed.

> ℹ️ Each sample waits ~30 ms, so `readAverage(5)` takes about 150 ms.

**Example**
```cpp
#include <EasyUltrasonic.h>

EasyUltrasonic ultrasonic(9, 10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  float single  = ultrasonic.readDistance();
  float average = ultrasonic.readAverage(10);       // 10 samples, cm
  float avgM    = ultrasonic.readAverage(5, M);     // 5 samples, metres

  Serial.print("Single: ");  Serial.print(single);
  Serial.print(" cm | Avg: "); Serial.print(average);
  Serial.print(" cm | Avg: "); Serial.print(avgM, 3);
  Serial.println(" m");
  delay(500);
}
```

---

### `readEchoTime()`

```cpp
unsigned long readEchoTime();
```

Returns the raw echo pulse duration in **microseconds**, or `0` on timeout. Useful for custom calculations or debugging.

**Example**
```cpp
#include <EasyUltrasonic.h>

EasyUltrasonic ultrasonic(9, 10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long us = ultrasonic.readEchoTime();

  if (us == 0) {
    Serial.println("No echo");
  } else {
    Serial.print("Echo time: ");
    Serial.print(us);
    Serial.println(" us");
  }
  delay(500);
}
```

---

### `setTimeout()`

```cpp
void setTimeout(unsigned long timeoutMicros);
```

Sets how long to wait for an echo before giving up. A shorter timeout limits the maximum range but keeps `loop()` responsive when nothing is in front of the sensor.

| Parameter | Type | Default | Description |
|---|---|---|---|
| `timeoutMicros` | `unsigned long` | `30000` | Max wait in µs (30000 µs ≈ 5 m) |

**Rule of thumb:** `timeout (µs) ≈ max range (cm) × 58`

| Max range | Timeout |
|---|---|
| 50 cm | 3000 |
| 1 m | 6000 |
| 2 m | 12000 |
| 4 m | 24000 |

**Example**
```cpp
#include <EasyUltrasonic.h>

EasyUltrasonic ultrasonic(9, 10);

void setup() {
  Serial.begin(9600);
  ultrasonic.setTimeout(6000);   // only care about objects within ~1 m
}

void loop() {
  float cm = ultrasonic.readDistance();

  if (cm < 0) {
    Serial.println("Nothing within 1 m");
  } else {
    Serial.print(cm);
    Serial.println(" cm");
  }
  delay(200);
}
```

---

### `setTemperature()`

```cpp
void setTemperature(float celsius);
```

The speed of sound depends on air temperature (~0.6 m/s per °C). Setting the ambient temperature improves accuracy, especially in very hot or cold conditions.

| Parameter | Type | Default | Description |
|---|---|---|---|
| `celsius` | `float` | `20.0` | Ambient air temperature in °C |

**Example — fixed temperature**
```cpp
#include <EasyUltrasonic.h>

EasyUltrasonic ultrasonic(9, 10);

void setup() {
  Serial.begin(9600);
  ultrasonic.setTemperature(35);   // hot summer day
}

void loop() {
  Serial.println(ultrasonic.readDistance());
  delay(500);
}
```

**Example — live temperature from a DHT11**
```cpp
#include <EasyUltrasonic.h>
#include <DHT.h>

EasyUltrasonic ultrasonic(9, 10);
DHT dht(2, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float t = dht.readTemperature();
  if (!isnan(t)) ultrasonic.setTemperature(t);

  Serial.print(ultrasonic.readDistance());
  Serial.print(" cm @ ");
  Serial.print(t);
  Serial.println(" C");
  delay(1000);
}
```

---

## Distance Units

| Constant | Unit | Typical use |
|---|---|---|
| `MM` | Millimetres | Precise short-range measurement |
| `CM` | Centimetres | **Default** — general purpose |
| `M` | Metres | Room / tank level measurement |
| `KM` | Kilometres | Data logging in large-scale units |
| `INCH` | Inches | Imperial projects |
| `FEET` | Feet | Imperial projects |

```cpp
ultrasonic.readDistance(MM);
ultrasonic.readDistance(FEET);
```

---

## Using Multiple Sensors

Each sensor is its own object, so you can use as many as you have pins.

```cpp
#include <EasyUltrasonic.h>

EasyUltrasonic front(9, 10);
EasyUltrasonic left(5, 6);
EasyUltrasonic right(3, 4);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Front: "); Serial.print(front.readDistance());
  delay(30);   // let echoes die out between sensors
  Serial.print(" | Left: "); Serial.print(left.readDistance());
  delay(30);
  Serial.print(" | Right: "); Serial.println(right.readDistance());
  delay(200);
}
```

> 💡 Read sensors one after another with a short delay to avoid one sensor picking up another's echo.

---

## Included Examples

| Example | Description |
|---|---|
| `BasicDistance` | Prints distance in cm, handles out-of-range |
| `AllUnits` | Shows every unit, averaging and temperature compensation |

Open them from **File → Examples → EasyUltrasonic** after installing.

---

## How It Works

1. The library pulls **TRIG** HIGH for 10 µs.
2. The sensor emits eight 40 kHz ultrasonic pulses.
3. **ECHO** goes HIGH until the reflected sound returns.
4. The library measures that HIGH time with `pulseIn()`.
5. Distance is calculated as:

```
distance (cm) = echo time (µs) × speed of sound (cm/µs) ÷ 2
speed of sound (m/s) = 331.3 + 0.606 × temperature (°C)
```

The division by 2 accounts for the sound travelling to the object **and back**.

---

## Troubleshooting

| Problem | Likely cause | Fix |
|---|---|---|
| Always returns `-1` | Wiring, or nothing in range | Check TRIG/ECHO aren't swapped; check 5 V and GND; try `setTimeout(30000)` |
| Always returns `0` or tiny values | ECHO floating / not connected | Verify ECHO wiring |
| Readings jump around | Soft or angled surfaces, noise | Use `readAverage()`; aim at a flat, hard surface |
| ESP32 resets or misbehaves | 5 V on a 3.3 V pin | Add a voltage divider on ECHO or use HC-SR04P |
| Wrong readings with multiple sensors | Cross-talk between sensors | Add `delay(30)` between reads |
| Minimum distance won't go below ~2 cm | Sensor blind zone | Physical limit of HC-SR04 (2 cm – 400 cm) |

---

## Library Structure

```
EasyUltrasonic/
├── examples/
│   ├── AllUnits/
│   │   └── AllUnits.ino
│   └── BasicDistance/
│       └── BasicDistance.ino
├── src/
│   ├── EasyUltrasonic.cpp
│   └── EasyUltrasonic.h
├── keywords.txt
├── library.properties
├── LICENSE
└── README.md
```

---

## Contributing

Contributions are welcome.

1. Fork this repository
2. Create a feature branch: `git checkout -b feature/my-improvement`
3. Commit your changes: `git commit -m "Add my improvement"`
4. Push the branch: `git push origin feature/my-improvement`
5. Open a Pull Request

Found a bug or have an idea? [Open an issue](https://github.com/devansh8011-oss/EasyUltrasonic/issues).

---

## License

Released under the [MIT License](LICENSE). Free to use in personal and commercial projects.

---

<p align="center">
  Made by <a href="https://github.com/devansh8011-oss">Devansh</a>
</p>
