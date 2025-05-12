#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

class User 
{
    protected:
        string name;
        string contact;
        string address;
        string email;
        string password;
        
    public:
        User(const string& n, const string& c, const string& add, const string& mail, const string& pass);
        virtual ~User() {}
        virtual void displayMenu() const = 0;

        string getname() const;
        string getcontact() const; 
        string getaddress() const;
        string getEmail() const;

        void setContact(string c);
        void setAddress(string a);
};
#endif
