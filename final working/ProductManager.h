#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include <vector>
#include <string>
#include "Product.h"
#include <fstream>
#include <iostream>

class ProductManager {
private:
    std::vector<Product> products;

public:
    // Add product to the list
    void addProduct(const Product& product);

    // Remove product by name and seller
    void removeProduct(const std::string& name, const std::string& seller);

    // Update the quantity of a product by its name and seller
    void updateQuantity(const std::string& name, const std::string& seller, int newQuantity);

    // List all products
    void listProducts() const;

    // Load products from a file
    void loadProductsFromFile();

    // Save products to a file
    void saveProductsToFile();

    // Find a product by its ID
    Product* findProduct(int productId);

    // Update the product quantities after an order is placed
bool updateProductQuantities(int productId, int newQty, const std::string& sellerEmail);

    // Generate a receipt for the customer
    void generateReceipt(const std::string& customerEmail, const std::vector<Product>& cart);
};

#endif
