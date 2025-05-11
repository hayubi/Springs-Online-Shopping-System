#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include <vector>
#include <string>
#include "Product.h"
#include <fstream>
#include <iostream>
using namespace std;

class ProductManager 
{
    private:
        vector<Product> products;

    public:
        void addProduct(const Product& product);
        void removeProduct(const string& name, const string& seller);
        void updateQuantity(const string& name, const string& seller, int newQuantity);
        void listProducts() const;

        void loadProductsFromFile();
        void saveProductsToFile();
        Product* findProduct(int productId);

        bool updatebuyQuantities(int productId, int newQty, const string& sellerEmail);
        bool updateProductQuantities(int productId, int newQty, const string& sellerEmail);
        void generateReceipt(const string& customerEmail, const vector<Product>& cart);
        void listProductsInRange(double minPrice, double maxPrice) const;
        void showProductsForSeller(const string& sellerEmail) const;
};

#endif