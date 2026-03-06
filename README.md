# Strider

Arduino-based autonomous RC car that uses a **Pixy2 camera** to track a coloured target, steer toward it with a PID controller, and modulate speed based on the target's vertical position in the frame.

## Demo

[![Strider demo](https://img.youtube.com/vi/o-yQknRDKSY/hqdefault.jpg)](https://youtu.be/o-yQknRDKSY)

---

## Project structure

```
strider/
├── strider.ino          # Thin orchestrator – setup() / loop() only
├── include/             # Public headers (one class per file)
│   ├── Config.hpp           # All constants and magic numbers
│   ├── PIDController.hpp
│   ├── SteeringController.hpp
│   ├── DriveController.hpp
│   ├── BluetoothHandler.hpp
│   └── TelemetryLogger.hpp
└── src/                 # Implementations
    ├── PIDController.cpp
    ├── SteeringController.cpp
    ├── DriveController.cpp
    ├── BluetoothHandler.cpp
    └── TelemetryLogger.cpp
```

### Module responsibilities

| Module | Responsibility |
|---|---|
| `Config.hpp` | Single source of truth for every constant / magic number |
| `PIDController` | Generic discrete-time PID (P + I + D) |
| `SteeringController` | Servo attachment, angle clamping, PID wiring |
| `DriveController` | H-bridge motor control, speed ramping |
| `BluetoothHandler` | Serial command parsing → tuning adjustments |
| `TelemetryLogger` | Periodic diagnostic output over Serial |

---

## Bluetooth command reference

| Key | Effect |
|---|---|
| `a` / `b` | Left servo limit +1 / −1 |
| `c` / `d` | Right servo limit +1 / −1 |
| `g` / `h` | Kp +0.001 / −0.001 |
| `i` / `j` | Kd +0.001 / −0.001 |
| `k` / `l` | Ki +0.0000001 / −0.0000001 |

---

## Hardware

| Component | Detail |
|---|---|
| Camera | Pixy2 (color connected components mode) |
| Steering | Servo on pin 2 |
| Drive | DC motor via H-bridge — EN: 6, IN1: 5, IN2: 4 |

---

## Tuning

All tunable values live in `include/Config.hpp`. Adjust PID gains, servo limits, speed thresholds, and timer intervals there before flashing.
