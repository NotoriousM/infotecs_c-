#!/bin/bash
if [ -d "build" ]; then
    echo "Директория 'build' уже существует."
else
    echo "Создаем директорию 'build'..."
    mkdir build
fi
cd build || { echo "Ошибка: Не удалось перейти в директорию 'build'."; exit 1; }
echo "Запускаем CMake..."
cmake .. || { echo "Ошибка: CMake завершился с ошибкой."; exit 1; }
echo "Компилируем проект..."
make || { echo "Ошибка: make завершился с ошибкой."; exit 1; }
echo "Проект успешно собран. Исполняемый файл находится в директории 'build'."