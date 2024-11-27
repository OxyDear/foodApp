//
// Created by Ivan Potyomin on 4.10.24.
//

#ifndef DONERAPP_SOUP_H
#define DONERAPP_SOUP_H

#include "../Food.h"

class Soup : public Food {
private:
    std::string flavor;

public:
    Soup(const std::string& flavor,
         double price,
         int mass,
         const std::string &type = "Soup") : Food(type, price, mass), flavor(flavor) {}
//    void display() const override;
};

#endif //DONERAPP_SOUP_H
