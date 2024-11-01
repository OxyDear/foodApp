//
// Created by Ivan Potyomin on 4.10.24.
//

#ifndef DONERAPP_DRINK_H
#define DONERAPP_DRINK_H

#include "../Food.h"

class Drink : public Food {
private:
    std::string name;

public:
    Drink(const std::string& name,
          double price,
          int mass,
          const std::string &type = "Drink") : Food(type, price, mass), name(name) {}
//    void display() const override;
};

#endif //DONERAPP_DRINK_H
