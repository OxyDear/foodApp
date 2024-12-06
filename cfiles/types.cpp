#include "../hfiles/types.h"
#include <QMessageBox>
#include <QFont>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>

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
        emit backToMain("", "", ""); // Сигнал для переключения на главную страницу без параметров
    });

    layout->addLayout(headerLayout); // Добавляем заголовок с кнопкой в основной макет

    // Кнопки типов
    QVBoxLayout *buttonsLayout = new QVBoxLayout();
    QLineEdit *fromPriceEdit = new QLineEdit(this);
    QLineEdit *toPriceEdit = new QLineEdit(this);

    QStringList types = {"Burger", "Drink", "FoodBox", "Salad", "Sauce", "Snack", "Soup"};
    for (const QString &type : types) {
        QPushButton *typeButton = new QPushButton(type, this);
        typeButton->setFixedSize(250, 45); // Увеличиваем размер кнопок
        QFont buttonFont = typeButton->font();
        buttonFont.setPointSize(16); // Увеличиваем размер шрифта кнопок
        typeButton->setFont(buttonFont);
        buttonsLayout->addWidget(typeButton);

        // Подключаем сигнал на каждую кнопку
        connect(typeButton, &QPushButton::clicked, this, [this, type, fromPriceEdit, toPriceEdit]() {
            emit backToMain(type, fromPriceEdit->text().toStdString(), toPriceEdit->text().toStdString()); // Передаем тип обратно на главную страницу
        });
    }

    layout->addLayout(buttonsLayout); // Добавляем кнопки типов в основной макет

    layout->addStretch(); // Добавляем растяжение, чтобы элементы оставались по центру

    // Поля для ввода цен
    QVBoxLayout *priceLayout = new QVBoxLayout(); // Используем вертикальный макет

    // QLabel *fromLabel = new QLabel("Цена от:", this);
    // QLineEdit *fromPriceEdit = new QLineEdit(this);
    fromPriceEdit->setFixedWidth(250);
    fromPriceEdit->setStyleSheet("padding: 5px; border: 1px solid #aaa; border-radius: 5px;");
    fromPriceEdit->setPlaceholderText("Введите цену от"); // Подсказка для поля

    // QLabel *toLabel = new QLabel("Цена до:", this);
    // QLineEdit *toPriceEdit = new QLineEdit(this);
    toPriceEdit->setFixedWidth(250);
    toPriceEdit->setStyleSheet("padding: 5px; border: 1px solid #aaa; border-radius: 5px;");
    toPriceEdit->setPlaceholderText("Введите цену до"); // Подсказка для поля

    priceLayout->addWidget(fromPriceEdit);
    priceLayout->addWidget(toPriceEdit);

    layout->addLayout(priceLayout); // Добавляем макет цен в основной макет
}
