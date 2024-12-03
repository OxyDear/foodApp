#include "../hfiles/mainwindow.h"
#include <QDebug>
#include <QGridLayout>
#include "../hfiles/ProductWidget.h"
#include "../hfiles/registerpage.h"
#include "../hfiles/loginpage.h"
#include "../hfiles/types.h"
#include "../Food.h"
#include <iostream>
#include "vector"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupUI();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Главная страница
    mainPage = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainPage);

    RegisterPage *registerpage = new RegisterPage(this);
    connect(registerpage, &RegisterPage::backToMain, this, [this]() {
        stackedWidget->setCurrentWidget(mainPage);
        std::cout << "main" << " ";
    });

    connect(registerpage, &RegisterPage::switchToLogin, this, [this, registerpage]() {
        std::cout << "login1" << " ";
        LoginPage* loginpage = new LoginPage(this);
        connect(loginpage, &LoginPage::backToMain, this, [this]() {
            stackedWidget->setCurrentWidget(mainPage);
            std::cout << "main" << " ";
        });
        connect(loginpage, &LoginPage::switchToRegister, [this, registerpage]() {
            stackedWidget->setCurrentWidget(registerpage);
            std::cout << "register1" << " ";
        });

        connect(loginpage, &LoginPage::userLoggedIn, this, [this](const std::string& username) {
            setCurrentUser(username); // Устанавливаем текущего пользователя
        });

        stackedWidget->addWidget(loginpage);
        stackedWidget->setCurrentWidget(loginpage);
        std::cout << "login2" << " ";
    });

    connect(registerpage, &RegisterPage::userRegIn, this, [this](const std::string& username) {
        setCurrentUser(username); // Устанавливаем текущего пользователя
    });

    stackedWidget->addWidget(registerpage);
    stackedWidget->setCurrentWidget(registerpage);
    std::cout << "register2" << " ";

    // Панель категорий
    QHBoxLayout *categoryLayout = new QHBoxLayout();
    categoryLayout->setAlignment(Qt::AlignLeft);
    mainLayout->addLayout(categoryLayout);

    // Добавляем кнопки категорий
    addCategoryButton(categoryLayout, "Types");

    categoryLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // Заменяем кнопку Auth на QLabel для имени пользователя
    userLabel = new QLabel("Пользователь: Не вошел", this); // Изначально не вошел
    categoryLayout->addWidget(userLabel); // Добавляем QLabel в layout категорий
    addAuthorizeButton(categoryLayout, "Auth");

    // Убираем кнопку "Auth"
    // addAuthorizeButton(categoryLayout, "Auth");

    // Прокручиваемая область для продуктов
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollWidget = new QWidget();
    scrollLayout = new QVBoxLayout(scrollWidget);

    updateProductList();

    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea);

    stackedWidget->addWidget(mainPage);

    // Страница товара
    productPage = new QWidget(this);
    QVBoxLayout *productLayout = new QVBoxLayout(productPage);

    mainImageLabel = new QLabel();
    mainImageLabel->setAlignment(Qt::AlignCenter);
    mainImageLabel->setFixedSize(300, 300);

    backButton = new QPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, [this]() {
        stackedWidget->setCurrentWidget(mainPage);
    });

    productLayout->addWidget(mainImageLabel);
    productLayout->addWidget(backButton);
    stackedWidget->addWidget(productPage);
}

void MainWindow::addCategoryButton(QHBoxLayout *categoryLayout, const QString &name) {
    QPushButton *categoryButton = new QPushButton(name);
    categoryButton->setStyleSheet("QPushButton { padding: 10px; } QPushButton:hover { background-color: gray; }");

    connect(categoryButton, &QPushButton::clicked, [this]() {
        TypesPage *typesPage = new TypesPage(this);
        connect(typesPage, &TypesPage::backToMain, this, [this](const QString &type) {
            if (!type.isEmpty()) {
                MainWindow::types = type.toStdString();
                updateProductList();
            }
            stackedWidget->setCurrentWidget(mainPage);
        });

        stackedWidget->addWidget(typesPage);
        stackedWidget->setCurrentWidget(typesPage);
    });

    categoryLayout->addWidget(categoryButton);
}

