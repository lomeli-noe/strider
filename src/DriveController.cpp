#include "include/DriveController.hpp"
#include "include/Config.hpp"

DriveController::DriveController(int pinEn, int pinIn1, int pinIn2, int baseSpeed)
    : m_pinEn(pinEn), m_pinIn1(pinIn1), m_pinIn2(pinIn2), m_speed(baseSpeed) {}

void DriveController::begin() {
    pinMode(m_pinEn,  OUTPUT);
    pinMode(m_pinIn1, OUTPUT);
    pinMode(m_pinIn2, OUTPUT);
}

void DriveController::updateSpeed(int32_t yOffset) {
    const bool approachingFast = (yOffset <= Y_SPEED_UP_NEAR && yOffset >= Y_SPEED_UP_FAR);
    const bool tooClose        = (yOffset >  Y_SLOW_DOWN_NEAR && yOffset <= Y_SLOW_DOWN_FAR);

    if (approachingFast) {
        if (m_speed < SPEED_FAST) m_speed = SPEED_FAST;
        if (m_speed < SPEED_MAX)  m_speed += SPEED_STEP;
        m_status = Status::SpeedingUp;
    } else if (tooClose) {
        if (m_speed > SPEED_FAST) m_speed -= SPEED_STEP;
        m_status = Status::SlowingDown;
    } else {
        m_status = Status::Neutral;
    }
}

void DriveController::stop() {
    digitalWrite(m_pinIn1, LOW);
    digitalWrite(m_pinIn2, LOW);
    m_status = Status::Stop;
}

void DriveController::drive() {
    digitalWrite(m_pinIn1, HIGH);
    digitalWrite(m_pinIn2, LOW);
    analogWrite(m_pinEn, m_speed);
}

DriveController::Status DriveController::getStatus() const { return m_status; }
int                      DriveController::getSpeed()  const { return m_speed;  }
