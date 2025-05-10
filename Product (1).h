#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
class Product {
    int id;
    std::string name;
    double price;
public:
    Product(int i = 0, std::string n = "", double p = 0.0);
    void display() const;
    int getId() const;
    double getPrice() const;
    std::string getName() const;
};
void handleException(const std::string& message);
#endif
