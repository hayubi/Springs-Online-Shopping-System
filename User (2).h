#ifndef USER_H
#define USER_H
#include <string>
class User {
protected:
    std::string name;
    std::string email;
public:
    User(std::string, std::string);
    virtual void display() const = 0; // pure virtual
    std::string getEmail() const;
    virtual ~User() {}
};
#endif
