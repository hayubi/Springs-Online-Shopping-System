#include <iostream>
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
    private:

    public:
        Seller() {}

        void Register() override
        {
            cout << "cust";
        }
};


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
            cout << "Invalid choice. Please select option 1 or 2." << endl;
    } while (choice != 1 && choice != 2);


}
