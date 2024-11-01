#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User {
protected:
    std::string username;

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
};

#endif // USER_H