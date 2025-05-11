#include "Seller.h"
#include <iostream>
#include "Seller.h"
#include <fstream>
#include <iomanip>
using namespace std;

Seller::Seller(std::string n, std::string e) : User(n, e) {} 

void Seller::addProduct(const Product& p) 
{
    products.push_back(p);
}

void Seller::viewProducts() const 
{
    for (const auto& p : products)
        p.display();
}

void Seller::displayMenu() const 
{
    std::cout << "Seller Menu:\n1. Add Product\n2. View Products\n";
}

const std::vector<Product>& Seller::getProducts() const 
{
    return products;
}

void addProductToFile(int id, const string& name, double price, int quantity, const string& sellerName) 
{
    ofstream file("products.txt", ios::app);
    if (file.is_open()) 
    {
        file << id << " " << name << " " << price << " " << quantity << " " << sellerName << endl;
        cout << "Product added successfully.\n";
    } 
    else
        cout << "Error: Unable to open file for writing.\n";

    file.close();
}

void displayAllProducts() 
{
    ifstream file("products.txt");
    if (!file.is_open()) 
    {
        cout << "No products available.\n";
        return;
    }

    int id, quantity;
    string name, sellerName;
    double price;

    cout << "\n--- Available Products ---\n";
    cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(10) << "Price" << setw(10) << "Qty" << setw(15) << "Seller" << endl;
    cout << "------------------------------------------------------\n";

    while (file >> id >> name >> price >> quantity >> sellerName) 
    {
        cout << left << setw(10) << id << setw(15) << name << setw(10) << price << setw(10) << quantity << setw(15) << sellerName << endl;
    }

    file.close();
}

void updateProductQuantity(int productId, int newQuantity) 
{
    ifstream inFile("products.txt");
    ofstream outFile("temp.txt");
    bool found = false;

    int id, quantity;
    string name, sellerName;
    double price;

    while (inFile >> id >> name >> price >> quantity >> sellerName) 
    {
        if (id == productId) 
        {
            outFile << id << " " << name << " " << price << " " << newQuantity << " " << sellerName << endl;
            found = true;
        } 
        else 
            outFile << id << " " << name << " " << price << " " << quantity << " " << sellerName << endl;
    }

    inFile.close();
    outFile.close();

    remove("products.txt");
    rename("temp.txt", "products.txt");

    if (found)
        cout << "Quantity updated successfully.\n";
    else
        cout << "Product ID not found.\n";
}