// QStringList getPaths(QString &type) {
//     if (type == "Burger") {
//         return {}
//     }
// }


void MainWindow::addAuthorizeButton(QHBoxLayout *categoryLayout, const QString &name) {
    QPushButton *authButton = new QPushButton(name);
    authButton->setStyleSheet("QPushButton {"
                                  "padding: 10px;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: gray;"
                                  "}");

    connect(authButton, &QPushButton::clicked, [this]() {
        RegisterPage *registerpage = new RegisterPage(this);
        connect(registerpage, &RegisterPage::backToMain, this, [this]() {
            stackedWidget->setCurrentWidget(mainPage);
            std::cout << "main" << " ";
        });

        connect(registerpage, &RegisterPage::switchToLogin, this, [this, registerpage]() {
            std::cout << "login1" << " ";
            LoginPage* loginpage = new LoginPage(this);
            connect(loginpage, &LoginPage::backToMain, this, [this]() {
                stackedWidget->setCurrentWidget(mainPage);
                std::cout << "main" << " ";
            });
            connect(loginpage, &LoginPage::switchToRegister, [this, registerpage]() {
                stackedWidget->setCurrentWidget(registerpage);
                std::cout << "register1" << " ";
            });

            connect(loginpage, &LoginPage::userLoggedIn, this, [this](const std::string& username) {
                setCurrentUser(username); // Устанавливаем текущего пользователя
            });

            stackedWidget->addWidget(loginpage);
            stackedWidget->setCurrentWidget(loginpage);
            std::cout << "login2" << " ";
        });

        connect(registerpage, &RegisterPage::userRegIn, this, [this](const std::string& username) {
            setCurrentUser(username); // Устанавливаем текущего пользователя
        });

        stackedWidget->addWidget(registerpage);
        stackedWidget->setCurrentWidget(registerpage);
        std::cout << "register2" << " ";
    });


    // Добавляем кнопку в горизонтальный layout
    categoryLayout->addWidget(authButton);
}

void MainWindow::addProduct(const std::string &imagePath, const std::string &name) {
    ProductWidget *productWidget = new ProductWidget(imagePath, name);
    connect(productWidget, &ProductWidget::clicked, [this, imagePath, name]() {
        showProductPage(imagePath + "/images/" + name);
    });

    scrollLayout->addWidget(productWidget);
}

void MainWindow::showProductPage(const std::string &imagePath) {
    QPixmap pixmap(QString::fromStdString(imagePath));
    if (pixmap.isNull()) {
        qDebug() << "Ошибка загрузки изображения:" << imagePath;
    } else {
        mainImageLabel->setPixmap(pixmap.scaled(300, 300, Qt::KeepAspectRatio));
        stackedWidget->setCurrentWidget(productPage);
    }
}

void MainWindow::updateProductList() {
    // Очистить текущий контент
    QLayoutItem* item;
    while ((item = scrollLayout->takeAt(0)) != nullptr) {
        delete item->widget(); // Удаляем виджет
        delete item; // Удаляем элемент
    }

    // Здесь вы можете заново заполнить scrollLayout с нужными продуктами
    Food *reader = new Food(types);
    std::vector<std::string> prods = reader->setProdsList();

    // Заполнение прокручиваемой области
    for (auto &el : prods) {
        addProduct(":/assets/FoodTypes/" + types, el);
    }
}

void MainWindow::setCurrentUser(const std::string &username) {
    if (currentUser) {
        delete currentUser; // Удаляем предыдущего пользователя
    }
    User *currentUser = new User(username); // Создаем нового пользователя
    std::cout << currentUser->getUsername();
    userLabel->setText(QString::fromStdString(currentUser->getUsername()));
    std::cout << "Пользователь вошел: " << currentUser->getUsername() << std::endl;
}
