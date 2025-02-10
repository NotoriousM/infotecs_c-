#include "Client.hh"

Client::Client(const std::string& addr, int p) : address(addr), port(p), sock(-1) {
    reconnect();
}

void Client::reconnect() {
    if (sock != -1) {
        close(sock);
        sock = -1;
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Ошибка создания сокета.\n";
        return;
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    if (inet_pton(AF_INET, address.c_str(), &server_address.sin_addr) <= 0) {
        std::cerr << "Неверный адрес: " << address << "\n";
        return;
    }

    std::cout << "Ожидание подключения к серверу " << address << ":" << port << "...\n";
    while (connect(sock, (sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Не удалось подключиться к серверу: " << strerror(errno)
                  << "\nПовторная попытка через 1 секунду...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Подключение установлено!\n";
}

void Client::send_data(const std::string& data) {
    std::string message = data + "\n";
    if (send(sock, message.c_str(), message.size(), 0) < 0) {
        std::cerr << "Ошибка отправки данных: " << strerror(errno)
                  << "\nПереподключение...\n";
        reconnect();
        send_data(data);
    }
}
