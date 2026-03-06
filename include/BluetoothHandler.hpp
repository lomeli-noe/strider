#pragma once

#include "include/SteeringController.hpp"
#include "include/PIDController.hpp"

/**
 * @brief Reads single-character Bluetooth commands from Serial and applies
 *        the corresponding tuning adjustments.
 *
 * Command map
 * -----------
 *  a / b  → left max  ± 1
 *  c / d  → right max ± 1
 *  g / h  → Kp        ± BT_PID_STEP_KP
 *  i / j  → Kd        ± BT_PID_STEP_KD
 *  k / l  → Ki        ± BT_PID_STEP_KI
 */
class BluetoothHandler {
public:
    BluetoothHandler(SteeringController& steering, PIDController& pid);

    /** Call once per loop() to read and act on any pending command. */
    void poll();

private:
    SteeringController& m_steering;
    PIDController&      m_pid;

    void handleCommand(char cmd);
};
