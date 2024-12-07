#include "../hfiles/mainwindow.h"
#include "../hfiles/adminpage.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QStackedWidget>
#include <QPalette>
#include <QPixmap>
#include <QSpacerItem>
#include <QMessageBox>
#include <vector>
#include "../hfiles/ProductWidget.h"
#include "../hfiles/registerpage.h"
#include "../hfiles/loginpage.h"
#include "../hfiles/types.h"
#include "../Food.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentUser(nullptr) {
    setupUI();
}

MainWindow::~MainWindow() {
    delete currentUser;
}

void MainWindow::setupUI() {
    // Настройка общего стиля
    // setStyleSheet("QMainWindow { background-color: #f5f5f5; }");

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Главная страница
    mainPage = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainPage);
    mainLayout->setContentsMargins(20, 20, 20, 20); // Отступы

    QPushButton *addButton = new QPushButton("Add", this);
    addButton->setStyleSheet("QPushButton { padding: 10px; font-size: 14px; }"
                             "QPushButton:hover { color: #bbb; }");
    addButton->setVisible(false); // Initially hidden

    connect(addButton, &QPushButton::clicked, this, [this]() {
        AdminPage *adminPage = new AdminPage(this);
        connect(adminPage, &AdminPage::backToMain, this, [this]() {
            stackedWidget->setCurrentWidget(mainPage);
        });
        connect(adminPage, &AdminPage::adminActionTriggeredAdd, this, [this](const std::string& username) {
            updateUserStatusAdd(username);
        });
        connect(adminPage, &AdminPage::adminActionTriggeredDelete, this, [this](const std::string& username) {
            std::cout << "DELETE" << " ";
            updateUserStatusDelete(username);
        });
        connect(adminPage, &AdminPage::adminActionTriggeredChange, this, [this](const std::string& name, const std::string& editedName) {
            std::cout << "CHANGE" << " ";
            updateName(name, editedName);
            updateProductList("", "");
        });
        connect(adminPage, &AdminPage::adminActionTriggeredDeleteOne, this, [this](const std::string& name) {
            std::cout << "DELE" << " ";
            updateDelete(name);
            updateProductList("", "");
        });
        connect(adminPage, &AdminPage::adminActionTriggeredAddOne, this, [this](const std::string& name, const std::string& desc) {
            std::cout << "ADD" << " ";
            updateAdd(name, desc);
            updateProductList("", "");
        });
        stackedWidget->addWidget(adminPage);
        stackedWidget->setCurrentWidget(adminPage);
    });

    RegisterPage *registerpage = new RegisterPage(this);
    connect(registerpage, &RegisterPage::backToMain, this, [this]() {
        stackedWidget->setCurrentWidget(mainPage);
        std::cout << "main" << " ";
    });

    connect(registerpage, &RegisterPage::switchToLogin, this, [this, registerpage, addButton]() {
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

        connect(loginpage, &LoginPage::userLoggedIn, this, [this, addButton](const std::string& username, const std::string mode) {
            setCurrentUser(username); // Устанавливаем текущего пользователя
            if (mode == "1") {
                addButton->setVisible(true); // Show the "Добавить" button when mode=1
            } else {
                addButton->setVisible(false); // Hide otherwise
            }
        });

        stackedWidget->addWidget(loginpage);
        stackedWidget->setCurrentWidget(loginpage);
        std::cout << "login2" << " ";
    });

    connect(registerpage, &RegisterPage::userRegIn, this, [this, addButton](const std::string& username, const std::string mode) {
        setCurrentUser(username); // Устанавливаем текущего пользователя
        if (mode == "1") {
            addButton->setVisible(true); // Show the "Добавить" button when mode=1
        } else {
            addButton->setVisible(false); // Hide otherwise
        }
    });

    stackedWidget->addWidget(registerpage);
    stackedWidget->setCurrentWidget(registerpage);
    std::cout << "register2" << " ";

    // Панель категорий
    QHBoxLayout *categoryLayout = new QHBoxLayout();
    categoryLayout->setAlignment(Qt::AlignLeft);
    mainLayout->addLayout(categoryLayout);

    // Отображение имени пользователя
    userLabel = new QLabel("Пользователь: Не вошел", this);
    userLabel->setStyleSheet("font-size: 16px; font-weight: bold; padding: 10px;");
    categoryLayout->addWidget(userLabel);
    categoryLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // Кнопка для перехода на страницу типов
    addCategoryButton(categoryLayout, "Типы");

    // Кнопка авторизации
    addAuthorizeButton(categoryLayout, "Вход", addButton);

    // Прокручиваемая область для продуктов
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollWidget = new QWidget();
    scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setAlignment(Qt::AlignTop);
    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea);

    stackedWidget->addWidget(mainPage);

    // Страница товара
    productPage = new QWidget(this);
    QVBoxLayout *productLayout = new QVBoxLayout(productPage);
    productLayout->setAlignment(Qt::AlignCenter);

    mainImageLabel = new QLabel();
    mainImageLabel->setAlignment(Qt::AlignCenter);
    mainImageLabel->setFixedSize(300, 300);
    productLayout->addWidget(mainImageLabel);

    backButton = new QPushButton("Назад", this);
    backButton->setStyleSheet("padding: 10px; font-size: 16px;");
    connect(backButton, &QPushButton::clicked, [this]() {
        stackedWidget->setCurrentWidget(mainPage);
    });
    productLayout->addWidget(backButton);

    stackedWidget->addWidget(productPage);

    updateProductList("", ""); // Загружаем список продуктов
}

