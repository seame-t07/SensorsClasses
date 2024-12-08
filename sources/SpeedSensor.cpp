#include "SpeedSensor.hpp"

SpeedSensor::SpeedSensor(CANBus& can, uint32_t id) : ISensor(can, id), lastSpeed(0) {
    ;
}

void SpeedSensor::initialize() {
    std::cout << "Inicializando sensor de velocidade..." << std::endl;
}

void SpeedSensor::readData() {
    uint32_t id;
    std::vector<uint8_t> data;

    // Verifica se há mensagem disponível no barramento CAN e lê os dados
    if (canBus.receiveMessage(id, data)) {
        // Verifica se o ID da mensagem é o esperado
        if (id == canId) {
            std::cout << "Mensagem recebida com ID: 0x" 
                      << std::hex << id << std::dec << "\nDados: ";

            // Imprime os dados recebidos no formato hexadecimal
            for (size_t i = 0; i < data.size(); ++i) {
                std::cout << "0x" << std::hex << (int)data[i] << " ";
            }

            std::cout << std::dec << std::endl; // Retorna ao formato decimal
        } else {
            std::cout << "Mensagem ignorada com ID inesperado: 0x" 
                      << std::hex << id << std::dec << std::endl;
        }
    } else {
        std::cout << "Nenhuma mensagem disponível no barramento CAN." << std::endl;
    }
}

const std::string SpeedSensor::getType() const{
    return "SpeedSensor";
}


