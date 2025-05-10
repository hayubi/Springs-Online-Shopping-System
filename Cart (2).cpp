#include "Cart.h"
#include <iostream>
void Cart::addItem(const Product& p) {
    items.push_back(p);
}
void Cart::viewCart() const {
    for (const auto& item : items)
        item.display();
}
double Cart::getTotal() const {
    double total = 0.0;
    for (const auto& item : items)
        total += item.getPrice();
    return total;
}
