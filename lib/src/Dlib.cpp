#include "Dlib.hpp"

// Реализация функции 1
void Dlib::sorted(std::string& input) {
    // Сортировка по убыванию
    std::sort(input.rbegin(), input.rend());
    
    // Замена четных цифр на "KB"
    std::string res;
    for (char c : input) {
        if (isdigit(c) && (c - '0') % 2 == 0) {
            res += "KB";  // Заменяем четные цифры
        } else {
            res += c;     // Оставляем нечетные цифры
        }
    }
    input = res;  // Обновляем исходную строку
}

// Реализация функции 2
int Dlib::calc_sum(const std::string& str) {
    int sum = 0;
    for (char c : str) {
        if (isdigit(c)) {
            sum += c - '0';  // Суммируем только цифры
        }
    }
    return sum;
}

// Реализация функции 3
bool Dlib::analyse_length(const std::string& str) {
    size_t len = str.size();
    return (len > 2) && (len % 32 == 0);  // Проверка длины
}