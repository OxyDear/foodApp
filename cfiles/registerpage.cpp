#include "../hfiles/registerpage.h"
#include "../hfiles/encrypt.h"
#include <QMessageBox>
#include <QFont>
#include <QFile>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

RegisterPage::RegisterPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(30, 30, 30, 30); // Увеличиваем отступы

    // Заголовок с кнопкой
    QHBoxLayout *headerLayout = new QHBoxLayout();
    QLabel *titleLabel = new QLabel("Регистрация");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24); // Увеличиваем размер шрифта
    titleLabel->setFont(titleFont);
    headerLayout->addWidget(titleLabel);

    // Кнопка "Log In"
    QPushButton *loginButton = new QPushButton("Log In", this);
    loginButton->setFixedSize(100, 40);
    loginButton->setStyleSheet("QPushButton { padding: 10px; font-size: 16px; }"
                               "QPushButton:hover { color: #bbb; }");
    // loginButton->setStyleSheet("font-size: 14px; background-color: #bbb; color: #333; border: none; border-radius: 5px;");
    connect(loginButton, &QPushButton::clicked, this, [this]() {
        emit switchToLogin();
    });
    headerLayout->addWidget(loginButton, 0, Qt::AlignRight); // Выровнять вправо
    layout->addLayout(headerLayout); // Добавляем заголовок с кнопкой в основной макет

    // Логин
    layout->addWidget(new QLabel("Логин:", this));
    usernameEdit = new QLineEdit(this);
    usernameEdit->setFixedWidth(250);
    usernameEdit->setStyleSheet("padding: 5px; border: 1px solid #aaa; border-radius: 5px;"); // Нейтральный цвет рамки
    // usernameEdit->setStyleSheet("padding: 10px; font-size: 16px;");
    layout->addWidget(usernameEdit);

    // Пароль
    layout->addWidget(new QLabel("Пароль:", this));
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setFixedWidth(250);
    passwordEdit->setStyleSheet("padding: 5px; border: 1px solid #aaa; border-radius: 5px;");
    // passwordEdit->setStyleSheet("padding: 10px; font-size: 16px;");
    layout->addWidget(passwordEdit);
    layout->addSpacing(20);

    // Кнопка регистрации
    registerButton = new QPushButton("Зарегистрироваться", this);
    registerButton->setFixedSize(200, 50);
    // registerButton->setStyleSheet("font-size: 16px; padding: 10px; background-color: #ccc; color: #333; border: none; border-radius: 5px;"); // Нейтральный цвет кнопки
    registerButton->setStyleSheet("QPushButton { padding: 10px; font-size: 16px; } "
                                  "QPushButton:hover { color: #bbb; }");
    connect(registerButton, &QPushButton::clicked, this, &RegisterPage::handleRegister);
    layout->addWidget(registerButton, 0, Qt::AlignCenter); // Центрируем кнопку

    // Кнопка назад
    QPushButton* backButton = new QPushButton("Назад", this);
    backButton->setFixedSize(200, 50);
    backButton->setStyleSheet("QPushButton { padding: 10px; font-size: 16px; }"
                              "QPushButton:hover { color: #bbb; }");
    // backButton->setStyleSheet("font-size: 16px; padding: 10px; background-color: #ccc; color: #333; border: none; border-radius: 5px;"); // Нейтральный цвет кнопки
    connect(backButton, &QPushButton::clicked, this, [this]() {
        emit backToMain();
    });
    layout->addWidget(backButton, 0, Qt::AlignCenter); // Центрируем кнопку

    layout->addStretch(); // Добавляем растяжение, чтобы элементы оставались по центру
}

void RegisterPage::handleRegister() {
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }

    QFile file("/Users/oxydear/Documents/Ivan's Mac/BSUIR/OOP/course/foodApp/users/users.txt");
    bool userExists = false;

    // Проверяем, существует ли файл
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line;

        // Проверяем наличие логина в файле
        while (in.readLineInto(&line)) {
            if (line.startsWith(username + ":")) {
                userExists = true;
                break; // Логин найден, выходим из цикла
            }
        }
        file.close(); // Закрываем файл
    }

    // Если логин уже существует, показываем сообщение
    if (userExists) {
        // QMessageBox::warning(this, "Ошибка", "Этот логин уже существует. Пожалуйста, выберите другой.");
        return; // Выходим из функции
    }

    // Открываем файл для записи
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << username << ":" << password << ":0" << "\n"; // Записываем в файл
        file.close(); // Закрываем файл
    } else {
        // QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи.");
        return; // Выходим из функции, если файл не открывается
    }

    emit userRegIn(username.toStdString(), "0");
    emit backToMain(); // Возвращаем на главную страницу
}