void MainWindow::addCategoryButton(QHBoxLayout *categoryLayout, const QString &name) {
    QPushButton *categoryButton = new QPushButton(name);
    categoryButton->setStyleSheet("QPushButton { padding: 10px; font-size: 14px; }"
                                  "QPushButton:hover { color: #bbb; }");
    connect(categoryButton, &QPushButton::clicked, [this]() {
        TypesPage *typesPage = new TypesPage(this);
        connect(typesPage, &TypesPage::backToMain, this, [this](const QString &type, const std::string pricelow, const std::string pricemax) {
            if (!type.isEmpty()) {
                MainWindow::types = type.toStdString();
                updateProductList(pricelow, pricemax);
            }
            stackedWidget->setCurrentWidget(mainPage);
        });

        stackedWidget->addWidget(typesPage);
        stackedWidget->setCurrentWidget(typesPage);
    });
    categoryLayout->addWidget(categoryButton);
}

void MainWindow::addAuthorizeButton(QHBoxLayout *categoryLayout, const QString &name, QPushButton* addButton) {
    QPushButton *authButton = new QPushButton(name);
    authButton->setStyleSheet("QPushButton { padding: 10px; font-size: 14px; }"
                              "QPushButton:hover { color: #bbb; }");

    // QPushButton *addButton = new QPushButton("Добавить", this);
    // addButton->setStyleSheet("QPushButton { padding: 10px; font-size: 14px; }"
    //                          "QPushButton:hover { color: #bbb; }");
    // addButton->setVisible(false); // Initially hidden

    connect(authButton, &QPushButton::clicked, [this, addButton]() {
        RegisterPage *registerpage = new RegisterPage(this);
        connect(registerpage, &RegisterPage::backToMain, this, [this]() {
            stackedWidget->setCurrentWidget(mainPage);
        });

        connect(registerpage, &RegisterPage::switchToLogin, this, [this, registerpage, addButton] {
            LoginPage* loginpage = new LoginPage(this);
            connect(loginpage, &LoginPage::backToMain, this, [this]() {
                stackedWidget->setCurrentWidget(mainPage);
            });

            connect(loginpage, &LoginPage::userLoggedIn, this, [this, addButton](const std::string& username, const std::string mode) {
                setCurrentUser(username);
                if (mode == "1") {
                    addButton->setVisible(true); // Show the "Добавить" button when mode=1
                } else {
                    addButton->setVisible(false); // Hide otherwise
                }
            });

            stackedWidget->addWidget(loginpage);
            stackedWidget->setCurrentWidget(loginpage);
        });

        connect(registerpage, &RegisterPage::userRegIn, this, [this, addButton](const std::string& username, const std::string mode) {
            setCurrentUser(username);
            if (mode == "1") {
                addButton->setVisible(true); // Show the "Добавить" button when mode=1
            } else {
                addButton->setVisible(false); // Hide otherwise
            }
        });

        stackedWidget->addWidget(registerpage);
        stackedWidget->setCurrentWidget(registerpage);
    });

    // Add the addButton to the layout
    categoryLayout->addWidget(authButton);
    categoryLayout->addWidget(addButton);
}

