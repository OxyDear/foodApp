#ifndef BURGER_H
#define BURGER_H

#include "../Food.h"
#include "Sauce.h"
#include "../DatabaseManager/FileProcessing.h"
#include <iostream>

class Burger : public Food {
protected:
    std::string name;
    std::vector<std::string> ingredients;
    std::vector<Sauce> sauces;

public:
    Burger(const std::string& name,
           double price,
           int mass,
           std::vector<std::string> ingredients,
           std::vector<Sauce> sauces,
           const std::string& type = "Burger")
            : Food(type, price, mass), name(name), ingredients(ingredients), sauces(sauces) {}

    void display() const override {
        std::cout << "Burger: " << name << std::endl;
    }

    // Метод для изменения имени бургера
    void setName(const std::string& newName) {
        this->name = newName;
    }

};

#endif // BURGER_H