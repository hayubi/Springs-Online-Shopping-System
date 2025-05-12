#include "user.h"
#include <fstream>
#include <string>
using namespace std;

User::User(const string& n, const string& c, const string& add, const string& mail, const string& pass) : name(n), contact(c), address(add), email(mail), password(pass) {}

string User::getname() const { return name; }
string User::getcontact() const { return contact; }
string User::getaddress() const { return address; }
string User::getEmail() const { return email; }

void User::setContact(string c) { contact = c; }
void User::setAddress(string a) { address = a; }
