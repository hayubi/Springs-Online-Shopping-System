
 int main() {
    int choice;
    cout << "Welcome to the Shopping System!" << endl;
    cout << "Please choose your role:\n1. Customer\n2. Seller\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) {
        // Register as Customer
        Customer customer;
        customer.Register();

        // Create a Shopping Cart for the customer
        ShoppingCart cart;

        // Add hardcoded products to Seller's inventory
        Seller seller;
        seller.addProduct(101, 10.0, "Laptop", 5);
        seller.addProduct(102, 15.0, "Smartphone", 3);
        seller.addProduct(103, 5.0, "Headphones", 10);
        
        // Let the customer view and interact with products
        bool customerDone = false;
        while (!customerDone) {
            cout << "\nAvailable Products: \n";
            seller.viewAllProducts();
            
            cout << "\nEnter Product ID to view details or 0 to checkout: ";
            int productID;
            cin >> productID;

            if (productID == 0) {
                // Checkout
                cart.checkout();
                customerDone = true;
            } else {
                seller.viewProductDetails(productID);

                cout << "Do you want to add this product to your cart? (1 for Yes, 0 for No): ";
                int addToCart;
                cin >> addToCart;
                if (addToCart == 1) {
                    Product p = Product(productID, 10.0, "Product Example", 1); // Example, ideally from the product list
                    cart.addProduct(p);
                    cout << "Product added to cart.\n";
                }
            }
        }
    } 
    else if (choice == 2) {
        // Register as Seller
        Seller seller;
        string sellerName, sellerEmail;
        int sellerID;
        cout << "\nEnter your Seller ID: ";
        cin >> sellerID;
        cout << "Enter your Seller Name: ";
        cin >> sellerName;
        cout << "Enter your Seller Email: ";
        cin >> sellerEmail;
        
        seller.addProduct(104, 25.0, "Keyboard", 7);
        seller.addProduct(105, 40.0, "Mouse", 20);

        // Let the seller manage their products
        bool sellerDone = false;
        while (!sellerDone) {
            cout << "\nSeller Menu: \n";
            cout << "1. View all products\n";
            cout << "2. Add a product\n";
            cout << "3. Delete a product\n";
            cout << "4. Update product price\n";
            cout << "5. Update product description\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            int sellerChoice;
            cin >> sellerChoice;

            switch (sellerChoice) {
                case 1:
                    seller.viewAllProducts();
                    break;
                case 2: {
                    int id;
                    float price;
                    string description;
                    int quantity;
                    cout << "Enter Product ID: ";
                    cin >> id;
                    cout << "Enter Product Price: ";
                    cin >> price;
                    cout << "Enter Product Description: ";
                    cin.ignore();
                    getline(cin, description);
                    cout << "Enter Product Quantity: ";
                    cin >> quantity;
                    seller.addProduct(id, price, description, quantity);
                    cout << "Product added successfully.\n";
                    break;
                }
                case 3: {
                    int id;
                    cout << "Enter Product ID to delete: ";
                    cin >> id;
                    seller.deleteProduct(id);
                    cout << "Product deleted.\n";
                    break;
                }
                case 4: {
                    int id;
                    float newPrice;
                    cout << "Enter Product ID to update price: ";
                    cin >> id;
                    cout << "Enter new price: ";
                    cin >> newPrice;
                    seller.updateProductPrice(id, newPrice);
                    cout << "Product price updated.\n";
                    break;
                }
                case 5: {
                    int id;
                    string newDesc;
                    cout << "Enter Product ID to update description: ";
                    cin >> id;
                    cout << "Enter new description: ";
                    cin.ignore();
                    getline(cin, newDesc);
                    seller.updateProductDesc(id, newDesc);
                    cout << "Product description updated.\n";
                    break;
                }
                case 0:
                    sellerDone = true;
                    break;
                default:
                    cout << "Invalid choice, try again.\n";
            }
        }
    } 
    else {
        cout << "Invalid choice, exiting.\n";
    }

    return 0;
}
