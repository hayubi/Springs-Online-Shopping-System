#include "Customer.h"
#include "Seller.h"
#include "Utilities.h"
#include "Cart.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

// Load user (login)
bool loadUserFromFile(const string& username, const string& password, string& roleOut) {
    ifstream inFile("users.txt");
    string fileUsername, filePassword, fileRole;
    while (inFile >> fileUsername >> filePassword >> fileRole) {
        if (fileUsername == username && filePassword == password) {
            roleOut = fileRole;
            return true;
        }
    }
    return false;
}

// Check if the username already exists in the file
bool usernameExists(const string& username) {
    ifstream inFile("users.txt");
    string fileUsername, filePassword, fileRole;
    while (inFile >> fileUsername >> filePassword >> fileRole) {
        if (fileUsername == username) {
            return true;  // Username already exists
        }
    }
    return false;
}

// Save a new user (signup)
void saveUserToFile(const string& username, const string& password, const string& role) {
    ofstream outFile("users.txt", ios::app);
    if (outFile) {
        outFile << username << " " << password << " " << role << endl;
        outFile.close();
    } else {
        cout << "Error writing to file.\n";
    }
}

// Updated signup function with username check
void signup() {
    string username, password, role;
    cout << "\n--- Sign Up ---\n";
    cout << "Enter username: ";
    cin >> username;

    // Check if username already exists
    if (usernameExists(username)) {
        cout << "Username already exists. Please choose a different one.\n";
        return;  // Abort the signup process if username exists
    }

    cout << "Enter password: ";
    cin >> password;
    cout << "Enter role (Customer or Shopper): ";
    cin >> role;

    saveUserToFile(username, password, role);
    cout << "Signup successful!\n";
}

int main() {
    try {
        int choice;
        cout << "Welcome to the Shopping System\n";
        cout << "1. Sign Up\n";
        cout << "2. Log In\n";
        cout << "Enter choice: ";
        cin >> choice;

        // Sign Up or Log In
        if (choice == 1) {
            signup();
        } else if (choice == 2) {
            string username, password, role;
            cout << "\n--- Login ---\n";
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            // Validate user login
            if (loadUserFromFile(username, password, role)) {
                cout << "Login successful! Role: " << role << endl;

                // Handle different roles
                if (role == "Customer") {
                    Customer customer(username, "customer@email.com", 5); // Example: assign default points
                    int option;
                    do {
                        cout << "\n--- Customer Menu ---\n";
                        cout << "1. View Cart\n2. Add to Cart\n3. Checkout\n4. Exit\nChoice: ";
                        cin >> option;
                        switch (option) {
                            case 1:
                                customer.viewCart();
                                break;
                            case 2:
                                int pid;
                                cout << "Enter Product ID to Add: ";
                                cin >> pid;
                                // For demo, hardcode some products
                                if (pid == 1)
                                    customer.addToCart(Product(1, "Keyboard", 49.99));
                                else if (pid == 2)
                                    customer.addToCart(Product(2, "Mouse", 29.99));
                                else if (pid == 3)
                                    customer.addToCart(Product(3, "Monitor", 199.99));
                                else
                                    cout << "Invalid Product ID.\n";
                                break;
                            case 3:
                                customer.checkout();
                                break;
                        }
                    } while (option != 4);

                } else if (role == "Shopper" || role == "Seller") {
                    Seller seller(username, "seller@email.com");

                    // Add default products
                    seller.addProduct(Product(1, "Keyboard", 49.99));
                    seller.addProduct(Product(2, "Mouse", 29.99));
                    seller.addProduct(Product(3, "Monitor", 199.99));

                    int option;
                    do {
                        cout << "\n--- Seller Menu ---\n";
                        cout << "1. View Products\n2. Add Product\n3. Update Quantity\n4. Exit\nChoice: ";
                        cin >> option;
                        switch (option) {
                            case 1:
                                seller.viewProducts();
                                break;
                            case 2: {
                                int id, quantity;
                                double price;
                                string name, sellerName;
                                cout << "Enter ID, Name, Price, Quantity, Seller: ";
                                cin >> id >> name >> price >> quantity >> sellerName;
                                seller.addProductToFile(id, name, price, quantity, sellerName);
                                break;
                            }
                            case 3: {
                                int id, newQty;
                                cout << "Enter Product ID and New Quantity: ";
                                cin >> id >> newQty;
                                seller.updateProductQuantity(id, newQty);
                                break;
                            }
                        }
                    } while (option != 4);

                } else {
                    cout << "Unknown role.\n";
                }
            } else {
                cout << "Invalid login.\n";
            }
        } else {
            cout << "Invalid choice.\n";
        }
    } catch (const std::exception& e) {
        handleException(e.what());
    }

    return 0;
}
