#include<iostream>
using namespace std;

class User{
    string name;
    string email;
    public:
    User() : name(""), email(""){}
    User(string n,string e): name(n), email(e){}

    virtual void Register(){
        cout << "Enter your registration details\n";
        cout << "Name: ";
        getline(cin, name);
        cout << "Email: ";
        getline(cin, email);

}
};
int main(){
    User user;
    user.Register();
    return 0;

}
