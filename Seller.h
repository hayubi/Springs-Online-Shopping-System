#ifndef SELLER_H
#define SELLER_H
#include "User.h"
#include "Product.h"
#include "ProductManager.h"
#include <vector>
using namespace std;

void displayAllProducts();
void updateProductQuantity(int productId, int newQuantity);

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
        void viewProducts() const;
        void displayMenu() const override;
};

#endif