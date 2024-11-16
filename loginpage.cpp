#include "loginpage.h"
#include <QMessageBox>
#include <QFont>

LoginPage::LoginPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter); // Центрируем все элементы

    // Заголовок с кнопкой
    QHBoxLayout *headerLayout = new QHBoxLayout();
    QLabel *titleLabel = new QLabel("Вход");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24); // Увеличиваем размер шрифта
    titleLabel->setFont(titleFont);
    headerLayout->addWidget(titleLabel);

    // Кнопка "Log In"
    QPushButton *regButton = new QPushButton("Reg In", this);
    regButton->setFixedSize(100, 40); // Размер кнопки
    headerLayout->addWidget(regButton, 0, Qt::AlignRight); // Выравнивание по правому краю

    layout->addLayout(headerLayout); // Добавляем заголовок с кнопкой в основной макет

    // Логин
    layout->addWidget(new QLabel("Логин:"));
    usernameEdit = new QLineEdit(this);
    usernameEdit->setFixedWidth(250); // Увеличиваем ширину
    layout->addWidget(usernameEdit);

    // Пароль
    layout->addWidget(new QLabel("Пароль:"));
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setFixedWidth(250); // Увеличиваем ширину
    layout->addWidget(passwordEdit);

    // Кнопка регистрации
    loginButton = new QPushButton("Войти", this);
    loginButton->setFixedSize(200, 50); // Увеличиваем размер кнопки
    QFont buttonFont = loginButton->font();
    buttonFont.setPointSize(16); // Увеличиваем размер шрифта кнопки
    loginButton->setFont(buttonFont);
    connect(loginButton, &QPushButton::clicked, this, &LoginPage::handleLogin);
    layout->addWidget(loginButton);

    // Кнопка назад
    QPushButton* backButton = new QPushButton("Назад", this);
    backButton->setFixedSize(200, 50); // Увеличиваем размер кнопки
    backButton->setFont(buttonFont); // Используем тот же шрифт
    // connect(backButton, &QPushButton::clicked, this, &LoginPage::backToMain);
    connect(backButton, &QPushButton::clicked, this, [this]() {
        emit backToMain();
    });
    layout->addWidget(backButton);

    // Связываем кнопку "Log In" с переходом на страницу логинизации
    connect(regButton, &QPushButton::clicked, this, [this]() {
        emit switchToRegister(); // Сигнал для переключения на страницу логинизации
    });

    layout->addStretch(); // Добавляем растяжение, чтобы элементы оставались по центру
}

void LoginPage::handleLogin() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    // Здесь добавьте логику для входа
    QMessageBox::information(this, "Вход", "Вход выполнен как: " + username);
    emit backToMain();
    // Логика входа...
}
