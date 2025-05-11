#include "Customer.h"
#include <iostream>
#include<fstream>

Customer::Customer(std::string n, std::string e, int pts) : User(n, e), points(pts) {}

void Customer::addToCart(const Product& p) 
{
    cart.addItem(p);
}

void Customer::viewCart() const 
{
    cart.viewCart();
}

void Customer::buy_product() {
    int product_id, quantity;
    cout << "Enter Product ID to buy: ";
    cin >> product_id;
    cout << "Enter Quantity: ";
    cin >> quantity;

    ifstream file("product.txt");
    if (!file.is_open()) {
        cout << "Unable to open product file!" << endl;
        return;
    }

    vector<Product> products;
    Product temp;
    bool found = false, updated = false;

    while (file >> temp.id >> temp.name >> temp.price >> temp.quantity) {
        if (temp.id == product_id) {
            found = true;
            if (temp.quantity >= quantity) {
                temp.quantity -= quantity;
                updated = true;
                cout << "Purchase successful!" << endl;
            } else {
                cout << "Insufficient stock." << endl;
            }
        }
        products.push_back(temp);
    }
    file.close();

    if (!found) {
        cout << "Product not found." << endl;
        return;
    }

    if (updated) {
        ofstream outfile("product.txt");
        for (const auto &p : products) {
            outfile << p.id << " " << p.name << " " << p.price << " " << p.quantity << endl;
        }
        outfile.close();
    }
}


void Customer::checkout() 
{
    double total = cart.getTotal();
    std::cout << "Cart Total: $" << total << "\n";
    double discount = points * 0.1;
    if (discount > total) discount = total;
    std::cout << "Points Discount: $" << discount << "\n";
    std::cout << "Final Total: $" << total - discount << "\n";

    points = 0;
    // Consider: points = static_cast<int>((total - discount) / 10); // Reward logic
    // cart.clear(); // Add a clearCart() method to reset items
}


void Customer::displayMenu() const 
{
    std::cout << "Customer Menu:\n1. Browse Products\n2. View Cart\n3. Checkout\n";
}
