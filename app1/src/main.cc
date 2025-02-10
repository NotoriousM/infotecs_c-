#include "Buffer.hh"
#include "Client.hh"
#include "Dlib.hpp"  // Подключение библиотеки обработки данных
#include <iostream>
#include <thread>

int main() {
    Buffer buffer;
    Client client("127.0.0.1", 8080);

    // Поток 1: ввод пользователя
    std::thread thread_1([&] {
        std::string input;
        while (true) {
            std::cout << "Введите строку (цифры, до 64 символов): ";
            std::cin >> input;

            if (input.size() > 64 || !std::all_of(input.begin(), input.end(), ::isdigit)) {
                std::cerr << "Ошибка ввода! Введите не более 64 цифр.\n";
                continue;
            }

            Dlib::sorted(input); // Сортируем строку
            buffer.push(input);
        }
    });

    // Поток 2: обработка и отправка данных
    std::thread thread_2([&] {
        while (true) {
            std::string processed = buffer.pop();
            std::cout << "Обработанная строка: " << processed << std::endl;

            int sum = Dlib::calc_sum(processed);
            std::cout << "Вычисленная сумма цифр: " << sum << std::endl;

            std::string message = processed + "|" + std::to_string(sum);
            client.send_data(message);
        }
    });

    thread_1.join();
    thread_2.join();
    return 0;
}
