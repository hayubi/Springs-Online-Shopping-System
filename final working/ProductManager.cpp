#include "ProductManager.h"
#include <fstream>
#include <iostream>

void ProductManager::addProduct(const Product& product) {
    products.push_back(product); // Add to in-memory list

    // Append product to file
    std::ofstream fout("products.txt", std::ios::app);
    if (fout.is_open()) {
        fout << product.getId() << " "
             << product.getName() << " "
             << product.getPrice() << " "
             << product.getQuantity() << " "
             << product.sellerName << "\n";
        fout.close();
    } else {
        std::cerr << "❌ Could not open products.txt to write product.\n";
    }
}


void ProductManager::removeProduct(const std::string& name, const std::string& seller) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getName() == name && it->sellerName== seller) {
            products.erase(it);
            break;
        }
    }
}

void ProductManager::updateQuantity(const std::string& name, const std::string& seller, int newQuantity) {
    bool updated = false;
    
    // Update in memory
    for (auto& product : products) {
        if (product.getName() == name && product.sellerName == seller) {
            product.setQuantity(newQuantity);
            updated = true;
            break;
        }
    }

    // If updated in memory, save to file
    if (updated) {
        std::ofstream file("products.txt");  // or your actual file name
        if (file.is_open()) {
            for (const auto& product : products) {
                file << product.getName() << ","
                     << product.getPrice() << ","
                     << product.getQuantity() << ","
                     << product.sellerName << std::endl;
            }
            file.close();
        } else {
            std::cerr << "Error: Unable to open products.txt for writing." << std::endl;
        }
    }
}


void ProductManager::listProducts() const {
    std::ifstream fin("products.txt");
    if (!fin.is_open()) {
        std::cerr << "❌ Could not open products.txt for reading.\n";
        return;
    }

    int id, quantity;
    std::string name, sellerName;
    double price;

    while (fin >> id >> name >> price >> quantity >> sellerName) {
        std::cout << "ID: " << id << ", Name: " << name
                  << ", Price: " << price << ", Quantity: " << quantity
                  << ", Seller: " << sellerName << "\n";
    }

    fin.close();
}


void ProductManager::loadProductsFromFile() {
    std::ifstream file("products.txt");
    if (!file.is_open()) {
        std::cout << "Error loading products file!\n";
        return;
    }

    int id, quantity;
    double price;
    std::string name, seller;

    while (file >> id >> name >> price >> quantity >> seller) {
        products.emplace_back(id, name, price, quantity, seller);
    }

    file.close();
}

void ProductManager::saveProductsToFile() {
    std::ofstream fout("products.txt");
    for (const auto& p : products) {
        fout << p.getId() << " " << p.getName() << " "
             << p.getPrice() << " " << p.getQuantity() << " "
             << p.sellerName << "\n";
    }
    fout.close();
}


Product* ProductManager::findProduct(int productId) {
    for (auto& product : products) {
        if (product.getId() == productId) {
            return &product;
        }
    }
    return nullptr;  // Return nullptr if not found
}

bool ProductManager::updateProductQuantities(int productId, int newQty, const std::string& sellerEmail) {
    for (auto& product : products) {
        if (product.getId() == productId && product.sellerName == sellerEmail) {
            product.setQuantity(newQty);
            saveProductsToFile();  // Save updated products to file
            return true;  // Successfully updated
        }
    }
    return false;  // Product not found or not owned by seller
}

void ProductManager::generateReceipt(const std::string& customerEmail, const std::vector<Product>& cart) {
    std::ofstream fout("orders.txt", std::ios::app);
    double total = 0;

    fout << "Customer: " << customerEmail << "\n";
    fout << "Ordered Products:\n";

    std::cout << "\n===== Receipt =====\n";
    std::cout << "Customer: " << customerEmail << "\n";
    std::cout << "Products:\n";

    for (const auto& p : cart) {
        double cost = p.getPrice() * p.getQuantity();
        total += cost;

        fout << "ID: " << p.getId()
             << ", Name: " << p.getName()
             << ", Qty: " << p.getQuantity()
             << ", Price: " << p.getPrice()
             << ", Seller: " << p.sellerName
             << ", Total: " << cost << "\n";

        std::cout << "ID: " << p.getId()
                  << ", Name: " << p.getName()
                  << ", Qty: " << p.getQuantity()
                  << ", Price: " << p.getPrice()
                  << ", Total: " << cost << "\n";

        // Update the product quantity for each product in the cart
        updateProductQuantities(p.getId(), p.getQuantity(), p.sellerName);
    }

    fout << "Grand Total: " << total << "\n\n";
    fout.close();

    std::cout << "Grand Total: " << total << "\n";
    std::cout << "Receipt saved to orders.txt\n";
}

