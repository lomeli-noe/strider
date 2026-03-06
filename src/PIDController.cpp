#include "include/PIDController.hpp"

PIDController::PIDController(float kp, float ki, float kd)
    : m_kp(kp), m_ki(ki), m_kd(kd) {}

float PIDController::update(float error, int dt_ms) {
    if (dt_ms <= 0) return 0.0f;

    const float errorChange = error - m_errorPrev;
    const float slope       = errorChange / static_cast<float>(dt_ms);

    m_errorArea  += error * static_cast<float>(dt_ms);
    m_errorPrev   = error;

    return m_kp * error + m_kd * slope + m_ki * m_errorArea;
}

void PIDController::reset() {
    m_errorPrev = 0.0f;
    m_errorArea = 0.0f;
}

void PIDController::setKp(float kp) { m_kp = kp; }
void PIDController::setKi(float ki) { m_ki = ki; }
void PIDController::setKd(float kd) { m_kd = kd; }

float PIDController::getKp() const { return m_kp; }
float PIDController::getKi() const { return m_ki; }
float PIDController::getKd() const { return m_kd; }
