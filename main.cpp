#include "sales.h"
#include <iostream>

int main() {
    std::string inputFile = "input.txt";  // Устанавливаем имя входного файла.
    std::string outputFile = "output.txt";  // Устанавливаем имя выходного файла.
    int numProducts = 0;  // Инициализируем переменную для количества товаров.

    auto products = Sales::readDataFromFile(inputFile, numProducts);  // Читаем данные из файла, получаем вектор продуктов.
    if (numProducts == 0) {  // Проверяем, успешно ли прошло чтение (если 0, значит ошибка).
        return 1;  // Выходим из программы с кодом ошибки.
    }

    Sales::calculateTotalCosts(products);  // Вычисляем общие стоимости для всех товаров.
    auto mostExpensive = Sales::findMostExpensive(products);  // Находим самый дорогой товар.
    Sales::sortByTotalCostDescending(products);  // Сортируем товары по убыванию стоимости.
    Sales::writeReportToFile(outputFile, products, mostExpensive);  // Записываем отчет в выходной файл.

    std::cout << "Report written to " << outputFile << std::endl;  // Выводим сообщение об успешной записи.
    return 0;  // Завершаем программу успешно.
}
