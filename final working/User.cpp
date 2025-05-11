// user.cpp
#include "user.h"
#include <fstream>
#include <string>

User::User(const std::string& email, const std::string& password) : email(email), password(password) {}

std::string User::getEmail() const { return email; }
