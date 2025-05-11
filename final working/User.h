// user.h
#ifndef USER_H
#define USER_H
#include <string>

class User 
{
    protected:
        std::string email, password;
        
    public:
        User(const std::string& email, const std::string& password);

        virtual void displayMenu() const = 0;
        std::string getEmail() const;
        virtual ~User() {}
};

#endif