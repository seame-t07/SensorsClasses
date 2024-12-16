#include "ParkSensor.hpp"

ParkSensor::ParkSensor(CANBus& can, uint32_t id) : ISensor(can, id), _distance(0) {
    ;
}

void ParkSensor::initialize() {
    std::cout << "Park Sensor" << std::endl;
}

int ParkSensor::readData() {
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

            std::cout << std::dec << std::endl;

            // Verifica se temos pelo menos 2 bytes (para distância em centímetros)
            if (data.size() >= 2) {
                // Lê os 2 bytes de dados recebidos (distância em cm)
                uint16_t distanceValue = (data[0] << 8) | data[1];  // Little-endian: byte alto | byte baixo

                // Atribui o valor de distância à variável _distance
                _distance = static_cast<int>(distanceValue); // Para garantir que seja tratado como inteiro

                std::cout << "Distância lida: " << _distance << " cm" << std::endl;

                return 0; // Sucesso
            } else {
                std::cerr << "Erro: Dados insuficientes para interpretar o valor de distância." << std::endl;
                return -1; // Erro: Dados insuficientes
            }
        } else {
            std::cout << "Mensagem ignorada com ID inesperado: 0x" 
                      << std::hex << id << std::dec << std::endl;
            return -1; // Erro: ID inesperado
        }
    } else {
        std::cout << "Nenhuma mensagem disponível no barramento CAN." << std::endl;
        return -1; // Erro: Nenhuma mensagem
    }
}


const int ParkSensor::getValue() const {
    return _distance;
}

const std::string ParkSensor::getType() const{
    return "ParkSensor";
}


