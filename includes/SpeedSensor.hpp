
#pragma once

#include "ISensor.hpp"
#include <iostream>

class SpeedSensor : public ISensor {
    private:
        int _lastSpeed;

    public:
        SpeedSensor(CANBus& can, uint32_t id);

        void initialize();
        int readData();
        
        const std::string getType() const;
        const int getValue() const;
};