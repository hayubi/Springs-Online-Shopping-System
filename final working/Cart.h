#ifndef CART_H
#define CART_H
#include "Product.h"
#include <vector>

class Cart 
{
    private:
        std::vector<Product> items;
    public:
        void addItem(const Product&);
        void viewCart() const;
        double getTotal() const;
        void clear();
        void removeItem(const std::string& name);
        void checkout();


};

#endif
