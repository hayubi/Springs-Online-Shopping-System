// In Seller.h

#ifndef SELLER_H
#define SELLER_H
#include "User.h"
#include "Product.h"
#include <vector>

// Function prototypes from ProductManager.cpp
void displayAllProducts();
void updateProductQuantity(int productId, int newQuantity);

class Seller : public User 
{
    private:
        std::vector<Product> products;
    public:
        Seller(std::string, std::string);
        void addProduct(const Product&);
        void viewProducts() const;
        void displayMenu() const override;  // ✅ Correct

        const std::vector<Product>& getProducts() const;
};

#endif