//shoppingcart class and functions using product class functions, change to as product class is friend

class ShoppingCart {
private:
    vector<Product> cartItems;

public:
    void display() const {
    cout << "Product ID: " << id << ", Name: " << name << ", Price: $" << price << endl;
}
void removeProduct(int productId) {
    for (auto it = cartItems.begin(); it != cartItems.end(); ++it) {
        if (it->getId() == productId) {
            cout << "Removed product: " << it->getName() << endl;
            cartItems.erase(it);
            return;
        }
    }
    cout << "Product not found in cart.\n";
}

void viewCart() const {
    if (cartItems.empty()) {
        cout << "Cart is empty.\n";
        return;
    }
    cout << "Shopping Cart Contents:\n";
    for (const auto& item : cartItems) {
        item.display();
    }
}

void checkout() {
    double total = 0;
    cout << "\nChecking out the following items:\n";
    for (const auto& item : cartItems) {
        item.display();
        total += item.getPrice();
    }
    cout << "Total amount: $" << total << endl;
    cartItems.clear();
    cout << "Checkout complete. Cart is now empty.\n";
}

};

int main(){
  
ShoppingCart cart;
cart.addProduct(p1);
cart.addProduct(p2);
cart.viewCart();

cart.removeProduct(2);
cart.viewCart();

cart.addProduct(p3);
cart.checkout();
cart.viewCart();

return 0;
}
