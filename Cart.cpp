#include "Cart.h"
#include <iostream>
#include <limits>
using namespace std;

void Cart::addItem(const Product& p) 
{
    items.push_back(p);
}

void Cart::viewCart() const 
{
    if (items.empty()) 
    {
        cout << "Cart is empty.\n";
        return;
    }
    for (const auto& item : items) 
    {
        item.display();
    }
}

double Cart::getTotal() const 
{
    double total = 0.0;
    for (const auto& item : items)
        total += item.getPrice() * item.getQuantity();
    return total;
}

void Cart::clear() 
{
    items.clear();
}

void Cart::removeItem(const string& name) 
{
    for (auto it = items.begin(); it != items.end(); ++it) 
    {
        if (it->getName() == name) 
        {
            items.erase(it);
            cout << name << " removed from cart.\n";
            return;
        }
    }
    cout << "Item not found in cart.\n";
}

void Cart::checkout() 
{
    double total = getTotal();

    cout << "\nCart Total: Rs. " << total << endl;

    cout << "Enter payment amount (Rs.): ";
    double payment;
    cin >> payment;

    while (cin.fail() || payment < 0) 
    {
        cout << "Invalid input. Enter a valid amount: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> payment;
    }
    
    while (payment < total) 
    {
        cout << "Sorry, payment is less than total bill.\n";

        char choice;
        cout << "Do you want to remove an item from the cart? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') 
        {
            string name;
            cout << "Enter product name to remove: ";
            cin.ignore();
            getline(cin, name);
            removeItem(name);
            total = getTotal();
            cout << "\nUpdated Cart Total: Rs. " << total << endl;

            cout << "Enter new payment amount: ";
            cin >> payment;
        } 
        else 
        {
            cout << "Checkout cancelled.\n";
            return;
        }
    }

    cout << "Payment successful. Thank you for shopping!\n";
    clear();
}