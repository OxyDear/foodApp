QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cfiles/ProductWidget.cpp \
    cfiles/loginpage.cpp \
    cfiles/main.cpp \
    cfiles/mainwindow.cpp \
    cfiles/registerpage.cpp \
    cfiles/types.cpp \
    DatabaseManager/FileProcessing.cpp \

HEADERS += \
    DatabaseManager/FileProcessing.h \
    hfiles/ProductWidget.h \
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
    images/sample.png

RESOURCES += \
    resources.qrc \
    style.qrc
