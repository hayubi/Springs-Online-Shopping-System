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
template<typename T>
void handleException(const T& msg) 
{
    std::cerr << "Error: " << msg << "\n";
}

bool validateLogin(const std::string& filename, const std::string& email, const std::string& password)
{
    std::ifstream file(filename);
    std::string fileEmail, filePassword;
    while (file >> fileEmail >> filePassword) 
    {
        if (fileEmail == email && filePassword == password)
            return true;
    }
    return false;
}

// Email validation: lowercase, digits, '_', '.', and one '@'
bool isValidEmailFormat(const std::string& email) {
    int atCount = 0;
    for (char c : email) {
        if (c == '@') atCount++;
        else if (!std::islower(c) && !std::isdigit(c) && c != '.' && c != '_')
            return false;
    }
    return atCount == 1 && email.find('@') != 0 && email.find('@') != email.length() - 1;
}

// Check format and uniqueness
bool isValidEmailAndUnique(const std::string& filename, const std::string& email) {
    if (!isValidEmailFormat(email)) {
        std::cout << "❌ Invalid email format.\n";
        return false;
    }
    std::ifstream fin(filename);
    std::string storedEmail, storedPassword;
    while (fin >> storedEmail >> storedPassword) {
        if (storedEmail == email) {
            std::cout << "❌ Email already exists.\n";
            return false;
        }
    }
    return true;
}



void saveUser(const std::string& filename, const std::string& email, const std::string& password) {
    std::ofstream fout(filename, std::ios::app);
    fout << email << " " << password << "\n";
    fout.close();
}

int main() {
    ProductManager productManager;
    productManager.loadProductsFromFile();

    int choice;
    std::cout << "1. Signup\n2. Login\nEnter choice: ";
    std::cin >> choice;

    std::string email, password;
    std::cout << "Enter Email: ";
    std::cin >> email;
    std::cout << "Enter Password: ";
    std::cin >> password;

    int role;
    std::cout << "1. Customer\n2. Seller\nSelect Role: ";
    std::cin >> role;

    if (choice == 1) {
        if (!isValidEmailAndUnique("users.txt", email)) return 0;
        saveUser("users.txt", email, password);
        if (role == 1) saveUser("customers.txt", email, password);
        else saveUser("sellers.txt", email, password);
        std::cout << (role == 1 ? "Customer" : "Seller") << " signed up successfully.\n";
        return 0;
    }

    if ((role == 1 && validateLogin("customers.txt", email, password)) ||
        (role == 2 && validateLogin("sellers.txt", email, password))) {

        if (role == 1) {
            Customer customer(email, password);
            std::vector<Product> cart;
            int op;

            do {
                std::cout << "\n1. View Products\n2. Add to Cart\n3. Checkout\n0. Logout\nChoice: ";
                std::cin >> op;

                if (op == 1) {
                    productManager.listProducts();
                } else if (op == 2) {
                    int pid, qty;
                    std::cout << "Enter product ID to add: ";
                    std::cin >> pid;
                    std::cout << "Enter quantity: ";
                    std::cin >> qty;
                    Product* p = productManager.findProduct(pid);
                    if (p && qty <= p->getQuantity()) {
                        cart.push_back(Product(p->getId(), p->getName(), p->getPrice(), qty, p->sellerName));
                        std::cout << "✅ Added to cart.\n";
                    } else {
                        std::cout << "❌ Invalid product or quantity.\n";
                    }
                } else if (op == 3 && !cart.empty()) {
                   
                      

                    productManager.generateReceipt(customer.getEmail(), cart);
                    
                    // Remove this block in main.cpp after calling generateReceipt():

                    cart.clear();
                    std::cout << "✅ Checkout complete.\n";
                }

            } while (op != 0);

        } else {
            Seller seller(email, password);
            int op;

            do {
                std::cout << "\n1. Add Product\n2. Update Product Quantity\n0. Logout\nChoice: ";
                std::cin >> op;

                if (op == 1) {
                    int id, quantity;
                    std::string name;
                    double price;
                    std::cout << "Enter ID: "; std::cin >> id;
                    std::cout << "Enter name: "; std::cin >> name;
                    std::cout << "Enter price: "; std::cin >> price;
                    std::cout << "Enter quantity: "; std::cin >> quantity;
                    Product product(id, name, price, quantity, seller.getEmail());
                    productManager.addProduct(product);
                    std::cout << "✅ Product added.\n";
                } else if (op == 2) {
                    int id, newQty;
                    std::cout << "Enter product ID: ";
                    std::cin >> id;
                    std::cout << "Enter new quantity: ";
                    std::cin >> newQty;
                    if (productManager.updateProductQuantities(id, newQty, seller.getEmail())) {
    productManager.saveProductsToFile(); // <-- ADD THIS
    std::cout << "✅ Product quantity updated.\n";
}

                    else
                        std::cout << "❌ Product not found or not owned by you.\n";
                }

            } while (op != 0);
        }

    } else {
        std::cout << "❌ Invalid login credentials.\n";
    }

    return 0;
}
