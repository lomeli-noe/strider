#include "include/TelemetryLogger.hpp"

TelemetryLogger::TelemetryLogger(const SteeringController& steering,
                                 const DriveController&    drive,
                                 const PIDController&      pid,
                                 unsigned long             intervalMs)
    : m_steering(steering), m_drive(drive), m_pid(pid), m_intervalMs(intervalMs) {}

void TelemetryLogger::poll(unsigned long nowMs) {
    if (nowMs - m_lastPrintMs < m_intervalMs) return;
    m_lastPrintMs = nowMs;

    Serial.print(m_steering.getLeftMax());  Serial.print('|');
    Serial.print(m_steering.getRightMax()); Serial.print('|');
    Serial.print(m_drive.getSpeed());       Serial.print('|');
    Serial.print(m_pid.getKp(), 3);         Serial.print('|');
    Serial.print(m_pid.getKd(), 3);         Serial.print('|');
    Serial.print(m_pid.getKi(), 7);         Serial.print('|');
    Serial.println(statusToString(m_drive.getStatus()));
}

const char* TelemetryLogger::statusToString(DriveController::Status s) {
    switch (s) {
        case DriveController::Status::SpeedingUp:  return "speeding up";
        case DriveController::Status::SlowingDown: return "slowing down";
        case DriveController::Status::Neutral:     return "neutral";
        default:                                   return "stop";
    }
}
