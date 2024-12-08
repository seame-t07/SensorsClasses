
#pragma once

#include "ISensor.hpp"
#include <iostream>

class SpeedSensor : public ISensor {
    private:
        float lastSpeed;

    public:
        SpeedSensor(CANBus& can, uint32_t id);

        void initialize();
        void readData();
        const std::string getType() const;
};