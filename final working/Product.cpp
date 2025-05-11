#include "Product.h"
#include "ProductManager.h"
using namespace std;

Product::Product(int i, std::string n, double p, int q, std::string seller) : id(i), name(n), price(p), quantity(q), sellerName(seller) {}

void Product::display() const 
{
    std::cout << "ID: " << id << ", Name: " << name << ", Price: " << price << ", Quantity: " << quantity << ", Seller: " << sellerName << "\n";
}
void Product::setQuantity(int newQuantity){this->quantity=newQuantity;}
int Product::getId() const { return id; }
int Product::getQuantity() const { return quantity; }
std::string Product::getName() const { return name; }
double Product::getPrice()const{return price;};