#include <iostream>
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

        virtual void Register();
};


class Seller : public User
{
    protected:
        int sellerID;
        string name;
        string email;
        //sellers array

    public:
        Seller() {}

        void Register() override
        {
            cout << "cust";
        }
};

class Product : public Seller //make product a friend class
{
    private:
        int productID;
        float price;
        string description;
        int quantity;
        //products array
        //static int totalproducts;
        //int productcount;

    public:
        Product() : productID(0), price(0.0), description(""), quantity(0) {}
        Product(int id, float p, string desc, int qty) : productID(id), price(p), description(desc), quantity(qty) {}

        void addProduct(int id, float price, string description, int quantity)
        {
            
        }

        void deleteProduct(int id, float price, string description, int quantity)
        {

        }

        void updateProductPrice(int id, float price)
        {

        }

        void updateProductDesc(int id, string description)
        {

        }

        void viewProductDetails()
        {

        }

        void viewAllProducts()
        {

        }

        //Getters
        int getProdID() { return productID; }
        float getPrice() { return price; }
        string getDesc() { return description; }
        int getQuantity() { return quantity; }

        //Setters
        void setProdID(int pid) { productID = pid; }
        void setprice(float p) { price = p; }
        void setdesc(int desc) { description = desc; }
        void setqty(int qty) { quantity = qty; }

}


class Customer : public User
{
    private:

    public:
        Customer() {}

        void Register() override
        {
            cout << "cust";
        }      
};



int main()
{ 
    Seller s;
    Customer c;

    int choice;
    do
    {
        cout << "Are you interested in\n(1) Buying\n(2) Selling? ";
        cin >> choice;
        if (choice == 1)
            c.Register();
        else if (choice == 2)
            s.Register();
        else
            cout << "Invalid choice. Please only select option 1 or 2." << endl;
    } while (choice != 1 && choice != 2);
}
