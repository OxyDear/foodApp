#include "../hfiles/registerpage.h"
#include <QMessageBox>
#include <QFont>
#include <QHBoxLayout>

RegisterPage::RegisterPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter); // Центрируем все элементы

    // Заголовок с кнопкой
    QHBoxLayout *headerLayout = new QHBoxLayout();
    QLabel *titleLabel = new QLabel("Регистрация");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24); // Увеличиваем размер шрифта
    titleLabel->setFont(titleFont);
    headerLayout->addWidget(titleLabel);

    // Кнопка "Log In"
    QPushButton *loginButton = new QPushButton("Log In", this);
    loginButton->setFixedSize(100, 40); // Размер кнопки
    headerLayout->addWidget(loginButton, 0, Qt::AlignRight);

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
    registerButton = new QPushButton("Зарегистрироваться", this);
    registerButton->setFixedSize(200, 50); // Увеличиваем размер кнопки
    QFont buttonFont = registerButton->font();
    buttonFont.setPointSize(16); // Увеличиваем размер шрифта кнопки
    registerButton->setFont(buttonFont);
    connect(registerButton, &QPushButton::clicked, this, &RegisterPage::handleRegister);
    layout->addWidget(registerButton);

    // Кнопка назад
    QPushButton* backButton = new QPushButton("Назад", this);
    backButton->setFixedSize(200, 50); // Увеличиваем размер кнопки
    backButton->setFont(buttonFont); // Используем тот же шрифт
    // connect(backButton, &QPushButton::clicked, this, &RegisterPage::backToMain);
    connect(backButton, &QPushButton::clicked, this, [this]() {
        emit backToMain(); // Сигнал для переключения на страницу логинизации
    });
    layout->addWidget(backButton);

    // Связываем кнопку "Log In" с переходом на страницу логинизации
    connect(loginButton, &QPushButton::clicked, this, [this]() {
        emit switchToLogin(); // Сигнал для переключения на страницу логинизации
    });

    layout->addStretch(); // Добавляем растяжение, чтобы элементы оставались по центру
}


void RegisterPage::handleRegister() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    QMessageBox::information(this, "Регистрация", "Регистрация выполнена для: " + username);
    emit backToMain(); // Возвращаем на главную страницу
}
