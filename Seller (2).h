#ifndef SELLER_H
#define SELLER_H
#include "User.h"
#include "Product.h"
#include <vector>
class Seller : public User {
    std::vector<Product> products;
public:
    Seller(std::string, std::string);
    void addProduct(const Product&);
    void viewProducts() const;
    void display() const override;
    const std::vector<Product>& getProducts() const;
    void addProductToFile(int id, const std::string& name, double price, int quantity, const std::string& sellerName);
void displayAllProducts();
void updateProductQuantity(int productId, int newQuantity);

};
#endif
