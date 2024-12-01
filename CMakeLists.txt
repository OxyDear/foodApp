cmake_minimum_required(VERSION 3.25)
project(donerApp)

set(CMAKE_CXX_STANDARD 17)

add_executable(donerApp main.cpp mainClasses/Sauce.h mainClasses/Burger.h mainClasses/FoodBox.h mainClasses/Salad.h mainClasses/Snack.h mainClasses/Drink.h mainClasses/Soup.h Food.h users/User.h users/Admin.h DatabaseManager/FileProcessing.cpp DatabaseManager/FileProcessing.h users/hashSHA256.cpp users/hashSHA256.cpp)
