#pragma once

#include <Arduino.h>
#include "include/SteeringController.hpp"
#include "include/DriveController.hpp"
#include "include/PIDController.hpp"

/**
 * @brief Periodically prints diagnostic telemetry over Serial.
 */
class TelemetryLogger {
public:
    TelemetryLogger(const SteeringController& steering,
                    const DriveController&    drive,
                    const PIDController&      pid,
                    unsigned long intervalMs);

    /** Call once per loop(); prints only when the interval has elapsed. */
    void poll(unsigned long nowMs);

private:
    const SteeringController& m_steering;
    const DriveController&    m_drive;
    const PIDController&      m_pid;

    const unsigned long m_intervalMs;
    unsigned long       m_lastPrintMs = 0;

    static const char* statusToString(DriveController::Status s);
};
