// g++ main.cpp User.cpp Customer.cpp Seller.cpp Product.cpp Cart.cpp ProductManager.cpp -o ShoppingSystem.exe
// ./ShoppingSystem.exe

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <exception>
#include "User.h"
#include "Customer.h"
#include "Seller.h"
#include "ProductManager.h"
#include "Product.h"
using namespace std;

double applyDiscount(double total) 
{
    if (total > 500) 
    {
        double discount = total * 10;
        cout << "You received a 10% discount! You saved $" << discount << "\n";
        return total - discount;
    }
    return total;
}

bool validateLogin(const string& filename, const string& email, const string& password) 
{
    ifstream file(filename);
    if (!file.is_open()) throw runtime_error("Could not open file: " + filename);
    string fileEmail, filePassword;
    while (file >> fileEmail >> filePassword) 
    {
        if (fileEmail == email && filePassword == password)
            return true;
    }
    return false;
}

bool isValidEmailFormat(const string& email) 
{
    int atCount = 0;
    for (char c : email) 
    {
        if (c == '@') atCount++;
        else if (!islower(c) && !isdigit(c) && c != '.' && c != '_')
            return false;
    }
    return atCount == 1 && email.find('@') != 0 && email.find('@') != email.length() - 1;
}

bool isEmailUnique(const string& filename, const string& email) 
{
    ifstream fin(filename);
    if (!fin.is_open()) throw runtime_error("Could not open file: " + filename);
    string storedEmail, storedPassword;
    while (fin >> storedEmail >> storedPassword) 
    {
        if (storedEmail == email) return false;
    }
    return true;
}

void saveUser(const string& filename, const string& email, const string& password, const string& name, const string& contact, const string& address) 
{
    ofstream fout(filename, ios::app);
    if (!fout.is_open()) 
        throw runtime_error("Could not open file to save user: " + filename);
    fout << email << " " << password << " " << name << " " << contact << " " << address << "\n";
    fout.close();
}

bool loadUserDetails(const string& filename, const string& email, const string& password, string& name, string& contact, string& address) 
{
    ifstream fin(filename);
    if (!fin.is_open()) 
        throw runtime_error("Could not open file: " + filename);

    string fileEmail, filePassword, fileName, fileContact, fileAddress;
    while (fin >> fileEmail >> filePassword >> fileName >> fileContact >> fileAddress) 
    {
        if (fileEmail == email && filePassword == password) 
        {
            name = fileName;
            contact = fileContact;
            address = fileAddress;
            return true;
        }
    }
    return false;
}

void handleCustomerSession(Customer& customer, ProductManager& pm) 
{
    vector<Product> cart;
    int choice;

    do 
    {
        customer.displayMenu();
        cin >> choice;

        if (choice == 1)
            pm.listProducts();

        else if (choice == 2) 
        {
            int pid, qty;
            cout << "Enter product ID: ";
            cin >> pid;
            Product* p = pm.findProduct(pid);
            if (p) 
            {
                cout << "Enter quantity (Available: " << p->getQuantity() << "): ";
                cin >> qty;
                if (qty > 0 && qty <= p->getQuantity()) 
                {
                    cart.emplace_back(p->getId(), p->getName(), p->getPrice(), qty, p->sellerName);
                    cout << "Added to cart.\n";
                } 
                else
                    cout << "Invalid quantity.\n";
            } 
            else
                cout << "Product not found.\n";
        }

        else if (choice == 3) 
        {
            if (cart.empty())
                cout << "Cart is empty.\n";
            else 
            {
                double total = 0;
                cout << "\n===== YOUR CART =====\n";
                for (const auto& item : cart) 
                {
                    double itemTotal = item.getPrice() * item.getQuantity();
                    cout << item.getName() << " x" << item.getQuantity() 
                         << " @ $" << item.getPrice() << " = $" << itemTotal << "\n";
                    total += itemTotal;
                }
                cout << "TOTAL: $" << total << "\n";
            }
        }

        else if (choice == 4) 
        {
            if (cart.empty()) 
                cout << "Cart is empty.\n";
            else 
            {
                for (auto& item : cart) 
                {
                    Product* p = pm.findProduct(item.getId());
                    if (p)
                        pm.updatebuyQuantities(item.id, item.quantity,item.sellerName);
                }
                pm.saveProductsToFile();
                pm.generateReceipt(customer.getEmail(), cart);
                cart.clear();
            }
        }

        else if (choice == 5) 
        {
            double minPrice,maxPrice;
            cout << "Enter minimum price to filter (e.g., 200): ";
            cin >> minPrice;
            cout << "Enter maxmum price to filter: ";
            cin >> maxPrice;
            pm.listProductsInRange(minPrice,maxPrice);
        }

    } while (choice != 0);
}

