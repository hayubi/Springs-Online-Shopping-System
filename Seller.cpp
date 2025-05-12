#include "Seller.h"
#include "ProductManager.h"
#include <iostream>
#include "Seller.h"
#include <fstream>
#include <iomanip>
using namespace std;

Seller::Seller(const string& n, const string& c, const string& add, const string& mail, const string& pass, ProductManager& pm) : User(n, c, add, mail, pass), productManager(pm) {}

void Seller::displayMenu() const 
{
    cout << "\n===== SELLER MENU =====\n";
    cout << "1. Add Product\n";
    cout << "2. Update Product\n";
    cout << "3. Remove Product\n";
    cout << "4. View My Products\n";
    cout << "0. Logout\n";
    cout << "Choice: ";
}

void Seller::addProduct() 
{
    int id, quantity;
    string name;
    double price;
    
    cout << "Enter product details:\n";
    cout << "ID: "; cin >> id;
    cout << "Name: "; cin >> name;
    cout << "Price: $"; cin >> price;
    cout << "Quantity: "; cin >> quantity;
    
    Product product(id, name, price, quantity, this->getEmail());
    productManager.addProduct(product);
}

void Seller::removeProduct() 
{
    string name;
    cout << "Enter product name to remove: ";
    cin >> name;
    productManager.removeProduct(name, this->getEmail());
}

void Seller::updateProduct() 
{
    int id, newQty;
    cout << "Enter product ID to update: ";
    cin >> id;
    cout << "Enter new quantity: ";
    cin >> newQty;
    productManager.updateProductQuantities(id, newQty, this->getEmail());
}

Seller::~Seller() {}
