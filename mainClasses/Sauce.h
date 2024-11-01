//
// Created by Ivan Potyomin on 4.10.24.
//

#ifndef DONERAPP_SAUCE_H
#define DONERAPP_SAUCE_H

#include <utility>

#include "../Food.h"

class Sauce : public Food {
protected:
    std::string name;
public:
    Sauce(std::string name,
          double price,
          int mass,
          const std::string& type = "Sauce")
          : Food(type, price, mass), name(name) {}
//    void display() const override;

    void setName(const std::string& newName) {
        name = newName;
    }
};

#endif //DONERAPP_SAUCE_H
