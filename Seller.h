#ifndef SELLER_H
#define SELLER_H
#include "User.h"
#include "Product.h"
#include "ProductManager.h"
#include <vector>
using namespace std;

class Seller : public User 
{
    private:
        ProductManager& productManager;

    public:
        Seller(const string& n, const string& c, const string& add, const string& mail, const string& pass, ProductManager& pm);
        virtual ~Seller();
        void displayMenu() const override;

        void addProduct();
        void removeProduct();
        void updateProduct();
};
#endif
