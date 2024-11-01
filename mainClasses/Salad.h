//
// Created by Ivan Potyomin on 4.10.24.
//

#ifndef DONERAPP_SALAD_H
#define DONERAPP_SALAD_H

#include "../Food.h"

class Salad : public Food {
private:
    const std::vector<std::string> ingredients;

public:
    Salad(const std::vector<std::string>& ingredients,
          double price,
          int mass,
          const std::string& type = "Salad") : Food(type, price, mass), ingredients(ingredients) {};
//    void display() const override;
};

#endif //DONERAPP_SALAD_H
