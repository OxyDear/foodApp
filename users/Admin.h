#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include "User.h"
#include "../Food.h"
#include "../mainClasses/Burger.h"
#include "../mainClasses/FoodBox.h"
#include "../mainClasses/Salad.h"
#include "../mainClasses/Snack.h"
#include "../mainClasses/Soup.h"
#include "../mainClasses/Drink.h"
#include "../mainClasses/Sauce.h"

class Admin : public User {
public:
    Admin(const std::string& username) : User(username) {}

    // Функция для изменения имени
    template <typename T>
    void changeName(T& item, const std::string& newName) {
        item.setName(newName);
    }
};

#endif // ADMIN_H