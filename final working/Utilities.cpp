#include<iostream>
#include<string>
#include<fstream>
#include"Utilities.h"
using namespace std;

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