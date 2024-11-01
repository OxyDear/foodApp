//
// Created by Ivan Potyomin on 4.10.24.
//

#ifndef DONERAPP_SNACK_H
#define DONERAPP_SNACK_H

#include "../Food.h"

class Snack : public Food {
private:
    std::string type;

public:
    Snack(double price,
          int mass,
          const std::string& type = "Snack") : Food(type, price, mass) {};
//    void display() const override;
};

#endif //DONERAPP_SNACK_H
