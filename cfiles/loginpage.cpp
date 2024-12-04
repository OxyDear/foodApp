#include "../hfiles/loginpage.h"
#include "../hfiles/encrypt.h"
#include <QMessageBox>
#include <QFont>
#include <QFile>

LoginPage::LoginPage(QWidget *parent) : QWidget(parent) {

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter); // Центрируем все элементы
    layout->setContentsMargins(30, 30, 30, 30);

    // Заголовок с кнопкой
    QHBoxLayout *headerLayout = new QHBoxLayout();
    QLabel *titleLabel = new QLabel("Вход");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24); // Увеличиваем размер шрифта
    titleLabel->setFont(titleFont);
    headerLayout->addWidget(titleLabel);

    // Кнопка "Reg In"
    QPushButton *regButton = new QPushButton("Reg In", this);
    regButton->setFixedSize(100, 40); // Размер кнопки
    regButton->setStyleSheet("QPushButton { padding: 10px; font-size: 16px; }"
                             "QPushButton:hover { color: #bbb; }");
    connect(regButton, &QPushButton::clicked, this, [this]() {
        emit switchToRegister();
    });
    headerLayout->addWidget(regButton, 0, Qt::AlignRight); // Выравнивание по правому краю
    layout->addLayout(headerLayout); // Добавляем заголовок с кнопкой в основной макет

    // Логин
    layout->addWidget(new QLabel("Логин:"));
    usernameEdit = new QLineEdit(this);
    usernameEdit->setFixedWidth(250); // Увеличиваем ширину
    usernameEdit->setStyleSheet("padding: 5px; border: 1px solid #aaa; border-radius: 5px;");
    layout->addWidget(usernameEdit);

    // Пароль
    layout->addWidget(new QLabel("Пароль:"));
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setFixedWidth(250); // Увеличиваем ширину
    passwordEdit->setStyleSheet("padding: 5px; border: 1px solid #aaa; border-radius: 5px;");
    layout->addWidget(passwordEdit);

    layout->addSpacing(20);

    // Кнопка регистрации
    loginButton = new QPushButton("Войти", this);
    loginButton->setFixedSize(200, 50); // Увеличиваем размер кнопки
    loginButton->setStyleSheet("QPushButton { padding: 10px; font-size: 16px; }"
                               "QPushButton:hover { color: #bbb; }");
    // layout->addWidget(regButton, 0, Qt::AlignCenter); // Центрируем кнопку
    QFont buttonFont = loginButton->font();
    buttonFont.setPointSize(16); // Увеличиваем размер шрифта кнопки
    loginButton->setFont(buttonFont);
    connect(loginButton, &QPushButton::clicked, this, &LoginPage::handleLogin);
    layout->addWidget(loginButton, 0, Qt::AlignCenter);

    // Кнопка назад
    QPushButton* backButton = new QPushButton("Назад", this);
    backButton->setFixedSize(200, 50); // Увеличиваем размер кнопки
    backButton->setFont(buttonFont); // Используем тот же шрифт
    backButton->setStyleSheet("QPushButton { padding: 10px; font-size: 16px; }"
                              "QPushButton:hover { color: #bbb; }");
    // connect(backButton, &QPushButton::clicked, this, &LoginPage::backToMain);
    connect(backButton, &QPushButton::clicked, this, [this]() {
        emit backToMain();
    });
    layout->addWidget(backButton, 0, Qt::AlignCenter);

    // Связываем кнопку "Log In" с переходом на страницу логинизации
    connect(regButton, &QPushButton::clicked, this, [this]() {
        emit switchToRegister(); // Сигнал для переключения на страницу логинизации
    });

    layout->addStretch(); // Добавляем растяжение, чтобы элементы оставались по центру
}

void LoginPage::handleLogin() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }

    // Открываем файл для чтения
    QFile file("/Users/oxydear/Documents/Ivan's Mac/BSUIR/OOP/course/foodApp/users/users.txt");
    bool userFound = false;

    // Проверяем, существует ли файл
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line;

        // Проверяем наличие логина и пароля в файле
        while (in.readLineInto(&line)) {
            QStringList credentials = line.split(":");
            // QString::fromStdString(hashPassword(password.toStdString()))
            if (credentials.size() == 2 && credentials[0] == username && credentials[1] == password) {
                userFound = true; // Логин и пароль совпадают
                break; // Выходим из цикла
            }
        }
        file.close(); // Закрываем файл
    } else {
        // QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для чтения.");
        return; // Выходим из функции
    }

    // Если пользователь не найден, показываем сообщение
    if (!userFound) {
        // QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль.");
        return; // Выходим из функции
    }

    // Если вход успешен
    if (userFound) {
        emit userLoggedIn(username.toStdString());
    }
    // QMessageBox::information(this, "Вход", "Вход выполнен как: " + username);
    emit backToMain();
}
