#include "User.h"
User::User(std::string n, std::string e) : name(n), email(e) {}
std::string User::getEmail() const { return email; }
