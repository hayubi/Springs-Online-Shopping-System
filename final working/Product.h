#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <iostream>
using namespace std;

class Product 
{
    public:
        int id;
        std::string name;
        double price;
        int quantity;
        std::string sellerName;

        Product() = default;
        Product(int id, std::string name, double price, int quantity, std::string seller);

        void display() const;
        int getId() const;
        std::string getName() const;
        int getQuantity() const;
        friend void addProductToFile(const Product& product);
        
         void setQuantity(int newQuantity);
         double getPrice()const;

};

#endif