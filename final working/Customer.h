#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "User.h"
#include "Cart.h"

class Customer : public User 
{
    private:
        Cart cart;
        int points;
        
    public:
        Customer(std::string, std::string, int pts = 0);
        void addToCart(const Product&);
        void viewCart() const;
        void checkout();
        void displayMenu() const override;  // ✅ Correct
        void buy_product();
};

#endif