void MainWindow::addProduct(const std::string &imagePath, const std::string &name, const std::string &mass, const std::string &price) {
    ProductWidget *productWidget = new ProductWidget(imagePath, name, mass, price);
    Food* reader = new Food(types);
    std::vector<std::vector<std::string>> props = reader->setPropsList();
    std::vector<std::string> prop;
    std::vector<std::string> prods = reader->setProdsList();
    for (int i = 0; i < prods.size(); ++i) {
        if (prods[i] == name) {
            prop = props[i];
        }
    }
    connect(productWidget, &ProductWidget::clicked, [this, imagePath, name, prop]() {

        QFile adds("/Users/oxydear/Documents/Ivan's Mac/BSUIR/OOP/course/foodApp/assets/adds.txt");

        if (!adds.open(QIODevice::ReadWrite | QIODevice::Text)) {
            std::cerr << "Could not open file" << std::endl;
        }

        QTextStream ins(&adds);
        QString content = ins.readAll(); // Read the entire file content
        adds.resize(0); // Clear the file for writing
        QStringList is = content.split(';');

        bool ad = false;

        for (auto &el : is) {

            int pos;
            std::string token;
            std::string dataEl = el.toStdString();

            while ((pos = dataEl.find(':')) != std::string::npos) {
                token = dataEl.substr(0, pos);
                dataEl.erase(0, pos + 1);
            }

            std::string tk = token.c_str();
            std::string nk = name.c_str();
            if (!token.empty() and token == name) {
                QFile fl(QString::fromStdString(imagePath+"/images/"+dataEl));
                showProductPage(imagePath + "/images/", dataEl, prop);
                ad = true;
            } else {
                continue;
            }
        }
        if (!ad) {
            showProductPage(imagePath + "/images", name, prop);
        }

        // showProductPage(imagePath + "/images/" + name, prop);
    });

    scrollLayout->addWidget(productWidget);
}

void MainWindow::showProductPage(const std::string &imagePath, const std::string &name, std::vector<std::string> props) {
    // Создаем новый виджет для отображения страницы товара
    QWidget *productDetailsPage = new QWidget(this);
    QVBoxLayout *productLayout = new QVBoxLayout(productDetailsPage);
    productLayout->setContentsMargins(10, 10, 10, 10); // Отступы у вертикального компоновщика
    productLayout->setSpacing(10); // Расстояние между элементами

    // Загружаем изображение
    QPixmap pixmap(QString::fromStdString(imagePath+"/"+name));
    QLabel *mainImageLabel = new QLabel(); // Создаем метку для изображения
    if (pixmap.isNull()) {
        QDir dir(QString::fromStdString(imagePath));
        QStringList allEntries = dir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot);
        mainImageLabel->setPixmap(QPixmap(QString::fromStdString(imagePath+"/"+allEntries[0].toStdString())).scaled(200, 200, Qt::KeepAspectRatio));
    } else {
        QFile fl(QString::fromStdString(imagePath+"/"+name));
        mainImageLabel->setPixmap(QPixmap(QString::fromStdString(imagePath+"/"+name)).scaled(200, 100, Qt::KeepAspectRatio).scaled(200, 200, Qt::KeepAspectRatio));
    }
    // mainImageLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));
    mainImageLabel->setAlignment(Qt::AlignLeft); // Выравниваем изображение по центру
    productLayout->addWidget(mainImageLabel); // Добавляем изображение в основной компоновщик

    // Создаем вертикальный компоновщик для свойств
    QVBoxLayout *textLayout = new QVBoxLayout();
    textLayout->setSpacing(5); // Расстояние между элементами
    textLayout->setContentsMargins(10, 10, 10, 10); // Установите отступы вокруг layout

    // Добавляем содержимое вектора props
    for (const auto &p : props) {
        QHBoxLayout *hLayout = new QHBoxLayout();
        QLabel *propLabel = new QLabel(QString::fromStdString(p));
        propLabel->setStyleSheet("margin: 0; padding: 0; font-size: 14px;");
        hLayout->addWidget(propLabel);
        hLayout->setContentsMargins(0, 0, 0, 0); // Убираем отступы у горизонтального компоновщика
        hLayout->addStretch(); // Добавляем растяжение для создания отступов справа

        textLayout->addLayout(hLayout);
    }

    // Добавляем вертикальный виджет с текстом под изображением
    QWidget *textWidget = new QWidget();
    textWidget->setLayout(textLayout);
    productLayout->addWidget(textWidget); // Добавляем текстовый виджет под изображением

    // Кнопка "Назад"
    QPushButton *backButton = new QPushButton("Назад", this);
    backButton->setStyleSheet("QPushButton { padding: 10px; font-size: 16px; }"
                              "QPushButton:hover { color: #bbb; }");
    connect(backButton, &QPushButton::clicked, [this]() {
        stackedWidget->setCurrentWidget(mainPage);
    });

    // Добавляем кнопку под текстовыми элементами
    productLayout->addWidget(backButton);

    // Устанавливаем новый виджет на стек
    stackedWidget->addWidget(productDetailsPage);
    stackedWidget->setCurrentWidget(productDetailsPage);
}

