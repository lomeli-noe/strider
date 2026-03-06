#pragma once

#include <Servo.h>
#include "include/PIDController.hpp"

/**
 * @brief Manages the steering servo and the PID loop that drives it.
 *
 * Owns the Servo object and clamps output to the configured left/right limits.
 */
class SteeringController {
public:
    SteeringController(int servoPin,
                       int centerAngle,
                       int leftMax,
                       int rightMax,
                       PIDController& pid);

    void begin();

    /**
     * @param lateralError  Signed pixel offset (frame_centre_x − target_x).
     * @param dt_ms         Elapsed milliseconds since last call.
     */
    void update(float lateralError, int dt_ms);

    void adjustLeftMax(int delta);
    void adjustRightMax(int delta);

    int getLeftMax()  const;
    int getRightMax() const;

private:
    Servo        m_servo;
    PIDController& m_pid;

    const int m_servoPin;
    const int m_centerAngle;
    int       m_leftMax;
    int       m_rightMax;
    int       m_currentAngle;
};
