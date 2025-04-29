#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Seller;
class Customer;

class User {
protected:
    string name;
    int id;
    string email;

public:
    User() : name(""), id(0), email("") {}
    User(string n, int ID, string e) : name(n), id(ID), email(e) {}

    virtual void Register() {}
};

class Product {
private:
    int productID;
    float price;
    string description;
    int quantity;

public:
    Product() : productID(0), price(0.0), description(""), quantity(0) {}
    Product(int id, float p, string desc, int qty) : productID(id), price(p), description(desc), quantity(qty) {}

    void addProduct(int id, float price, string description, int quantity) {}
    void deleteProduct(int id, float price, string description, int quantity) {}
    void updateProductPrice(int id, float price) {}
    void updateProductDesc(int id, string description) {}
    void viewProductDetails() {}
    void viewAllProducts() {}

    int getProdID() const { return productID; }
    float getPrice() const { return price; }
    string getDesc() const { return description; }
    int getQuantity() const { return quantity; }

    void setProdID(int pid) { productID = pid; }
    void setprice(float p) { price = p; }
    void setdesc(string desc) { description = desc; }
    void setqty(int qty) { quantity = qty; }

    void display() const {
        cout << "Product ID: " << productID << ", Price: $" << price
             << ", Description: " << description << ", Quantity: " << quantity << endl;
    }
};

class Seller : public User {
public:
    Seller() {}
    Seller(string n, int ID, string e) : User(n, ID, e) {}

    void Register() override {
        cout << "\n-----------------------------------------\n";
        cout << " Enter the following details for Seller: \n  ID: ";
        cin >> id;
        cout << "  Name: ";
        cin >> name;
        cout << "  Email: ";
        cin >> email;
    }

    friend class Product;
};

class Customer : public User {
private:
    double phone_num;
    string address;
    vector<Product> productItems;
    static vector<int> registeredCustomerIDs;
    static map<int, int> customerPoints;

public:
    Customer() : phone_num(0.0), address("") {}
    Customer(double pnum, string adrs) : phone_num(pnum), address(adrs) {}
    Customer(string n, int ID, string e) : User(n, ID, e), phone_num(0.0), address("") {}

    void Register() override {
        cout << "\n-------------------------------------------\n";
        cout << "Enter the following details for Customer:\n";
        cout << "ID: ";
        cin >> id;
        cout << "Name: ";
        cin >> name;
        cout << "Email: ";
        cin >> email;
        cout << "Address: ";
        cin.ignore();
        getline(cin, address);
        cout << "Phone Number: ";
        cin >> phone_num;

        registeredCustomerIDs.push_back(id);
        cout << "Customer registered successfully.\n";
    }

    static void showAllCustomerIDs() {
        cout << "Registered Customer IDs:\n";
        for (int cid : registeredCustomerIDs) {
            cout << " - " << cid << "\n";
        }
    }

    double getPhoneNum() const { return phone_num; }
    string getAddress() const { return address; }
    vector<Product>& getProductItems() { return productItems; }

    void setPhoneNum(double num) { phone_num = num; }
    void setAddress(string addr) { address = addr; }
    void addProductToCart(Product p) { productItems.push_back(p); }

    void viewProducts() {
        for (const Product& p : productItems) {
            p.display();
        }
    }

    friend void pointdiscount(class Shoppingsystem pointdisc);
};

vector<int> Customer::registeredCustomerIDs;
map<int, int> Customer::customerPoints;

class ShoppingCart {
private:
    vector<Product> cartItems;

public:
    void addProduct(const Product& p) {
        cartItems.push_back(p);
    }

    void removeProduct(int productId) {
        for (auto it = cartItems.begin(); it != cartItems.end(); ++it) {
            if (it->getProdID() == productId) {
                cout << "Removed product with ID: " << it->getProdID() << endl;
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
    friend void pointdiscount(Shoppingsystem pointdisc);

    float calculateBill(float price, int quantity, int productID) {
        Total = price * quantity;
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
//HAFSA YAHAN SE CHECK KARO
void pointdiscount(Shoppingsystem pointdisc) {
    const float MIN_BILL_FOR_POINTS = 100.0;
    const float MAX_DISCOUNT = 50.0;
    const float POINTS_PER_100 = 50;
    const float DISCOUNT_PER_50_POINTS = 1.0f / 20.0f;

    float bill = pointdisc.getTotal();
    int customerID = pointdisc.customers.id;

    bool isRegistered = false;
    for (int id : Customer::registeredCustomerIDs) {
        if (id == customerID) {
            isRegistered = true;
            break;
        }
    }

    if (!isRegistered) {
        cout << "Customer is not registered. No points or discount applicable.\n";
        pointdisc.setNetTotal(bill);
        return;
    }

    int currentPoints = Customer::customerPoints[customerID];
    cout << "Your current points: " << currentPoints << "\n";

    int pointsEarned = 0;
    if (bill >= MIN_BILL_FOR_POINTS) {
        pointsEarned = static_cast<int>(bill / 100) * POINTS_PER_100;
        cout << "You earned " << pointsEarned << " new points from this purchase.\n";
    }

    char choice;
    cout << "Would you like to use your points now for a discount? (y/n): ";
    cin >> choice;

    float discount = 0.0f;
    if (tolower(choice) == 'y' && currentPoints >= 50) {
        int applicablePoints = (currentPoints / 50) * 50;
        discount = bill * DISCOUNT_PER_50_POINTS * (applicablePoints / 50);
        if (discount > MAX_DISCOUNT) {
            discount = MAX_DISCOUNT;
            applicablePoints = static_cast<int>((MAX_DISCOUNT / (bill * DISCOUNT_PER_50_POINTS)) * 50);
        }
        bill -= discount;
        currentPoints -= applicablePoints;
        cout << "Discount of $" << discount << " applied using " << applicablePoints << " points.\n";
    }

    if (pointsEarned > 0) {
        currentPoints += pointsEarned;
    }

    Customer::customerPoints[customerID] = currentPoints;
    pointdisc.setNetTotal(bill);

    cout << "Final bill after discount (if any): $" << bill << "\n";
    cout << "Remaining points: " << currentPoints << "\n";
}

int main() {
    Seller s;
    Customer c;
    string choice;

    do {
        cout << "\nAre you interested in\n(1) Buying\n(2) Selling? \n Option: ";
        cin >> choice;
        if (choice == "1")
            c.Register();
        else if (choice == "2")
            s.Register();
        else
            cout << "Invalid choice. Please only select option 1 or 2." << endl;
    } while (choice != "1" && choice != "2");

    return 0;
}

