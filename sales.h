#ifndef SALES_H
#define SALES_H

#include <string>
#include <vector>
#include <fstream>

namespace Sales {

struct Product {
    std::string name;
    int quantity;
    float price;
    float total;
};

std::vector<Product> readDataFromFile(const std::string& filename, int& numProducts);
void calculateTotalCosts(std::vector<Product>& products);
Product findMostExpensive(const std::vector<Product>& products);
void sortByTotalCostDescending(std::vector<Product>& products);
void writeReportToFile(const std::string& filename, const std::vector<Product>& products, const Product& mostExpensive);

} // namespace Sales

#endif // SALES_H