void handleSellerSession(Seller& seller, ProductManager& pm) 
{
    int choice;
    do 
    {
        seller.displayMenu();
        cin >> choice;

        if (choice == 1) 
        {
            int id, qty;
            string name;
            double price;
            while(true){

            cout << "Enter product ID: ";
            cin >> id;
            if (pm.isDuplicateID(id)) {
            cout << "This product ID already exists. Please enter a unique ID.\n";
             }
             else {
                break;
             } 
             // or ask again 
            }
            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter price: $";
            cin >> price;
            cout << "Enter quantity: ";
            cin >> qty;

            pm.addProduct(Product(id, name, price, qty, seller.getEmail()));
        }
        else if (choice == 2) 
        {
            int id, newQty;
            cout << "Enter product ID to update: ";
            cin >> id;
            cout << "Enter new quantity: ";
            cin >> newQty;
            pm.updateProductQuantities(id, newQty, seller.getEmail());
        }
        else if (choice == 3) 
        {
            string name;
            cout << "Enter product name to remove: ";
            cin >> name;
            pm.removeProduct(name, seller.getEmail());
        }
        else if (choice == 4) 
        {
            pm.showProductsForSeller(seller.getEmail());
        }
        else if (choice == 0) 
        {
            cout << "Logging out...\n";
            break;
        }
        else 
        {
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

int main() 
{
    try 
    {
        ProductManager productManager;
        productManager.loadProductsFromFile();

        while (true) 
        {
            cout << "\n===== MAIN MENU =====\n"
                 << "1. Login\n"
                 << "2. Register\n"
                 << "0. Exit\n"
                 << "Choice: ";

            int mainChoice;
            cin >> mainChoice;
            cin.ignore(); // Add this to discard leftover newline before getline

            if (mainChoice == 0) break;

            string name, contact, address, email, password;
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Contact: ";
            getline(cin, contact);
            cout << "Enter Address: ";
            getline(cin, address);
            cout << "Enter Email: ";
            getline(cin, email);
            cout << "Enter Password: ";
            getline(cin, password);

            if (mainChoice == 2) 
            {
                if (!isValidEmailFormat(email)) 
                {
                    cout << "Invalid email format.\n";
                    continue;
                }
                if (!isEmailUnique("users.txt", email)) 
                {
                    cout << "Email already exists.\n";
                    continue;
                }

                

                int role;
                cout << "Register as:\n1. Customer\n2. Seller\nChoice: ";
                cin >> role;

                saveUser("users.txt", email, password, name, contact, address);
                saveUser(role == 1 ? "customers.txt" : "sellers.txt", email, password, name, contact, address);

                cout << "Registration successful.\n";
                continue;
            }

            int role;
            if (validateLogin("customers.txt", email, password)) 
                role = 1;
            else if (validateLogin("sellers.txt", email, password)) 
                role = 2;

            else 
            {
                cout << "Invalid credentials.\n";
                continue;
            }

            if (role == 1) 
            {
                Customer customer(name, contact, address, email, password);
                handleCustomerSession(customer, productManager);
            } 
            else 
            {
                Seller seller(name, contact, address, email, password, productManager);
                handleSellerSession(seller, productManager);
            }

        }

        productManager.saveProductsToFile();
        cout << "Goodbye!\n";
    }
    catch (const exception& ex) 
    {
        cerr << "Exception: " << ex.what() << endl;
    }
    catch (...) 
    {
        cerr << "Unknown error occurred!" << endl;
    }
}
