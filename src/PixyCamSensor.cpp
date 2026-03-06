#include "PixyCamSensor.hpp"

void PixyCamSensor::begin() {
    m_pixy.init();
    m_pixy.changeProg("color_connected_components");
}

void PixyCamSensor::update() {
    m_pixy.ccc.getBlocks();
    m_visible = (m_pixy.ccc.numBlocks > 0);
}

bool PixyCamSensor::isTargetVisible() const {
    return m_visible;
}

int32_t PixyCamSensor::getTargetX() const {
    return static_cast<int32_t>(m_pixy.ccc.blocks[0].m_x);
}

int32_t PixyCamSensor::getTargetY() const {
    return static_cast<int32_t>(m_pixy.ccc.blocks[0].m_y);
}

int32_t PixyCamSensor::getFrameWidth() const {
    return static_cast<int32_t>(m_pixy.frameWidth);
}

int32_t PixyCamSensor::getFrameHeight() const {
    return static_cast<int32_t>(m_pixy.frameHeight);
}
