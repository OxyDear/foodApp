#include "../hfiles/types.h"
#include <QMessageBox>
#include <QFont>
#include <QHBoxLayout>

TypesPage::TypesPage(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void TypesPage::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter); // Центрируем все элементы

    // Заголовок с кнопкой
    QHBoxLayout *headerLayout = new QHBoxLayout();
    QLabel *titleLabel = new QLabel("Типы товаров");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24); // Увеличиваем размер шрифта
    titleLabel->setFont(titleFont);
    headerLayout->addWidget(titleLabel);

    // Кнопка "Назад"
    QPushButton *backButton = new QPushButton("Назад", this);
    backButton->setFixedSize(100, 40); // Размер кнопки
    headerLayout->addWidget(backButton, 0, Qt::AlignRight);
    connect(backButton, &QPushButton::clicked, this, [this]() {
        emit backToMain(""); // Сигнал для переключения на главную страницу без параметров
    });

    layout->addLayout(headerLayout); // Добавляем заголовок с кнопкой в основной макет

    // Кнопки типов
    QVBoxLayout *buttonsLayout = new QVBoxLayout();

    QStringList types = {"Тип 1", "Тип 2", "Тип 3"};
    for (const QString &type : types) {
        QPushButton *typeButton = new QPushButton(type, this);
        typeButton->setFixedSize(250, 50); // Увеличиваем размер кнопок
        QFont buttonFont = typeButton->font();
        buttonFont.setPointSize(16); // Увеличиваем размер шрифта кнопок
        typeButton->setFont(buttonFont);
        buttonsLayout->addWidget(typeButton);

        // Подключаем сигнал на каждую кнопку
        connect(typeButton, &QPushButton::clicked, this, [this, type]() {
            emit backToMain(type); // Передаем тип обратно на главную страницу
        });
    }

    layout->addLayout(buttonsLayout); // Добавляем кнопки типов в основной макет

    layout->addStretch(); // Добавляем растяжение, чтобы элементы оставались по центру
}
