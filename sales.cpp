#include "sales.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

namespace Sales {

// Функция для чтения данных из файла.
// Сначала открываем файл, проверяем, открылся ли он.
// Затем читаем количество товаров, проверяем его на корректность (от 1 до 50).
// Далее в цикле читаем данные для каждого товара и добавляем в вектор.
// Если ошибка чтения, выводим сообщение и возвращаем пустой вектор.
// В конце закрываем файл.
std::vector<Product> readDataFromFile(const std::string& filename, int& numProducts) {
    std::ifstream in(filename);  // Открываем файл для чтения.
    if (!in.is_open()) {  // Проверяем, успешно ли открылся файл.
        std::cerr << "Error opening file: " << filename << std::endl;  // Выводим сообщение об ошибке, если файл не открылся.
        numProducts = 0;  // Устанавливаем количество товаров в 0, чтобы указать на ошибку.
        return {};  // Возвращаем пустой вектор продуктов.
    }

    in >> numProducts;  // Читаем количество товаров из файла.
    if (numProducts <= 0 || numProducts > 50) {  // Проверяем, что количество товаров в допустимом диапазоне.
        std::cerr << "Invalid number of products: " << numProducts << std::endl;  // Выводим сообщение, если количество некорректно.
        numProducts = 0;  // Сбрасываем количество в 0.
        return {};  // Возвращаем пустой вектор.
    }

    std::vector<Product> products;  // Создаем вектор для хранения продуктов.
    products.reserve(numProducts);  // Резервируем место в векторе для ускорения добавления элементов.
    for (int i = 0; i < numProducts; ++i) {  // Цикл для чтения данных о каждом товаре.
        Product p;  // Создаем структуру для текущего товара.
        in >> p.name >> p.quantity >> p.price;  // Читаем имя, количество и цену из файла.
        if (in.fail()) {  // Проверяем, произошла ли ошибка при чтении.
            std::cerr << "Error reading data for product " << i + 1 << std::endl;  // Выводим сообщение об ошибке чтения.
            numProducts = 0;  // Сбрасываем количество.
            return {};  // Возвращаем пустой вектор.
        }
        products.push_back(p);  // Добавляем товар в вектор.
    }
    in.close();  // Закрываем файл.
    return products;  // Возвращаем вектор с продуктами.
}

// Функция для вычисления общей стоимости каждого товара.
// Проходим по вектору продуктов в цикле.
// Для каждого товара умножаем количество на цену и сохраняем в поле total.
void calculateTotalCosts(std::vector<Product>& products) {
    for (auto& p : products) {  // Цикл по всем продуктам с ссылкой, чтобы изменять оригиналы.
        p.total = p.quantity * p.price;  // Вычисляем общую стоимость: количество умножить на цену.
    }
}

// Функция для поиска самого дорогого товара.
// Если вектор пуст, возвращаем пустую структуру.
// Иначе используем std::max_element, чтобы найти товар с максимальной total.
// Сравниваем по полю total.
Product findMostExpensive(const std::vector<Product>& products) {
    if (products.empty()) {  // Проверяем, пуст ли вектор продуктов.
        return {};  // Возвращаем пустую структуру, если ничего нет.
    }
    auto maxIt = std::max_element(products.begin(), products.end(),
                                  [](const Product& a, const Product& b) { return a.total < b.total; });  // Находим итератор на элемент с максимальной стоимостью.
    return *maxIt;  // Возвращаем копию найденного товара.
}

// Функция для сортировки товаров по общей стоимости по убыванию.
// Используем std::sort с лямбдой, где сравниваем total в обратном порядке (a > b).
void sortByTotalCostDescending(std::vector<Product>& products) {
    std::sort(products.begin(), products.end(),
              [](const Product& a, const Product& b) { return a.total > b.total; });  // Сортируем вектор: от большего total к меньшему.
}

// Функция для записи отчета в файл.
// Открываем файл для записи, проверяем открытие.
// Устанавливаем формат вывода: фиксированная точность с 2 знаками после запятой.
// Записываем информацию о каждом товаре.
// Затем пишем о самом дорогом товаре.
// Далее список товаров по убыванию с номерами.
// В конце закрываем файл.
void writeReportToFile(const std::string& filename, const std::vector<Product>& products, const Product& mostExpensive) {
    std::ofstream out(filename);  // Открываем файл для записи.
    if (!out.is_open()) {  // Проверяем, успешно ли открылся файл.
        std::cerr << "Error opening file for writing: " << filename << std::endl;  // Выводим сообщение об ошибке.
        return;  // Выходим из функции.
    }

    out << std::fixed << std::setprecision(2);  // Устанавливаем формат: фиксированная точка, 2 знака после запятой.
    for (const auto& p : products) {  // Цикл по продуктам для записи их данных.
        out << "Product: " << p.name << ", Total cost: " << p.total << "\n";  // Записываем имя и общую стоимость.
    }
    out << "Most expensive product: " << mostExpensive.name << " (" << mostExpensive.total << ")\n";  // Записываем информацию о самом дорогом товаре.
    out << "Products by descending cost:\n";  // Записываем заголовок для списка.
    for (size_t i = 0; i < products.size(); ++i) {  // Цикл для записи отсортированного списка.
        out << i + 1 << ". " << products[i].name << ": " << products[i].total << "\n";  // Записываем номер, имя и стоимость.
    }
    out.close();  // Закрываем файл.
}

} // namespace Sales
