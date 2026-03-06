#pragma once

/**
 * @brief Generic discrete-time PID controller.
 *
 * Call update() every loop iteration; it returns the correction value that
 * should be applied to the plant.
 */
class PIDController {
public:
    PIDController(float kp, float ki, float kd);

    /**
     * @param error   Signed error (setpoint − measurement) for this tick.
     * @param dt_ms   Elapsed time since last call, in milliseconds.
     * @return        Correction output.
     */
    float update(float error, int dt_ms);

    void reset();

    // Runtime tuning (e.g. via Bluetooth)
    void setKp(float kp);
    void setKi(float ki);
    void setKd(float kd);

    float getKp() const;
    float getKi() const;
    float getKd() const;

private:
    float m_kp, m_ki, m_kd;
    float m_errorPrev  = 0.0f;
    float m_errorArea  = 0.0f;
};
