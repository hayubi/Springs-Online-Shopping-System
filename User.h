#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

class User 
{
    protected:
        string email, password;
        
    public:
        User(const string& email, const string& password);
        virtual void displayMenu() const = 0;
        string getEmail() const;
        virtual ~User() {}
};
#endif