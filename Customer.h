#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "User.h"
#include "Cart.h"
using namespace std;

class Customer : public User 
{
    private:
        Cart cart;
        int points;
        
    public:
        Customer(string, string, int pts = 0);
        void addToCart(const Product&);
        void viewCart() const;
        void checkout();
        void displayMenu() const override;
        void buy_product();
};

#endif