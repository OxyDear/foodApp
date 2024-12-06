#include "../hfiles/adminpage.h"
#include <QLabel>
#include <QPushButton>
// #include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QFont>
#include <iostream>

AdminPage::AdminPage(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void AdminPage::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter); // Center all elements

    // Header with title and back button
    QHBoxLayout *headerLayout = new QHBoxLayout();
    QLabel *titleLabel = new QLabel("Админ Панель");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24); // Increase font size
    titleLabel->setFont(titleFont);
    headerLayout->addWidget(titleLabel);

    // Back button
    QPushButton *backButton = new QPushButton("Назад", this);
    backButton->setFixedSize(100, 40); // Size of the button
    headerLayout->addWidget(backButton, 0, Qt::AlignRight);
    connect(backButton, &QPushButton::clicked, this, [this]() {
        emit backToMain(); // Signal to switch back to the main page
    });

    layout->addLayout(headerLayout); // Add header to the main layout

    // Buttons for admin actions
    QVBoxLayout *buttonsLayout = new QVBoxLayout();

    QStringList adminActions = {"Изменить", "Добавить", "Удалить", "Админ Добавить", "Aдмин Удалить"};
    for (const QString &action : adminActions) {
        QPushButton *actionButton = new QPushButton(action, this);
        actionButton->setFixedSize(250, 45); // Size of the buttons
        QFont buttonFont = actionButton->font();
        buttonFont.setPointSize(16); // Increase font size for buttons
        actionButton->setFont(buttonFont);
        buttonsLayout->addWidget(actionButton);

        // Connect each button's signal
        connect(actionButton, &QPushButton::clicked, this, [this, action, layout]() {
            // emit adminActionTriggeredAdd(action.toStdString()); // Emit action triggered signal

            showUsernameInput(layout, action.toStdString()); // Show username input when "Админ" is clicked
        });
    }

    layout->addLayout(buttonsLayout); // Add action buttons to the main layout
    layout->addStretch(); // Add stretch to keep elements centered
}

void AdminPage::showUsernameInput(QVBoxLayout *layout, const std::string &action) {
    // Create a QLineEdit for username input
    QLineEdit *usernameInput = new QLineEdit(this);
    usernameInput->setPlaceholderText("Введите имя пользователя");
    usernameInput->setFixedWidth(250); // Set width
    usernameInput->setStyleSheet("padding: 5px; border: 1px solid #aaa; border-radius: 5px;");

    // Create a button to confirm the input
    // QPushButton *confirmButton = new QPushButton("Подтвердить", this);
    // confirmButton->setFixedWidth(250); // Optionally set the same width as QLineEdit

    QPushButton *confirmButton = new QPushButton("Confirm", this);
    confirmButton->setFixedSize(250, 45); // Размер кнопки
    confirmButton->setStyleSheet("QPushButton { padding: 10px; font-size: 16px; }"
                             "QPushButton:hover { color: #bbb; }");

    // Layout for the username input
    QVBoxLayout *inputLayout = new QVBoxLayout(); // Use vertical layout
    inputLayout->addWidget(usernameInput);
    inputLayout->addWidget(confirmButton);
    // inputLayout->setAlignment(confirmButton, Qt::AlignCenter); // Выравнивание кнопки по центру

    // Add the input layout to the main layout
    layout->addLayout(inputLayout); // Add to the existing layout

    // Connect the confirm button
    connect(confirmButton, &QPushButton::clicked, this, [this, usernameInput, inputLayout, layout, confirmButton, action]() {
        QString username = usernameInput->text();
        // Process the username input here (e.g., emit a signal or handle it directly)
        if (std::strcmp(action.c_str(), "Админ Добавить")) {
            std::cout << "ADD" << " ";
            emit adminActionTriggeredAdd(username.toStdString());
        }
        if (std::strcmp(action.c_str(), "Админ Удалить")) {
            std::cout << "DEL" << " ";
            emit adminActionTriggeredDelete(username.toStdString());
        }


        // Clear the input field and remove the layout after use
        usernameInput->clear();
        usernameInput->setVisible(false);
        confirmButton->setVisible(false);
        layout->removeItem(inputLayout);
        delete inputLayout; // Clean up
    });
}
