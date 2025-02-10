#include "Server.hh"
#include "Dlib.hpp"
#include <csignal>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

Server::Server(int p) : port(p) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Ошибка создания серверного сокета.\n";
        exit(1);
    }

    // Опция SO_REUSEADDR для повторного использования порта
    int opt_flag = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt_flag, sizeof(opt_flag)) < 0) {
        std::cerr << "Ошибка установки опции SO_REUSEADDR.\n";
        exit(1);
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(sockfd, (sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Ошибка привязки серверного сокета к порту " << port << ".\n";
        exit(1);
    }
    if (listen(sockfd, 5) < 0) {
        std::cerr << "Ошибка прослушивания серверного сокета.\n";
        exit(1);
    }
    std::cout << "Сервер запущен на порту " << port << ". Ожидание подключений...\n";
}

void Server::start() {
    while (true) {
        int client_sock = accept(sockfd, nullptr, nullptr);
        if (client_sock < 0) {
            std::cerr << "Ошибка подключения клиента.\n";
            continue;
        }
        std::cout << "Клиент подключен.\n";

        char buffer[1024];
        std::string box_message; // Накопитель для данных от клиента.
        while (true) {
            ssize_t len = recv(client_sock, buffer, sizeof(buffer), 0);
            if (len <= 0) {
                std::cout << "Соединение с клиентом потеряно. Ожидание нового подключения...\n";
                close(client_sock);
                break;
            }

            // Добавляем полученные данные к накопленной строке.
            box_message.append(buffer, len);

            // Ищем разделитель (символ новой строки).
            size_t pos;
            while ((pos = box_message.find('\n')) != std::string::npos) {
                // Извлекаем полное сообщение (без символа новой строки).
                std::string complete_message = box_message.substr(0, pos);
                // Удаляем обработанную часть.
                box_message.erase(0, pos + 1);

                // Сообщение должно быть в формате: processedString|sum.
                size_t sep_pos = complete_message.find('|');
                if (sep_pos == std::string::npos) {
                    std::cerr << "Неверный формат сообщения: " << complete_message << std::endl;
                    continue;
                }
                std::string sort_str = complete_message.substr(0, sep_pos);
                std::string sum_str = complete_message.substr(sep_pos + 1);

                // Вызываем функцию ValidateLength для проверки длины обработанной строки.
                bool valid = Dlib::analyse_length(sort_str);
                if (valid) {
                    std::cout << "Получено сообщение:(вернула истину) " << complete_message << std::endl;
                } else {
                    std::cout << "Ошибка:(вернула ложь)." << std::endl;
                }
            }
        }
    }
}