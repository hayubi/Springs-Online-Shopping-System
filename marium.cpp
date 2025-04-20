//shoppingcart class and functions using product class functions, change to as product class is friend


class Customer : public User {
    private:
        double phone_num;
        string address;
        vector<Product> productItems;
    
    public:
        Customer() : phone_num(0.0), address("") {}  
    
        Customer(double pnum, string adrs) : phone_num(pnum), address(adrs) {}
    
        Customer(string n, int ID, string e) : User(n, ID, e), phone_num(0.0), address("") {}
    
        void Register() override {
            cout << "\n-------------------------------------------\n";
            cout << " Enter the following details for Customer: \n  ID: ";
            cin >> id;
            cout << "  Name: ";
            cin >> name;
            cout << "  Email: ";
            cin >> email;
            cout<<"  Address: ";
            cin>>address;
            cout<<"  Phone Number: ";
            cin>>phone_num;

        }
    
        void viewProducts(int productID, float price) {  //also can add to sellerfunctions class directly
            for (size_t i = 0; i < productItems.size(); i++) {
                cout << "Product ID: " << productItems[i].getProdID() << endl;
                cout << "Price: $" << productItems[i].getPrice() << endl;
                cout << "Description: " << productItems[i].getDesc() << endl;
                cout << "Quantity: " << productItems[i].getQuantity() << endl;
            }
        }
     
        double getPhoneNum() const { return phone_num; }
        string getAddress() const { return address; }
        vector<Product>& getProductItems() { return productItems; }
     
        void setPhoneNum(double num) { phone_num = num; }
        void setAddress(string addr) { address = addr; }
        void addProductToCart(Product p) { productItems.push_back(p); }
    };

class ShoppingCart {
private:
    vector<Product> cartItems;//to work with cart item arrays

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

void Filter(float min_p, float max_p) {
    const int min = 5;
    const int max = 500;

    cout << "Enter the minimum filtering price (min $" << min << "): ";
    cin >> min_p;
    if (min_p < min) {
        cout << "Enter a value higher than $" << min << endl;
        return;
    }

    cout << "Enter the maximum filtering price (max $" << max << "): ";
    cin >> max_p;
    if (max_p > max) {
        cout << "Enter a value lower than $" << max << endl;
        return;
    }

    cout << "Filtering products between $" << min_p << " and $" << max_p << "...\n";
}

class Shoppingsystem {
private:
    float Total;
    float NetTotal;
    Seller sellers;
    Customer customers;
    Product products;

public:
    Shoppingsystem() : Total(0), NetTotal(0) {}  
    Shoppingsystem(float tot, float nTot) : Total(tot), NetTotal(nTot) {}

    float calculateBill(float price, int quantity, int productID) { //CAN GO IN CART CLASS TOO
        Total = 0; 
        Total = (price * quantity);
        return Total;
    }
 
    float getTotal() const { return Total; }
    float getNetTotal() const { return NetTotal; }
    void setTotal(float t) { Total = t; }
    void setNetTotal(float nt) { NetTotal = nt; }

    Seller& getSeller() { return sellers; }
    Customer& getCustomer() { return customers; }
    Product& getProduct() { return products; }
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
