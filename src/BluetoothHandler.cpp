#include "include/BluetoothHandler.hpp"
#include "include/Config.hpp"
#include <Arduino.h>

BluetoothHandler::BluetoothHandler(SteeringController& steering, PIDController& pid)
    : m_steering(steering), m_pid(pid) {}

void BluetoothHandler::poll() {
    if (Serial.available() > 0) {
        handleCommand(static_cast<char>(Serial.read()));
    }
}

void BluetoothHandler::handleCommand(char cmd) {
    switch (cmd) {
        // Steering limits
        case 'a': m_steering.adjustLeftMax( BT_SERVO_STEP); break;
        case 'b': m_steering.adjustLeftMax(-BT_SERVO_STEP); break;
        case 'c': m_steering.adjustRightMax( BT_SERVO_STEP); break;
        case 'd': m_steering.adjustRightMax(-BT_SERVO_STEP); break;

        // PID gains
        case 'g': m_pid.setKp(m_pid.getKp() + BT_PID_STEP_KP); break;
        case 'h': m_pid.setKp(m_pid.getKp() - BT_PID_STEP_KP); break;
        case 'i': m_pid.setKd(m_pid.getKd() + BT_PID_STEP_KD); break;
        case 'j': m_pid.setKd(m_pid.getKd() - BT_PID_STEP_KD); break;
        case 'k': m_pid.setKi(m_pid.getKi() + BT_PID_STEP_KI); break;
        case 'l': m_pid.setKi(m_pid.getKi() - BT_PID_STEP_KI); break;

        default: break;
    }
}
