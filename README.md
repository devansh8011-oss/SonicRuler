# EasyUltrasonic

Simple Arduino library for HC-SR04 ultrasonic sensors. Give it the **TRIG** and **ECHO** pins, call `readDistance()`. That's it.

## Install
**Arduino IDE:** download this repo as ZIP → *Sketch → Include Library → Add .ZIP Library…*
**PlatformIO:** add to `platformio.ini`
```
lib_deps = https://github.com/devansh8011-oss/EasyUltrasonic.git
```

## Usage
```cpp
#include <EasyUltrasonic.h>

EasyUltrasonic ultrasonic(9, 10);   // (TRIG, ECHO)

void setup() { Serial.begin(115200); }

void loop() {
  Serial.println(ultrasonic.readDistance());      // cm
  Serial.println(ultrasonic.readDistance(M));     // metres
  delay(500);
}
```

## API
| Function | Returns |
|---|---|
| `readDistance(unit)` / `read_distance(unit)` | distance in `MM`, `CM` (default), `M`, `KM`, `INCH`, `FEET`; `-1` if no echo |
| `readCM()`, `readMM()`, `readM()`, `readKM()`, `readInch()` | shortcuts |
| `readAverage(samples, unit)` | average of N readings |
| `readEchoTime()` | raw echo time in µs |
| `setTimeout(us)` | max echo wait (default 30000 µs ≈ 5 m) |
| `setTemperature(°C)` | temperature compensation (default 20 °C) |

## ESP32 / 3.3 V boards
HC-SR04 ECHO outputs 5 V. Use a voltage divider (e.g. 1 kΩ + 2 kΩ) on ECHO, or use an HC-SR04P / 3.3 V-capable module.

## License
MIT
