#include "mainwindow.h"
#include <QDebug>
#include <QGridLayout>
#include "ProductWidget.h"
#include "registerpage.h"
#include "loginpage.h"
#include <iostream>

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

    // Панель категорий
    QHBoxLayout *categoryLayout = new QHBoxLayout();
    categoryLayout->setAlignment(Qt::AlignLeft); // Выравнивание по левому краю
    mainLayout->addLayout(categoryLayout); // Добавляем layout категорий в основной layout

    // Добавляем кнопки категорий в горизонтальный layout
    addCategoryButton(categoryLayout, "Types");

    categoryLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    addAuthorizeButton(categoryLayout, "Auth");
    // addCategoryButton(categoryLayout, "Тип 2");
    // addCategoryButton(categoryLayout, "Тип 3");

    // Прокручиваемая область для продуктов
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollWidget = new QWidget();
    scrollLayout = new QVBoxLayout(scrollWidget);

    // Заполнение прокручиваемой области
    addProduct(":/images/sample.png", "Товар 1");
    addProduct(":/images/sample.png", "Товар 2");
    addProduct(":/images/sample.png", "Товар 3");

    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea);

    stackedWidget->addWidget(mainPage);  // Добавляем главную страницу в стек

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
    categoryButton->setStyleSheet("QPushButton {"
                                  "padding: 10px;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: gray;"
                                  "}");

    // Добавляем кнопку в горизонтальный layout
    categoryLayout->addWidget(categoryButton);
}


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

            stackedWidget->addWidget(loginpage);
            stackedWidget->setCurrentWidget(loginpage);
            std::cout << "login2" << " ";
        });

        stackedWidget->addWidget(registerpage);
        stackedWidget->setCurrentWidget(registerpage);
        std::cout << "register2" << " ";
    });

    // Добавляем кнопку в горизонтальный layout
    categoryLayout->addWidget(authButton);
}

void MainWindow::addProduct(const QString &imagePath, const QString &name) {
    ProductWidget *productWidget = new ProductWidget(imagePath, name);
    connect(productWidget, &ProductWidget::clicked, [this, imagePath]() {
        showProductPage(imagePath);
    });

    scrollLayout->addWidget(productWidget);
}

void MainWindow::showProductPage(const QString &imagePath) {
    QPixmap pixmap(imagePath);
    if (pixmap.isNull()) {
        qDebug() << "Ошибка загрузки изображения:" << imagePath;
    } else {
        mainImageLabel->setPixmap(pixmap.scaled(300, 300, Qt::KeepAspectRatio));
        stackedWidget->setCurrentWidget(productPage);
    }
}
