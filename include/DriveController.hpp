#pragma once

#include <Arduino.h>

/**
 * @brief Controls the DC drive motor via an H-bridge.
 *
 * Handles forward motion, coasting/braking, and speed ramping based on the
 * vertical pixel offset reported by the camera.
 */
class DriveController {
public:
    enum class Status { Stop, Neutral, SpeedingUp, SlowingDown };

    DriveController(int pinEn, int pinIn1, int pinIn2, int baseSpeed);

    void begin();

    /**
     * @brief Adjust speed according to how far the target is vertically.
     * @param yOffset  Signed pixel offset (target_y − frame_centre_y).
     *                 Negative means target is above centre (farther away).
     */
    void updateSpeed(int32_t yOffset);

    void stop();
    void drive();   ///< Apply current speed setting to motors

    Status  getStatus()   const;
    int     getSpeed()    const;

private:
    const int m_pinEn;
    const int m_pinIn1;
    const int m_pinIn2;

    int    m_speed;
    Status m_status = Status::Stop;
};
