#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Seller;
class Customer;

class User
{
    protected:
        string name;
        int id;
        string email;

    public:
        User() : name(""), id(0), email(""){}
        User(string n, int ID, string e): name(n), id(ID), email(e) {}

        virtual void Register() {};
};


class Product //make product a friend class
{
    private:
        int productID;
        float price;
        string description;
        int quantity;

    public:
        Product() : productID(0), price(0.0), description(""), quantity(0) {}
        Product(int id, float p, string desc, int qty) : productID(id), price(p), description(desc), quantity(qty) {}
        
        void display() const
        {
            cout << "Product ID: " << productID << endl;
            cout << "Price: Rs" << price << endl;
            cout << "Description: " << description << endl;
            cout << "Quantity: " << quantity << endl;
        }

        //Getters
        int getProdID() { return productID; }
        float getPrice() { return price; }
        string getDesc() { return description; }
        int getQuantity() { return quantity; }

        //Setters
        void setprice(float p) { price = p; }
        void setdesc(string desc) { description = desc; }
        void setqty(int qty) { quantity = qty; }

        friend class Seller; //seller can access product

};

class Seller : public User
{
    private:
        vector<Product> products;
        //sellers array

    public:
        Seller() {}
        Seller(string n, int ID, string e) : User(n, ID, e) {}

        void Register() override
        {
            cout << "\n-----------------------------------------\n";
            cout << " Enter the following details for Seller: \n  ID: ";
            cin >> id;
            cout << "  Name: ";
            cin >> name;
            cout << "  Email: ";
            cin >> email;
        }

        void addProduct(int ID, float price, string description, int quantity)
        {
            Product p(ID, price, description, quantity);
            products.push_back(p);
            cout << "Product " << ID << " added." << endl;
        }

        void deleteProduct(int ID)
        {
            for (auto it = products.begin(); it != products.end(); ++it) 
            {
                if (it->productID == ID) 
                {
                    products.erase(it);
                    cout << "Product " << ID << " deleted." << endl;
                    return;
                }
            }  
            cout << "Product ID " << ID << " not found" << endl;
        }

        void updateProductPrice(int ID, float p)
        {
            for (int i=0; i<products.size(); i++)
            {
                if (products[i].productID == ID)
                {
                    products[i].setprice(p);
                    cout << "Product " << ID << " price updated." << endl;
                    return;
                }
            }
            cout << "Product " << ID << " not found." << endl;
        }

        void updateProductDesc(int ID, string d)
        {
            for (int i=0; i<products.size(); i++)
            {
                if (products[i].productID == ID)
                {
                    products[i].setdesc(d);
                    cout << "Product " << ID << " description updated." << endl;
                    return;
                }
            }
            cout << "Product " << ID << " not found." << endl;
        }

        void updateProductQty(int ID, int q)
        {
            for (int i=0; i<products.size(); i++)
            {
                if (products[i].productID == ID)
                {
                    products[i].setqty(q);
                    cout << "Product " << ID << " quantity updated." << endl;
                    return;
                }
            }
            cout << "Product " << ID << " not found." << endl;
        }

        void viewProductDetails(int ID) const
        {
            for (int i=0; i<products.size(); i++)
            {
                if (products[i].productID == ID)
                {
                    cout << "Product Details for " << ID << endl;
                    products[i].display();
                    return;
                }
            }
            cout << "Product " << ID << " not found." << endl;
        }

        void viewAllProducts() const
        {
            if (products.empty())
            {
                cout << "No products to display." << endl;
                return;
            }
            else
            {
                cout << "----All Products----" << endl;
                for (int i=0; i<products.size(); i++)
                {
                    products[i].display();
                    cout << "------------" << endl;
                }
            }
        }
};


class Customer : public User
{
    private:

    public:
        Customer() {}
        Customer(string n, int ID, string e) : User(n, ID, e) {}

        void Register() override
        {
            cout << "\n-------------------------------------------\n";
            cout << " Enter the following details for Customer: \n  ID: ";
            cin >> id;
            cout << "  Name: ";
            cin >> name;
            cout << "  Email: ";
            cin >> email;
        }   
};


class Cart
{

};


class Shoppingsystem
{
    private:
        Seller sellers;
        Customer customers;
        Product products;

    public:
        Shoppingsystem() {}
        
};


int main()
{ 
    Seller s;
    Customer c;

    string choice; //made it string and not int bcz if anything other than integer is entered,,,it was working giving infinite couts
    do
    {
        cout << "\nAre you interested in\n(1) Buying\n(2) Selling? \n Option: ";
        cin >> choice;
        if (choice == "1")
            c.Register();
        else if (choice == "2")
            s.Register();
        else
            cout << "Invalid choice. Please only select option 1 or 2." << endl;
    } while (choice != "1" && choice != "2");
}
