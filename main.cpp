#include <iostream>
#include "mainClasses/Burger.h"
#include "mainClasses/FoodBox.h"
#include "mainClasses/Salad.h"
#include "mainClasses/Snack.h"
#include "mainClasses/Soup.h"
#include "mainClasses/Drink.h"
#include "mainClasses/Sauce.h"
#include "users/User.h"
#include "users/Admin.h"

int main() {
    std::cout << "hi" << "\n";
    User user("RegularUser");
    Admin admin("AdminrUser");
    user.viewDetails();

    Sauce sgs("signature garlic sauce", 1, 50);
    Sauce burgs("burger sauce", 1, 50);
    Drink drink("Black Tea", 2, 300);
    Burger bg("Chicken Burger", 9.5, 300, {"signature bun", "chicken cutlet", "pickled cucumber", "tomato", "Iceberg lettuce"}, {sgs, burgs});
//    Sauce sc("Sauc");
    bg.display();
//    sc.display();

    admin.changeName(bg, "Deluxe Cheeseburger");
//    admin.changeName(sc, "Spicy Ketchup");

    bg.display();
//    sc.display();

//    std::string data = bg.readInfo();
//    std::cout << bg.readInfo() << std::endl;
    std::vector<std::string> prodsList;
    std::vector<std::vector<std::string>> propsList;
    std::vector<std::string> prodsListDrink;
    std::vector<std::vector<std::string>> propsListDrink;
    prodsList = bg.setProdsList();
    propsList = bg.setPropsList();

    prodsListDrink = drink.setProdsList();
    propsListDrink = drink.setPropsList();
//    std::cout << sc.readInfo() << std::endl;

    std::vector<std::string> prods(14);
//    prods = sc.setList();
    for (const auto& prod : prodsListDrink) {
        std::cout << prod << '\n';
    }

//    FoodBox fdx("Rice with Chicken", {"Salad", "Fries"});
//    Salad sld({"Lettuce", "Tomato", "Cucumber"});
//    Snack snk("Chips"
//    Soup sp("Tomato");
//    Drink drnk("Coke", false);

    return 0;
}
