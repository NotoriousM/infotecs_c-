#pragma once
#include <string>
#include <algorithm>  // Для сортировки
#include <cctype>     // Для isdigit

class Dlib {
public:
    // Функция 1: Сортирует и заменяет четные цифры на "KB"
    static void sorted(std::string& input);

    // Функция 2: Считает сумму цифр в строке
    static int calc_sum(const std::string& str);

    // Функция 3: Проверяет длину строки
    static bool analyse_length(const std::string& str);
};