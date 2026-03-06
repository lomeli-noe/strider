#pragma once

// ── Motor pins ────────────────────────────────────────────────────────────────
static constexpr int PIN_MOTOR_EN  = 6;
static constexpr int PIN_MOTOR_IN1 = 5;
static constexpr int PIN_MOTOR_IN2 = 4;

// ── Steering servo pin ────────────────────────────────────────────────────────
static constexpr int PIN_SERVO_DIR = 2;

// ── Steering limits (servo PWM angles) ───────────────────────────────────────
static constexpr int SERVO_CENTER    = 110;
static constexpr int SERVO_LEFT_MAX  = 120;
static constexpr int SERVO_RIGHT_MAX = 109;

// ── Speed (PWM 0-255) ─────────────────────────────────────────────────────────
static constexpr int SPEED_BASE        = 145;
static constexpr int SPEED_FAST        = 195;
static constexpr int SPEED_MAX         = 254;
static constexpr int SPEED_STEP        = 1;     // increment / decrement per tick
static constexpr unsigned long SPEED_INTERVAL_MS = 50;

// ── PID default gains ─────────────────────────────────────────────────────────
static constexpr float PID_KP_DEFAULT = 0.140f;
static constexpr float PID_KD_DEFAULT = 5.663f;
static constexpr float PID_KI_DEFAULT = 0.0000001f;

// ── Camera / target thresholds (pixels relative to frame centre) ──────────────
static constexpr int32_t Y_SPEED_UP_NEAR  = -30;   // target approaching fast
static constexpr int32_t Y_SPEED_UP_FAR   = -100;
static constexpr int32_t Y_SLOW_DOWN_NEAR =  20;
static constexpr int32_t Y_SLOW_DOWN_FAR  =  70;
static constexpr int32_t Y_EMERGENCY_STOP =  70;    // too close vertically
static constexpr int32_t Y_LOST_FAR       = -100;
static constexpr int32_t X_LOST_THRESHOLD =  150;   // too far laterally

// ── Bluetooth tuning step sizes ───────────────────────────────────────────────
static constexpr float  BT_PID_STEP_KP  = 0.001f;
static constexpr float  BT_PID_STEP_KD  = 0.001f;
static constexpr float  BT_PID_STEP_KI  = 0.0000001f;
static constexpr int    BT_SERVO_STEP   = 1;

// ── Serial ────────────────────────────────────────────────────────────────────
static constexpr long         SERIAL_BAUD     = 115200;
static constexpr unsigned long SERIAL_INTERVAL_MS = 1000;
