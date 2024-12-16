#include "ISensor.hpp"
#include "SpeedSensor.hpp"
#include "CANBus/includes/CANBus.hpp"

int main() {

    CANBus canBus("vcan0", 500000);
    ISensor* sensor = new SpeedSensor(canBus, 0x100);
    ISensor* sensor2 = new ParkSensor(canBus, 0x200);
    while(1)
    {
        sensor->readData();
        sensor2->readData();
        std::cout << "Read from " << sensor->getType() << sensor->getValue() << std::endl;
    }
    delete sensor;
    return 0;
}