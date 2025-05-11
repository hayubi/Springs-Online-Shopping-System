#ifndef CART_H
#define CART_H
#include "Product.h"
#include <vector>
using namespace std;

class Cart 
{
    private:
        vector<Product> items;
    public:
        void addItem(const Product&);
        void viewCart() const;
        double getTotal() const;
        void clear();
        void removeItem(const string& name);
        void checkout();
};

#endif