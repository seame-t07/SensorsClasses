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

            // Verifica se temos pelo menos 2 bytes
            if (data.size() >= 2) {
                // Leitura de 2 bytes e conversão para distância em centímetros
                // Certifique-se de que a ordem dos bytes está correta para o seu sistema
                // Little-endian (byte mais baixo vem primeiro)
                int sensorValue = data[0] | (data[1] << 8);  // Little-endian: byte baixo | byte alto << 8

                // Caso seja necessário usar Big-endian (byte mais alto vem primeiro):
                // int sensorValue = (data[1] | (data[0] << 8));  // Big-endian: byte alto | byte baixo << 8

                // Atribui o valor à variável _distance (distância em cm)
                _distance = sensorValue;

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


