#pragma once

#include <Pixy2.h>
#include "IVisionSensor.hpp"

/**
 * @brief IVisionSensor implementation backed by a Pixy2 camera.
 */
class PixyCamSensor : public IVisionSensor {
public:
    void begin() override;
    void update() override;

    bool    isTargetVisible() const override;
    int32_t getTargetX()      const override;
    int32_t getTargetY()      const override;
    int32_t getFrameWidth()   const override;
    int32_t getFrameHeight()  const override;

private:
    Pixy2 m_pixy;
    bool  m_visible = false;
};
