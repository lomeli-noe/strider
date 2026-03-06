#pragma once

#include <Arduino.h>

/**
 * @brief HAL interface for any vision/tracking sensor.
 *
 * Concrete implementations (e.g. PixyCamSensor) wrap specific hardware.
 * The rest of the application only depends on this interface.
 */
class IVisionSensor {
public:
    virtual ~IVisionSensor() = default;

    /** Initialise the hardware. Call once in setup(). */
    virtual void begin() = 0;

    /** Fetch the latest detection from the sensor. Call each loop iteration. */
    virtual void update() = 0;

    /** @return true if a target was detected in the last update(). */
    virtual bool isTargetVisible() const = 0;

    /** @return Pixel X coordinate of the primary target. */
    virtual int32_t getTargetX() const = 0;

    /** @return Pixel Y coordinate of the primary target. */
    virtual int32_t getTargetY() const = 0;

    /** @return Sensor frame width in pixels. */
    virtual int32_t getFrameWidth() const = 0;

    /** @return Sensor frame height in pixels. */
    virtual int32_t getFrameHeight() const = 0;
};
