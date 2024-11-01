//
// Created by Ivan Potyomin on 4.10.24.
//

#ifndef DONERAPP_FOODBOX_H
#define DONERAPP_FOODBOX_H

#include "../Food.h"

class FoodBox : public Food {
private:
    std::string mainDish;
    std::vector<std::string> sides;
public:
    FoodBox(const std::string& mainDish,
            const std::vector<std::string>& sides,
            double price,
            int mass,
            const std::string& type = "FoodBox") : mainDish(mainDish), sides(sides), Food(type, price, mass) {}
//    void display() const override;
};

#endif //DONERAPP_FOODBOX_H
