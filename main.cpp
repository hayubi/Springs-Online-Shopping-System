// g++ main.cpp User.cpp Customer.cpp Seller.cpp Product.cpp Cart.cpp ProductManager.cpp -o ShoppingSystem.exe
// ./ShoppingSystem.exe

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
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
        cout << "🎉 You received a 10% discount! You saved $" << discount << "\n";
        return total - discount;
    }
    return total;
}

bool validateLogin(const string& filename, const string& email, const string& password) 
{
    ifstream file(filename);
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
    string storedEmail, storedPassword;
    while (fin >> storedEmail >> storedPassword) 
    {
        if (storedEmail == email) return false;
    }
    return true;
}

void saveUser(const string& filename, const string& email, const string& password) 
{
    ofstream fout(filename, ios::app);
    fout << email << " " << password << "\n";
    fout.close();
}

void handleCustomerSession(Customer& customer, ProductManager& pm) 
{
    vector<Product> cart;
    int choice;

    do 
    {
        cout << "\n===== CUSTOMER MENU =====\n"
             << "1. View Products\n"
             << "2. Add to Cart\n"
             << "3. View Cart\n"
             << "4. Checkout\n"
             << "5. Set Price Filter (Min $200)\n"
             << "0. Logout\n"
             << "Choice: ";
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
        cout << "\n===== SELLER MENU =====\n"
             << "1. Add Product\n"
             << "2. Update Product\n"
             << "3. Remove Product\n"
             << "4. View My Products\n"
             << "0. Logout\n"
             << "Choice: ";
        cin >> choice;

        if (choice == 1) 
        {
            int id, qty;
            string name;
            double price;

            cout << "Enter product ID: ";
            cin >> id;
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

        if (mainChoice == 0) break;

        string email, password;
        cout << "Email: ";
        cin >> email;
        cout << "Password: ";
        cin >> password;

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

            saveUser("users.txt", email, password);
            saveUser(role == 1 ? "customers.txt" : "sellers.txt", email, password);
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
            Customer customer(email, password);
            handleCustomerSession(customer, productManager);
        } 
        else 
        {
            Seller seller(email, password, productManager);
            handleSellerSession(seller, productManager);
        }
    }

    productManager.saveProductsToFile();
    cout << "Goodbye!\n";
}