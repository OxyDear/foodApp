QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cfiles/ProductWidget.cpp \
    cfiles/adminpage.cpp \
    cfiles/encrypt.cpp \
    cfiles/loginpage.cpp \
    cfiles/main.cpp \
    cfiles/mainwindow.cpp \
    cfiles/registerpage.cpp \
    cfiles/types.cpp \
    DatabaseManager/FileProcessing.cpp

HEADERS += \
    DatabaseManager/FileProcessing.h \
    assets/ProductWidget.h \
    hfiles/ProductWidget.h \
    hfiles/adminpage.h \
    hfiles/checkps.h \
    hfiles/encrypt.h \
    hfiles/loginpage.h \
    hfiles/mainwindow.h \
    hfiles/registerpage.h \
    hfiles/types.h \
    mainClasses/Burger.h \
    mainClasses/Drink.h \
    mainClasses/FoodBox.h \
    mainClasses/Salad.h \
    mainClasses/Sauce.h \
    mainClasses/Snack.h \
    mainClasses/Soup.h \
    Food.h \
    users/Admin.h \
    users/User.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    # assets/FoodTypes/Burger/BurgerProps.txt \
    # assets/FoodTypes/Burger/BurgerTypes.txt \
    # assets/FoodTypes/Burger/images/Beef Burger.jpg \
    # assets/FoodTypes/Burger/images/Beef Cheeseburger.png \
    # assets/FoodTypes/Burger/images/Chicken Burger.png \
    # assets/FoodTypes/Burger/images/Chicken Cheeseburger.jpg \
    # assets/FoodTypes/Drink/DrinkProps.txt \
    # assets/FoodTypes/Drink/images/Black Tea.jpg \
    # assets/FoodTypes/Drink/images/Bottle of Water highly carbonated.png \
    # assets/FoodTypes/Drink/images/Bottle of Water medium sparkling.png \
    # assets/FoodTypes/Drink/images/Bottle of Water still.png \
    # assets/FoodTypes/Drink/images/Coca-Cola.png \
    # assets/FoodTypes/Drink/images/Fanta.png \
    # assets/FoodTypes/Drink/images/Ginger&Honey&Lemon Lemonade.png \
    # assets/FoodTypes/Drink/images/Ginger&Honey&Lemon Tea.jpg \
    # assets/FoodTypes/Drink/images/Green Tea.jpg \
    # assets/FoodTypes/Drink/images/Highly Carbonated Bottle of Water.png \
    # assets/FoodTypes/Drink/images/Juice Dobri.png \
    # assets/FoodTypes/Drink/images/Lemonade ginger-honey-lemon.jpg \
    # assets/FoodTypes/Drink/images/Lemonade orange-lime.jpg \
    # assets/FoodTypes/Drink/images/Lemonade raspberry-grapefruit.jpg \
    # assets/FoodTypes/Drink/images/Lemonade sea ​​buckthorn-orange.jpg \
    # assets/FoodTypes/Drink/images/Medium Sparkling Bottle of Water.png \
    # assets/FoodTypes/Drink/images/Orange&Lime Lemonade.png \
    # assets/FoodTypes/Drink/images/Orange&Lime Tea.jpg \
    # assets/FoodTypes/Drink/images/Raspberry&Grapefruit Lemonade.png \
    # assets/FoodTypes/Drink/images/Raspberry&Grapefruit Tea.jpg \
    # assets/FoodTypes/Drink/images/Sea Buckthorn&Orange Lemonade.jpg \
    # assets/FoodTypes/Drink/images/Sea Buckthorn&Orange Tea.jpg \
    # assets/FoodTypes/Drink/images/Still Bottle of Water.png \
    # assets/FoodTypes/Drink/images/Tea black.jpg \
    # assets/FoodTypes/Drink/images/Tea ginger-honey-lemon.jpg \
    # assets/FoodTypes/Drink/images/Tea green.jpg \
    # assets/FoodTypes/Drink/images/Tea orange-lime.jpg \
    # assets/FoodTypes/Drink/images/Tea raspberry-grapefruit.jpg \
    # assets/FoodTypes/Drink/images/Tea sea ​​buckthorn-orange.jpg \
    # assets/FoodTypes/FoodBox/FoodBoxProps.txt \
    # assets/FoodTypes/FoodBox/FoodBoxTypes.txt \
    # assets/FoodTypes/FoodBox/images/Classic Food Box.jpg \
    # assets/FoodTypes/FoodBox/images/Food box with nuggets.jpg \
    # assets/FoodTypes/FoodBox/images/Food box with sausages.jpg \
    # assets/FoodTypes/Salad/SaladProps.txt \
    # assets/FoodTypes/Salad/SaladTypes.txt \
    # assets/FoodTypes/Salad/images/Caesar salad.jpg \
    # assets/FoodTypes/Salad/images/Vegetable salad.jpg \
    # assets/FoodTypes/Sauce/SauceProps.txt \
    # assets/FoodTypes/Sauce/SauceTypes.txt \
    # assets/FoodTypes/Sauce/images/American mustard.jpg \
    # assets/FoodTypes/Sauce/images/Barbecue sauce.jpg \
    # assets/FoodTypes/Sauce/images/Burger sauce.jpg \
    # assets/FoodTypes/Sauce/images/Ketchup.jpg \
    # assets/FoodTypes/Sauce/images/Mushroom sauce.jpg \
    # assets/FoodTypes/Sauce/images/Signature caesar sauce.jpg \
    # assets/FoodTypes/Sauce/images/Signature grill sauce.jpg \
    # assets/FoodTypes/Sauce/images/Signature hot sauce.jpg \
    # assets/FoodTypes/Sauce/images/Signature onion-sour cream sauce.jpg \
    # assets/FoodTypes/Sauce/images/Sweet and sour sauce.jpg \
    # assets/FoodTypes/Sauce/images/Teriyaki sauce.jpg \
    # assets/FoodTypes/Snack/SnackProps.txt \
    # assets/FoodTypes/Snack/SnackTypes.txt \
    # assets/FoodTypes/Snack/images/Cheese sticks.jpg \
    # assets/FoodTypes/Snack/images/Chicken wings.jpg \
    # assets/FoodTypes/Snack/images/Country-style potatoes.jpg \
    # assets/FoodTypes/Snack/images/French fries.jpg \
    # assets/FoodTypes/Snack/images/Nuggets.jpg \
    # assets/FoodTypes/Snack/images/Shrimps.jpg \
    # assets/FoodTypes/Soup/SoupProps.txt \
    # assets/FoodTypes/Soup/SoupTypes.txt \
    # assets/FoodTypes/Soup/images/Solyanka.jpg \
    assets/FoodTypes/Burger/BurgerTypes.txt \
    assets/FoodTypes/Burger/images/Beef Burger.png \
    assets/FoodTypes/Burger/images/Beef Cheeseburger.png \
    assets/FoodTypes/Burger/images/Chicken Burger.png \
    assets/FoodTypes/Burger/images/Chicken Cheeseburger.png \
    assets/FoodTypes/BurgerTypes.txt \
    assets/FoodTypes/Drink/DrinkProps.txt \
    assets/FoodTypes/Drink/DrinkTypes.txt \
    assets/FoodTypes/Drink/images/Black Tea.jpg \
    assets/FoodTypes/Drink/images/Coca-Cola.png \
    assets/FoodTypes/Drink/images/Fanta.png \
    assets/FoodTypes/Drink/images/Ginger&Honey&Lemon Lemonade.png \
    assets/FoodTypes/Drink/images/Ginger&Honey&Lemon Tea.jpg \
    assets/FoodTypes/Drink/images/Green Tea.jpg \
    assets/FoodTypes/Drink/images/Highly Carbonated Bottle of Water.png \
    assets/FoodTypes/Drink/images/Juice Dobri.png \
    assets/FoodTypes/Drink/images/Medium Sparkling Bottle of Water.png \
    assets/FoodTypes/Drink/images/Orange&Lime Lemonade.png \
    assets/FoodTypes/Drink/images/Orange&Lime Tea.jpg \
    assets/FoodTypes/Drink/images/Pulpy.png \
    assets/FoodTypes/Drink/images/Raspberry&Grapefruit Lemonade.png \
    assets/FoodTypes/Drink/images/Raspberry&Grapefruit Tea.jpg \
    assets/FoodTypes/Drink/images/Sea Buckthorn&Orange Lemonade.jpg \
    assets/FoodTypes/Drink/images/Sea Buckthorn&Orange Tea.jpg \
    assets/FoodTypes/Drink/images/Sprite.png \
    assets/FoodTypes/Drink/images/Still Bottle of Water.png \
    assets/FoodTypes/FoodBox/FoodBoxProps.txt \
    assets/FoodTypes/FoodBox/FoodBoxTypes.txt \
    assets/FoodTypes/FoodBox/images/Classic Food Box.png \
    assets/FoodTypes/FoodBox/images/Falafel food box.png \
    assets/FoodTypes/FoodBox/images/Food box with nuggets.png \
    assets/FoodTypes/FoodBox/images/Food box with sausages.png \
    assets/FoodTypes/Salad/SaladProps.txt \
    assets/FoodTypes/Salad/SaladTypes.txt \
    assets/FoodTypes/Salad/images/Caesar salad.png \
    assets/FoodTypes/Salad/images/Vegetable salad.png \
    assets/FoodTypes/Sauce/SauceProps.txt \
    assets/FoodTypes/Sauce/SauceTypes.txt \
    assets/FoodTypes/Sauce/images/American mustard.jpg \
    assets/FoodTypes/Sauce/images/Barbecue sauce.jpg \
    assets/FoodTypes/Sauce/images/Burger sauce.jpg \
    assets/FoodTypes/Sauce/images/Cheese sauce.jpg \
    assets/FoodTypes/Sauce/images/Ketchup.jpg \
    assets/FoodTypes/Sauce/images/Mushroom sauce.jpg \
    assets/FoodTypes/Sauce/images/Signature caesar sauce.jpg \
    assets/FoodTypes/Sauce/images/Signature garlic sauce.jpg \
    assets/FoodTypes/Sauce/images/Signature grill sauce.jpg \
    assets/FoodTypes/Sauce/images/Signature hot sauce.jpg \
    assets/FoodTypes/Sauce/images/Signature onion-sour cream sauce.jpg \
    assets/FoodTypes/Sauce/images/Sweet and sour sauce.jpg \
    assets/FoodTypes/Sauce/images/Teriyaki sauce.jpg \
    assets/FoodTypes/Snack/SnackProps.txt \
    assets/FoodTypes/Snack/SnackTypes.txt \
    assets/FoodTypes/Snack/images/Cheese sticks.png \
    assets/FoodTypes/Snack/images/Chicken wings.png \
    assets/FoodTypes/Snack/images/Country-style potatoes.png \
    assets/FoodTypes/Snack/images/French fries.png \
    assets/FoodTypes/Snack/images/Shrimps.png \
    assets/FoodTypes/Snack/images/nuggets.png \
    assets/FoodTypes/Soup/SoupProps.txt \
    assets/FoodTypes/Soup/SoupTypes.txt \
    assets/FoodTypes/Soup/images/Solyanka.png \
    assets/FoodTypes/Burger/BurgerProps.txt \
    assets/adds.txt \
    images/sample.png \
    users/users.txt

RESOURCES += \
    resources.qrc \
    style.qrc

# Укажите путь к OpenSSL
INCLUDEPATH += /usr/local/opt/openssl/include
LIBS += -L/usr/local/opt/openssl/lib -lssl -lcrypto
