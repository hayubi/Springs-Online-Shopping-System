#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>

template<typename T>
void handleException(const T& msg) 
{
    std::cerr << "Error: " << msg << "\n";
}

bool validateLogin(const std::string& filename, const std::string& email, const std::string& password);

#endif