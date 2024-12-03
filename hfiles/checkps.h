#ifndef CHECKUPS_H
#define CHECKUPS_H

#include <QString>
#include <QDebug>
#include <fstream>
#include <sstream>
#include "mainwindow.h"

std::string fileName = "../../users.txt";

std::unordered_map<std::string, std::string> readUsers() {

    std::unordered_map<std::string, std::string> users;

    std::ifstream file(fileName);

    if (!file.is_open()) return users;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string username, passwordHash;
        if (std::getline(iss, username, ':') && std::getline(iss, passwordHash)) {
            users[username] = passwordHash;
        }
    }
    file.close();
    return users;
}

bool checkPass(std::string& lg, std::string& ps){
    std::unordered_map<std::string, std::string> users = readUsers();
    std::string str = users[lg];

    if(users.find(lg) != users.end() && str == ps){
        return true;
    } else return false;
}


bool is_exist(std::string& lg){
    std::unordered_map<std::string, std::string> users = readUsers();
    if(users.find(lg) != users.end()){
        return true;
    } else return false;
}

void writeUser(std::string& lg, std::string& ps){

    std::ofstream file(fileName, std::ios::app);
    if (file.is_open()) {
        file << lg << ":" << ps << "\n";
        file.close();
    }else{
        qDebug() << "ОШИБКА РЕГИСТРАЦИИ!";
    }
    return;
}

#endif // CHECKUPS_H
