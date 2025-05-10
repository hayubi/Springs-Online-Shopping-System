#include "Customer.h"
#include <iostream>
Customer::Customer(std::string n, std::string e, int pts) : User(n, e), points(pts) {}
void Customer::addToCart(const Product& p) {
    cart.addItem(p);
}
void Customer::viewCart() const {
    cart.viewCart();
}
void Customer::checkout() {
    double total = cart.getTotal();
    std::cout << "Cart Total: $" << total << "\n";
    double discount = points * 0.1;
    if (discount > total) discount = total;
    std::cout << "Points Discount: $" << discount << "\n";
    std::cout << "Final Total: $" << total - discount << "\n";
    points = 0;
}
void Customer::display() const {
    std::cout << "Customer: " << name << " | Email: " << email << " | Points: " << points << "\n";
}
