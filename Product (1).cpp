#include "Product.h"
#include "Utilities.h"
#include <iostream>
using namespace std;

#include <iostream>
Product::Product(int i, std::string n, double p) : id(i), name(n), price(p) {}
void Product::display() const {
    std::cout << "ID: " << id << " | " << name << " - $" << price << "\n";
}
int Product::getId() const { return id; }
double Product::getPrice() const { return price; }
std::string Product::getName() const { return name; }
void handleException(const string& message) {
    cout << "Exception: " << message << endl;
}