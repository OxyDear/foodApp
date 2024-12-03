#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User {
protected:
    std::string username;
    std::string login;
    std::string passwordCipher;

public:
    User(const std::string& username) : username(username) {}
    virtual ~User() = default;

    std::string getUsername() const {
        return username;
    }

    // Ограниченные функции
    virtual void viewDetails() const {
        // Ограниченный доступ
        std::cout << "User: " << username << std::endl;
    }

    void setLoginPass(std::string lg, std::string ps){
        this->login = lg;
        this->passwordCipher = ps;
    }

};

#endif // USER_H