void MainWindow::updateProductList(std::string pricelow, std::string pricemax) {
    // Очистить текущий контент
    QLayoutItem* item;
    while ((item = scrollLayout->takeAt(0)) != nullptr) {
        delete item->widget(); // Удаляем виджет
        delete item; // Удаляем элемент
    }

    // Здесь вы можете заново заполнить scrollLayout с нужными продуктами
    Food *reader = new Food(types);
    std::vector<std::string> prods = reader->setProdsList();
    std::vector<std::vector<std::string>> props = reader->setPropsList();

    // Заполнение прокручиваемой области
    for (int i = 0; i < prods.size(); ++i) {
        if (pricelow == "" and pricemax == "") {
            try {
                addProduct(":/assets/FoodTypes/" + types, prods[i], props[i][props[i].size()-2], props[i][props[i].size()-1]);
            } catch(...) {
                continue;
            }
        } else if (pricelow == "") {
            if (stod(props[i][props[i].size()-1]) <= stod(pricemax)) {
                try {
                    addProduct(":/assets/FoodTypes/" + types, prods[i], props[i][props[i].size()-2], props[i][props[i].size()-1]);
                } catch(...) {
                    continue;
                }
            }
        } else if (pricemax == "") {
            if (stod(props[i][props[i].size()-1]) >= stod(pricelow)) {
                try {
                    addProduct(":/assets/FoodTypes/" + types, prods[i], props[i][props[i].size()-2], props[i][props[i].size()-1]);
                } catch(...) {
                    continue;
                }
            }
        } else {
            if (stod(props[i][props[i].size()-1]) <= stod(pricemax) and stod(props[i][props[i].size()-1]) >= stod(pricelow) ) {
                try {
                    addProduct(":/assets/FoodTypes/" + types, prods[i], props[i][props[i].size()-2], props[i][props[i].size()-1]);
                } catch(...) {
                    continue;
                }
            }
        }
        // addProduct(":/assets/FoodTypes/" + types, prods[i], props[i][props[i].size()-2], props[i][props[i].size()-1]);
    }
}

void MainWindow::updateUserStatusAdd(const std::string &username) {
    QFile file("/Users/oxydear/Documents/Ivan's Mac/BSUIR/OOP/course/foodApp/users/users.txt");

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл users.txt";
        return;
    }

    QStringList lines;
    QTextStream in(&file);

    // Чтение всех строк файла
    while (!in.atEnd()) {
        QString line = in.readLine();
        // Проверка, является ли текущая строка той, что нам нужна
        if (line.startsWith(QString::fromStdString(username) + ":")) {
            QStringList parts = line.split(":");
            if (parts.size() > 2) {
                // Изменение последнего элемента на 1
                parts[2] = "1";
                line = parts.join(":");
            }
        }
        lines.append(line);
    }

    // Перезапись файла с обновленными данными
    file.resize(0); // Очистка файла
    QTextStream out(&file);
    for (const QString &line : lines) {
        out << line << "\n"; // Запись строк обратно в файл
    }

    file.close();
}

void MainWindow::updateUserStatusDelete(const std::string &username) {
    QFile file("/Users/oxydear/Documents/Ivan's Mac/BSUIR/OOP/course/foodApp/users/users.txt");

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл users.txt";
        return;
    }

    QStringList lines;
    QTextStream in(&file);

    // Чтение всех строк файла
    while (!in.atEnd()) {
        QString line = in.readLine();
        // Проверка, является ли текущая строка той, что нам нужна
        if (line.startsWith(QString::fromStdString(username) + ":")) {
            QStringList parts = line.split(":");
            if (parts.size() > 2) {
                // Изменение последнего элемента на 1
                parts[2] = "0";
                line = parts.join(":");
            }
        }
        lines.append(line);
    }

    // Перезапись файла с обновленными данными
    file.resize(0); // Очистка файла
    QTextStream out(&file);
    for (const QString &line : lines) {
        out << line << "\n"; // Запись строк обратно в файл
    }

    file.close();
}

