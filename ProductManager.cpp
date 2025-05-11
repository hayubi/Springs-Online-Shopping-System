#include "ProductManager.h"
#include <fstream>
#include <iostream>
using namespace std;

void ProductManager::addProduct(const Product& product) 
{
    products.push_back(product);
    ofstream fout("products.txt", ios::app);
    if (fout.is_open()) 
    {
        fout << product.getId() << " "
             << product.getName() << " "
             << product.getPrice() << " "
             << product.getQuantity() << " "
             << product.sellerName << "\n";
        fout.close();
    } 
    else
        cerr << "Could not open products.txt to write product.\n";
}

void ProductManager::removeProduct(const string& name, const string& seller) 
{
    for (auto it = products.begin(); it != products.end(); ++it) 
    {
        if (it->getName() == name && it->sellerName == seller) 
        {
            products.erase(it);
            break;
        }
    }
}

void ProductManager::listProducts() const 
{
    ifstream fin("products.txt");
    if (!fin.is_open()) {
        cerr << "Could not open products.txt for reading.\n";
        return;
    }

    int id, quantity;
    string name, sellerName;
    double price;

    while (fin >> id >> name >> price >> quantity >> sellerName) 
    {
        cout << "ID: " << id << ", Name: " << name
             << ", Price: " << price << ", Quantity: " << quantity
             << ", Seller: " << sellerName << "\n";
    }

    fin.close();
}

void ProductManager::loadProductsFromFile() 
{
    ifstream file("products.txt");
    if (!file.is_open()) {
        cout << "Error loading products file!\n";
        return;
    }

    int id, quantity;
    double price;
    string name, seller;

    while (file >> id >> name >> price >> quantity >> seller) 
    {
        products.emplace_back(id, name, price, quantity, seller);
    }

    file.close();
}

void ProductManager::saveProductsToFile() 
{
    ofstream fout("products.txt");
    if (!fout.is_open()) {
        cerr << "Error: Unable to open products.txt for saving.\n";
        return;
    }

    for (const auto& p : products) 
    {
        fout << p.getId() << " "
             << p.getName() << " "
             << p.getPrice() << " "
             << p.getQuantity() << " "
             << p.sellerName << "\n";
    }

    fout.close();
}

Product* ProductManager::findProduct(int productId) 
{
    for (auto& product : products) 
    {
        if (product.getId() == productId) {
            return &product;
        }
    }
    return nullptr;
}

bool ProductManager::updateProductQuantities(int productId, int newQty, const string& sellerEmail) 
{
    for (auto& product : products) 
    {
        if (product.getId() == productId && product.sellerName == sellerEmail) 
        {
            product.setQuantity(newQty);
            saveProductsToFile();
            return true;
        }
    }
    return false;
}

bool ProductManager::updatebuyQuantities(int productId, int quantityToReduce, const string& sellerEmail) 
{
    ofstream tempFile("products_temp.txt");
    if (!tempFile.is_open()) {
        cerr << "Error opening temporary file.\n";
        return false;
    }

    bool updated = false;
    for (auto& product : products) 
    {
        if (product.getId() == productId && product.sellerName == sellerEmail) 
        {
            int newQuantity = product.getQuantity() - quantityToReduce;
            if (newQuantity >= 0) 
            {
                product.setQuantity(newQuantity);
                updated = true;
            } 
            else 
            {
                cerr << "Not enough stock for this product.\n";
                tempFile.close();
                return false;
            }
        }

        tempFile << product.getId() << " "
                 << product.getName() << " "
                 << product.getPrice() << " "
                 << product.getQuantity() << " "
                 << product.sellerName << "\n";
    }

    if (updated) 
    {
        tempFile.close();
        remove("products.txt");
        rename("products_temp.txt", "products.txt");
        cout << "Product quantities updated successfully.\n";
    } 
    else 
    {
        cerr << "Product not found or update failed.\n";
        remove("products_temp.txt");
    }

    return updated;
}

void ProductManager::generateReceipt(const string& customerEmail, const vector<Product>& cart) 
{
    ofstream fout("orders.txt", ios::app);
    double total = 0;

    fout << "Customer: " << customerEmail << "\n";
    fout << "Ordered Products:\n";

    cout << "\n===== Receipt =====\n";
    cout << "Customer: " << customerEmail << "\n";
    cout << "Products:\n";

    for (const auto& p : cart) 
    {
        double cost = p.getPrice() * p.getQuantity();
        total += cost;

        fout << "ID: " << p.getId()
             << ", Name: " << p.getName()
             << ", Qty: " << p.getQuantity()
             << ", Price: " << p.getPrice()
             << ", Seller: " << p.sellerName
             << ", Total: " << cost << "\n";

        cout << "ID: " << p.getId()
             << ", Name: " << p.getName()
             << ", Qty: " << p.getQuantity()
             << ", Price: " << p.getPrice()
             << ", Total: " << cost << "\n";

        updateProductQuantities(p.getId(), p.getQuantity(), p.sellerName);
    }

    double discount = 0.0;
    if (total > 10000) 
    {
        discount = total * 0.10;
        total -= discount;
        fout << "Discount Applied (10%): -" << discount << "\n";
        cout << "Discount Applied (10%): -" << discount << "\n";
    }

    fout << "Grand Total: " << total << "\n\n";
    fout.close();

    cout << "Grand Total: " << total << "\n";
    cout << "Receipt saved to orders.txt\n";
}

void ProductManager::listProductsInRange(double minPrice, double maxPrice) const 
{
    if (minPrice < 200) {
        cout << "Minimum price must be at least 200.\n";
        return;
    }

    bool found = false;
    for (const auto& product : products) 
    {
        if (product.getPrice() >= minPrice && product.getPrice() <= maxPrice) 
        {
            cout << "ID: " << product.getId() << ", Name: " << product.getName()
                 << ", Price: " << product.getPrice() << ", Quantity: " << product.getQuantity()
                 << ", Seller: " << product.sellerName << "\n";
            found = true;
        }
    }

    if (!found)
        cout << "No products found in this price range.\n";
}

void ProductManager::showProductsForSeller(const string& sellerEmail) const 
{
    bool found = false;
    cout << "\n===== PRODUCTS FOR SELLER: " << sellerEmail << " =====\n";
    for (const auto& product : products) 
    {
        if (product.sellerName == sellerEmail) 
        {
            cout << "ID: " << product.getId()
                 << ", Name: " << product.getName()
                 << ", Price: $" << product.getPrice()
                 << ", Quantity: " << product.getQuantity() << "\n";
            found = true;
        }
    }
    if (!found)
        cout << "No products found for this seller.\n";
}