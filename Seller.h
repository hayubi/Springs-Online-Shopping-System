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
        Seller(string name, string email, ProductManager& pm);
        virtual ~Seller();
        void addProduct();
        void removeProduct();
        void updateProduct();
        void displayMenu() const override;
};

#endif