void MainWindow::updateName(const std::string &name, const std::string &editedName) {
    std::vector<std::string> filePaths = {"Burger/BurgerTypes.txt", "Drink/DrinkTypes.txt", "FoodBox/FoodTypes.txt", "Salad/SaladTypes.txt", "Sauce/SauceTypes.txt", "Snack/SnackTypes.txt", "Soup/SoupTypes.txt"};
    std::vector<std::string> imgPaths = {"Burger", "Drink", "FoodBox", "Salad", "Sauce", "Snack", "Soup"};
    for (int i = 0; i < filePaths.size(); ++i) {
        QFile file("/Users/oxydear/Documents/Ivan's Mac/BSUIR/OOP/course/foodApp/assets/FoodTypes/"+QString::fromStdString(filePaths[i]));

        // Open the file for reading and writing
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            std::cerr << "Could not open file: " << filePaths[i] << std::endl;
            continue; // Move to the next file
        }

        QTextStream in(&file);
        QString content = in.readAll(); // Read the entire file content
        file.resize(0); // Clear the file for writing

        // Split the content by ';' and replace occurrences of name
        QStringList items = content.split(';');
        for (QString &item : items) {
            if (item.trimmed() == QString::fromStdString(name)) {
                // img.rename("/Users/oxydear/Documents/Ivan's Mac/BSUIR/OOP/course/foodApp/assets/FoodTypes/"+QString::fromStdString(imgPaths[i]) + "/images/" + QString::fromStdString(editedName) + ".png");
                QFile adds("/Users/oxydear/Documents/Ivan's Mac/BSUIR/OOP/course/foodApp/assets/adds.txt");

                if (!adds.open(QIODevice::ReadWrite | QIODevice::Text)) {
                    std::cerr << "Could not open file" << std::endl;
                    continue; // Move to the next file
                }

                QTextStream ins(&adds);
                QString content = ins.readAll(); // Read the entire file content
                adds.resize(0); // Clear the file for writing
                QStringList is = content.split(';');
                bool as = false;

                for (int i = 0; i < is.size(); ++i) {
                    int pos;
                    std::string token;
                    std::string dataEl = is[i].toStdString();

                    while ((pos = dataEl.find(':')) != std::string::npos) {
                        token = dataEl.substr(0, pos);
                        dataEl.erase(0, pos + 1);
                    }

                    if (dataEl == editedName) {
                        is[i] = QString::fromStdString(editedName + ":" + item.toStdString());
                        as = true;
                    }
                }

                if (!as) {
                    is << QString::fromStdString(editedName + ":" + item.toStdString() + ";");
                }
                QTextStream out(&adds);
                out << is.join(';'); // Join items with ';' and add the delimiter at the end
                adds.close();

                // adds[editedName] = item.toStdString();
                item = QString::fromStdString(editedName); // Replace with editedName
                break;
            }

        }

        // Write the modified content back to the file
        QTextStream out(&file);
        out << items.join(';'); // Join items with ';' and add the delimiter at the end

        file.close(); // Close the file
    }
}

