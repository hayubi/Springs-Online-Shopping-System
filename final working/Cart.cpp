#include "Cart.h"
#include <iostream>
#include <limits>




void Cart::addItem(const Product& p) {
    items.push_back(p);
}

void Cart::viewCart() const {
    if (items.empty()) {
        std::cout << "Cart is empty.\n";
        return;
    }
    for (const auto& item : items) {
        item.display();
    }
}

double Cart::getTotal() const {
    double total = 0.0;
    for (const auto& item : items)
        total += item.getPrice() * item.getQuantity();
    return total;
}

void Cart::clear() {
    items.clear();
}

void Cart::removeItem(const std::string& name) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getName() == name) {
            items.erase(it);
            std::cout << name << " removed from cart.\n";
            return;
        }
    }
    std::cout << "Item not found in cart.\n";
}

void Cart::checkout() {
    double total = getTotal();

    std::cout << "\nCart Total: Rs. " << total << std::endl;

    std::cout << "Enter payment amount (Rs.): ";
    double payment;
    std::cin >> payment;

    while (std::cin.fail() || payment < 0) {
        std::cout << "Invalid input. Enter a valid amount: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> payment;
    }
    
    while (payment < total) {
        std::cout << "Sorry, payment is less than total bill.\n";

        char choice;
        std::cout << "Do you want to remove an item from the cart? (y/n): ";
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            std::string name;
            std::cout << "Enter product name to remove: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            removeItem(name);
            total = getTotal();
            std::cout << "\nUpdated Cart Total: Rs. " << total << std::endl;

            std::cout << "Enter new payment amount: ";
            std::cin >> payment;
        } else {
            std::cout << "Checkout cancelled.\n";
            return;
        }
    }

    std::cout << "Payment successful. Thank you for shopping!\n";
    clear();  // ✅ Clear the cart after successful payment
}
