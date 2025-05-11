#include "user.h"
#include <fstream>
#include <string>
using namespace std;

User::User(const string& email, const string& password) : email(email), password(password) {}
string User::getEmail() const { return email; }