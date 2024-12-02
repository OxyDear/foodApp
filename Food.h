//
// Created by Ivan Potyomin on 4.10.24.
//

#ifndef DONERAPP_FOOD_H
#define DONERAPP_FOOD_H

#include <iostream>
#include "DatabaseManager/FileProcessing.h"

class Food {
protected:
    std::string type;
    double price;
    int mass;
public:
    Food(const std::string &type, double price=0, int mass=0) : type(type), price(price), mass(mass) {}
    virtual void display() const {
        std::cout << type << std::endl;
    }

    // чтение данных из файла
    std::vector<std::string> readInfo() {
        File fileManager;
        try {
            int fd1 = fileManager.OpenFile("/Users/oxydear/Documents/Ivan's Mac/Qt/app/assets/FoodTypes/" + type + "/" + type + "Types.txt");
            int fd2 = fileManager.OpenFile("/Users/oxydear/Documents/Ivan's Mac/Qt/app/assets/FoodTypes/" + type + "/" + type + "Props.txt");
            char* buffer1 = new char[1000];
            char* buffer2 = new char[1000];
            fileManager.ReadFile(fd1, buffer1, 1000);
            fileManager.ReadFile(fd2, buffer2, 1000);
            buffer1[999] = '\0';
            buffer2[999] = '\0';
            close(fd1);
            close(fd2);
            return {buffer1, buffer2};
//            std::cout << "Read from file: " << buffer << std::endl;
//            delete[] buffer;

        } catch (const FileException& e) {
            std::cerr << e.Message() << std::endl;
        }
    }

    // Метод для записи типов продуктов в список
    std::vector<std::string> setProdsList() {
        std::string prodsData = readInfo()[0];
        std::vector<std::string> productsList;

        int pos;
        std::string token;

        while ((pos = prodsData.find(';')) != std::string::npos) {
            token = prodsData.substr(0, pos);
            productsList.push_back(token);
            prodsData.erase(0, pos + 1);
        }

        productsList.push_back(prodsData);

//        for (const auto& el : productsList) {
//            std::cout << el << std::endl;
//        }

        return productsList;
    }

    // Метод для записи свойств продуктов в список
    std::vector<std::vector<std::string>> setPropsList() {
        std::string propsData = readInfo()[1];
        std::vector<std::vector<std::string>> propertiesList;

        int pos;
        std::string token;

        while ((pos = propsData.find('\n')) != std::string::npos) {
            int pos2;
            std::string token2;
            token = propsData.substr(0, pos);
            propertiesList.push_back({});
            while ((pos2 = token.find(';')) != std::string::npos) {
                token2 = token.substr(0, pos2);
                propertiesList[propertiesList.size()-1].push_back(token2);
                token.erase(0, pos2 + 1);
            }
            propsData.erase(0, pos + 1);
        }

//        for (const auto& el : productsList) {
//            std::cout << el << std::endl;
//        }

        return propertiesList;
    }

    virtual ~Food() = default;
};

#endif //DONERAPP_FOOD_H
