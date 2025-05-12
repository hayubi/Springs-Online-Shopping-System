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
        Customer(const string& n, const string& c, const string& add, const string& mail, const string& pass, int pts = 0);
        void displayMenu() const override;

        void addToCart(const Product&);
        void viewCart() const;
        void checkout();
        void buy_product();
};

#endif
