#include "include/SteeringController.hpp"
#include <Arduino.h>

SteeringController::SteeringController(int servoPin,
                                       int centerAngle,
                                       int leftMax,
                                       int rightMax,
                                       PIDController& pid)
    : m_pid(pid),
      m_servoPin(servoPin),
      m_centerAngle(centerAngle),
      m_leftMax(leftMax),
      m_rightMax(rightMax),
      m_currentAngle(centerAngle) {}

void SteeringController::begin() {
    m_servo.attach(m_servoPin);
    m_servo.write(m_centerAngle);
}

void SteeringController::update(float lateralError, int dt_ms) {
    const float correction = m_pid.update(lateralError, dt_ms);
    m_currentAngle += static_cast<int>(correction);
    m_currentAngle  = constrain(m_currentAngle, m_rightMax, m_leftMax);
    m_servo.write(m_currentAngle);
}

void SteeringController::adjustLeftMax(int delta)  { m_leftMax  += delta; }
void SteeringController::adjustRightMax(int delta) { m_rightMax += delta; }

int SteeringController::getLeftMax()  const { return m_leftMax; }
int SteeringController::getRightMax() const { return m_rightMax; }
