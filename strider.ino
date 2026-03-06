#include "Config.hpp"
#include "PIDController.hpp"
#include "SteeringController.hpp"
#include "DriveController.hpp"
#include "BluetoothHandler.hpp"
#include "TelemetryLogger.hpp"
#include "PixyCamSensor.hpp"

// ── Module instances ──────────────────────────────────────────────────────────
PixyCamSensor     pixy;
PIDController     pid(PID_KP_DEFAULT, PID_KI_DEFAULT, PID_KD_DEFAULT);
SteeringController steering(PIN_SERVO_DIR, SERVO_CENTER,
                             SERVO_LEFT_MAX, SERVO_RIGHT_MAX, pid);
DriveController   drive(PIN_MOTOR_EN, PIN_MOTOR_IN1, PIN_MOTOR_IN2, SPEED_BASE);
BluetoothHandler  bluetooth(steering, pid);
TelemetryLogger   telemetry(steering, drive, pid, SERIAL_INTERVAL_MS);

// ── Timing ────────────────────────────────────────────────────────────────────
unsigned long prevSpeedMs = 0;
unsigned long prevSteerMs = 0;

// ── Helpers ───────────────────────────────────────────────────────────────────
/**
 * @return true when the target position warrants an emergency stop.
 */
static bool isOutOfBounds(int32_t xOffset, int32_t yOffset) {
    return yOffset >  Y_EMERGENCY_STOP
        || yOffset <  Y_LOST_FAR
        || xOffset >  X_LOST_THRESHOLD
        || xOffset < -X_LOST_THRESHOLD;
}

// ── Arduino entry points ──────────────────────────────────────────────────────
void setup() {
    Serial.begin(SERIAL_BAUD);

    steering.begin();
    drive.begin();

    pixy.begin();

    prevSteerMs = millis();
}

void loop() {
    const unsigned long now = millis();

    bluetooth.poll();
    telemetry.poll(now);

    pixy.update();

    if (!pixy.isTargetVisible()) {
        drive.stop();
        return;
    }

    // Pixel offsets relative to frame centre
    const int32_t xOffset = pixy.getFrameWidth()  / 2 - pixy.getTargetX();
    const int32_t yOffset = pixy.getTargetY() - pixy.getFrameHeight() / 2;

    if (isOutOfBounds(xOffset, yOffset)) {
        drive.stop();
        return;
    }

    // Steering update (every loop, dt derived from wall clock)
    const unsigned long nowMs = millis();
    const int dt = static_cast<int>(nowMs - prevSteerMs);
    prevSteerMs  = nowMs;
    steering.update(static_cast<float>(xOffset), dt);

    // Speed update (throttled to SPEED_INTERVAL_MS)
    if (now - prevSpeedMs >= SPEED_INTERVAL_MS) {
        drive.updateSpeed(yOffset);
        prevSpeedMs = now;
    }

    drive.drive();
}