void MainWindow::updateDelete(const std::string &name) {
    std::vector<std::string> filePaths = {"Burger/BurgerTypes.txt", "Drink/DrinkTypes.txt", "FoodBox/FoodTypes.txt", "Salad/SaladTypes.txt", "Sauce/SauceTypes.txt", "Snack/SnackTypes.txt", "Soup/SoupTypes.txt"};
    std::vector<std::string> imgPaths = {"Burger", "Drink", "FoodBox", "Salad", "Sauce", "Snack", "Soup"};
    for (int i = 0; i < filePaths.size(); ++i) {
        QFile file("/Users/oxydear/Documents/Ivan's Mac/BSUIR/OOP/course/foodApp/assets/FoodTypes/"+QString::fromStdString(filePaths[i]));

        // Open the file for reading and writing
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            std::cerr << "Could not open file: " << filePaths[i] << std::endl;
            continue; // Move to the next file
        }

        QTextStream in(&file);
        QString content = in.readAll(); // Read the entire file content
        file.resize(0); // Clear the file for writing

        // Split the content by ';' and replace occurrences of name
        QStringList items = content.split(';');
        for (int i = 0; i < items.size(); ++i) {
            if (items[i].trimmed() == QString::fromStdString(name)) {
                QFile fil("/Users/oxydear/Documents/Ivan's Mac/BSUIR/OOP/course/foodApp/assets/FoodTypes/"+QString::fromStdString(imgPaths[i])+"/"+QString::fromStdString(imgPaths[i])+"Props.txt");

                if (!fil.open(QIODevice::ReadWrite | QIODevice::Text)) {
                    std::cerr << "Could not open file" << std::endl;
                    continue; // Move to the next file
                }

                QTextStream ins(&fil);
                QString content = ins.readAll(); // Read the entire file content
                fil.resize(0); // Clear the file for writing
                QStringList is = content.split('\n');

                for (int i = 0; i < is.size(); ++i) {
                    std::string dataEl = is[i].toStdString();

                    if (dataEl == name) {
                        is.erase(is.begin()+i);
                    }
                }

                QTextStream out(&fil);
                out << is.join('\n'); // Join items with '\n' and add the delimiter at the end
                fil.close();

                items.erase(items.begin() + i); // Replace with editedName
                break;
            }

        }

        // Write the modified content back to the file
        QTextStream out(&file);
        out << items.join(';'); // Join items with ';' and add the delimiter at the end

        file.close(); // Close the file
    }
}

void MainWindow::updateAdd(const std::string &name, const std::string &desc) {
    std::vector<std::string> filePaths = {"Burger/BurgerTypes.txt", "Drink/DrinkTypes.txt", "FoodBox/FoodTypes.txt", "Salad/SaladTypes.txt", "Sauce/SauceTypes.txt", "Snack/SnackTypes.txt", "Soup/SoupTypes.txt"};
    std::vector<std::string> imgPaths = {"Burger", "Drink", "FoodBox", "Salad", "Sauce", "Snack", "Soup"};
    for (int i = 0; i < filePaths.size(); ++i) {
        QFile file("/Users/oxydear/Documents/Ivan's Mac/BSUIR/OOP/course/foodApp/assets/FoodTypes/"+QString::fromStdString(filePaths[i]));
        QFile fil("/Users/oxydear/Documents/Ivan's Mac/BSUIR/OOP/course/foodApp/assets/FoodTypes/"+QString::fromStdString(imgPaths[i])+"/"+QString::fromStdString(imgPaths[i])+"Props.txt");


        // Open the file for reading and writing
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            std::cerr << "Could not open file" << std::endl;
            continue; // Move to the next file
        }

        if (!fil.open(QIODevice::ReadWrite | QIODevice::Text)) {
            std::cerr << "Could not open file" << std::endl;
            continue; // Move to the next file
        }

        QTextStream in(&file);
        QString content = in.readAll(); // Read the entire file content
        file.resize(0); // Clear the file for writing

        QTextStream ins(&fil);
        QString cont = ins.readAll(); // Read the entire file content
        fil.resize(0); // Clear the file for writing

        // Split the content by ';' and replace occurrences of name
        QStringList items = content.split(';');
        if (items.back() == '\n') {
            items.pop_back();
        }
        QStringList props = cont.split('\n');
        if (props.back().isEmpty()) {
            props.pop_back();
        }
        items << QString::fromStdString(name);
        props << QString::fromStdString(desc);

        // Write the modified content back to the file
        QTextStream out(&file);
        QTextStream outs(&fil);
        out << items.join(';'); // Join items with ';' and add the delimiter at the end
        out << ";";
        outs << props.join('\n'); // Join items with '\n' and add the delimiter at the end
        outs << '\n';

        file.close(); // Close the file
        fil.close();
    }
}

void MainWindow::setCurrentUser(const std::string &username) {
    if (currentUser) {
        delete currentUser; // Удаляем предыдущего пользователя
    }
    currentUser = new User(username); // Создаем нового пользователя
    userLabel->setText(QString("Пользователь: %1").arg(QString::fromStdString(currentUser->getUsername())));
    qDebug() << "Пользователь вошел:" << currentUser->getUsername();
}
