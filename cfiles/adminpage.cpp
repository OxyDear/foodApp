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
    // QLineEdit *usernameInput = new QLineEdit(this);
    // if (usernameInput == nullptr) {
    if (action == "Изменить") {
        showNameInput(layout, action);
        return;
    }

    if (action == "Добавить") {
        showAddInput(layout, action);
        return;
    }

    if (action == "Удалить") {
        showDeleteInput(layout, action);
        return;
    }

    if (std::strcmp(action.c_str(), "Админ Добавить") or std::strcmp(action.c_str(), "Админ Удалить")) {
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
            if (action == "Админ Добавить") {
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

    // } else {
    //     usernameInput->setFocus();
    // }

}

void AdminPage::showNameInput(QVBoxLayout *layout, const std::string &action) {
    // Create a QLineEdit for username input
    // QLineEdit *usernameInput = new QLineEdit(this);
    // if (usernameInput == nullptr) {
    QLineEdit *nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Введите название");
    nameInput->setFixedWidth(250); // Set width
    nameInput->setStyleSheet("padding: 5px; border: 1px solid #aaa; border-radius: 5px;");

    QLineEdit *editedNameInput = new QLineEdit(this);
    editedNameInput->setPlaceholderText("Введите измененное название");
    editedNameInput->setFixedWidth(250); // Set width
    editedNameInput->setStyleSheet("padding: 5px; border: 1px solid #aaa; border-radius: 5px;");

    // Create a button to confirm the input
    // QPushButton *confirmButton = new QPushButton("Подтвердить", this);
    // confirmButton->setFixedWidth(250); // Optionally set the same width as QLineEdit

    QPushButton *confirmButton = new QPushButton("Confirm", this);
    confirmButton->setFixedSize(250, 45); // Размер кнопки
    confirmButton->setStyleSheet("QPushButton { padding: 10px; font-size: 16px; }"
                                 "QPushButton:hover { color: #bbb; }");

    // Layout for the username input
    QVBoxLayout *inputLayout = new QVBoxLayout(); // Use vertical layout
    inputLayout->addWidget(nameInput);
    inputLayout->addWidget(editedNameInput);
    inputLayout->addWidget(confirmButton);
    // inputLayout->setAlignment(confirmButton, Qt::AlignCenter); // Выравнивание кнопки по центру

    // Add the input layout to the main layout
    layout->addLayout(inputLayout); // Add to the existing layout

    // Connect the confirm button
    connect(confirmButton, &QPushButton::clicked, this, [this, nameInput, editedNameInput, inputLayout, layout, confirmButton, action]() {
        QString name = nameInput->text();
        QString editedName = editedNameInput->text();
        // Process the username input here (e.g., emit a signal or handle it directly)
        if (action == "Изменить") {
            std::cout << "CHANGE_GOODS" << " ";
            emit adminActionTriggeredChange(name.toStdString(), editedName.toStdString());
        }


        // Clear the input field and remove the layout after use
        nameInput->clear();
        editedNameInput->clear();
        nameInput->setVisible(false);
        editedNameInput->setVisible(false);
        confirmButton->setVisible(false);
        layout->removeItem(inputLayout);
        delete inputLayout; // Clean up
    });
    // } else {
    //     usernameInput->setFocus();
    // }

}

void AdminPage::showDeleteInput(QVBoxLayout *layout, const std::string &action) {
    // Create a QLineEdit for username input
    // QLineEdit *usernameInput = new QLineEdit(this);
    // if (usernameInput == nullptr) {
    QLineEdit *nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Введите название");
    nameInput->setFixedWidth(250); // Set width
    nameInput->setStyleSheet("padding: 5px; border: 1px solid #aaa; border-radius: 5px;");

    // Create a button to confirm the input
    // QPushButton *confirmButton = new QPushButton("Подтвердить", this);
    // confirmButton->setFixedWidth(250); // Optionally set the same width as QLineEdit

    QPushButton *confirmButton = new QPushButton("Confirm", this);
    confirmButton->setFixedSize(250, 45); // Размер кнопки
    confirmButton->setStyleSheet("QPushButton { padding: 10px; font-size: 16px; }"
                                 "QPushButton:hover { color: #bbb; }");

    // Layout for the username input
    QVBoxLayout *inputLayout = new QVBoxLayout(); // Use vertical layout
    inputLayout->addWidget(nameInput);
    inputLayout->addWidget(confirmButton);
    // inputLayout->setAlignment(confirmButton, Qt::AlignCenter); // Выравнивание кнопки по центру

    // Add the input layout to the main layout
    layout->addLayout(inputLayout); // Add to the existing layout

    // Connect the confirm button
    connect(confirmButton, &QPushButton::clicked, this, [this, nameInput, inputLayout, layout, confirmButton, action]() {
        QString name = nameInput->text();
        // Process the username input here (e.g., emit a signal or handle it directly)
        if (action == "Удалить") {
            std::cout << "DELETE_GOODS" << " ";
            emit adminActionTriggeredDeleteOne(name.toStdString());
        }


        // Clear the input field and remove the layout after use
        nameInput->clear();
        nameInput->setVisible(false);
        confirmButton->setVisible(false);
        layout->removeItem(inputLayout);
        delete inputLayout; // Clean up
    });
    // } else {
    //     usernameInput->setFocus();
    // }

}


void AdminPage::showAddInput(QVBoxLayout *layout, const std::string &action) {
    // Create a QLineEdit for username input
    // QLineEdit *usernameInput = new QLineEdit(this);
    // if (usernameInput == nullptr) {
    QLineEdit *nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Введите название");
    nameInput->setFixedWidth(250); // Set width
    nameInput->setStyleSheet("padding: 5px; border: 1px solid #aaa; border-radius: 5px;");

    QLineEdit *descInput = new QLineEdit(this);
    descInput->setPlaceholderText("Введите описание");
    descInput->setFixedWidth(250); // Set width
    descInput->setStyleSheet("padding: 5px; border: 1px solid #aaa; border-radius: 5px;");

    // Create a button to confirm the input
    // QPushButton *confirmButton = new QPushButton("Подтвердить", this);
    // confirmButton->setFixedWidth(250); // Optionally set the same width as QLineEdit

    QPushButton *confirmButton = new QPushButton("Confirm", this);
    confirmButton->setFixedSize(250, 45); // Размер кнопки
    confirmButton->setStyleSheet("QPushButton { padding: 10px; font-size: 16px; }"
                                 "QPushButton:hover { color: #bbb; }");

    // Layout for the username input
    QVBoxLayout *inputLayout = new QVBoxLayout(); // Use vertical layout
    inputLayout->addWidget(nameInput);
    inputLayout->addWidget(descInput);
    inputLayout->addWidget(confirmButton);
    // inputLayout->setAlignment(confirmButton, Qt::AlignCenter); // Выравнивание кнопки по центру

    // Add the input layout to the main layout
    layout->addLayout(inputLayout); // Add to the existing layout

    // Connect the confirm button
    connect(confirmButton, &QPushButton::clicked, this, [this, nameInput, descInput, inputLayout, layout, confirmButton, action]() {
        QString name = nameInput->text();
        QString desc = descInput->text();
        // Process the username input here (e.g., emit a signal or handle it directly)
        if (action == "Добавить") {
            std::cout << "ADD_GOODS" << " ";
            emit adminActionTriggeredAddOne(name.toStdString(), desc.toStdString());
        }


        // Clear the input field and remove the layout after use
        nameInput->clear();
        descInput->clear();
        nameInput->setVisible(false);
        descInput->setVisible(false);
        confirmButton->setVisible(false);
        layout->removeItem(inputLayout);
        delete inputLayout; // Clean up
    });
    // } else {
    //     usernameInput->setFocus();
    // }

}
