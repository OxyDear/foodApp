#include "../hfiles/ProductWidget.h"
#include <QMouseEvent>
#include <QFile>
#include <QDir>
#include <iostream>
#include <QPalette>

ProductWidget::ProductWidget(const std::string &imagePath, const std::string name, QWidget *parent)
    : QWidget(parent), imagePath(imagePath) {

    QHBoxLayout *layout = new QHBoxLayout(this);

    QFile adds("/Users/oxydear/Documents/Ivan's Mac/BSUIR/OOP/course/foodApp/assets/adds.txt");

    if (!adds.open(QIODevice::ReadWrite | QIODevice::Text)) {
        std::cerr << "Could not open file" << std::endl;
    }

    QTextStream ins(&adds);
    QString content = ins.readAll(); // Read the entire file content
    adds.resize(0); // Clear the file for writing
    QStringList is = content.split(';');

    productImage = new QLabel();
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
            productImage->setPixmap(QPixmap(QString::fromStdString(imagePath+"/images/"+dataEl)).scaled(100, 100, Qt::KeepAspectRatio));
            ad = true;
        } else {
            continue;
        }
    }
    if (!ad) {
        QFile fl(QString::fromStdString(imagePath+"/images/"+name));
        if (QPixmap(QString::fromStdString(imagePath+"/images/"+name)).scaled(100, 100, Qt::KeepAspectRatio).isNull()) {
            QDir dir(QString::fromStdString(imagePath+"/images"));
            QStringList allEntries = dir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot);
            productImage->setPixmap(QPixmap(QString::fromStdString(imagePath+"/images/"+allEntries[0].toStdString())).scaled(100, 100, Qt::KeepAspectRatio));
        } else {
            productImage->setPixmap(QPixmap(QString::fromStdString(imagePath+"/images/"+name)).scaled(100, 100, Qt::KeepAspectRatio).scaled(100, 100, Qt::KeepAspectRatio));
        }
    }
    productImage->setFixedSize(100, 100);

    QTextStream out(&adds);
    out << is.join(';'); // Join items with ';' and add the delimiter at the end
    adds.close();

    productName = new QLabel(QString::fromStdString(name));
    // QFont font = productName->font();
    // font.setPointSize(18);
    // font.setBold(true);
    // productName->setFont(font);

    layout->addWidget(productImage);
    layout->addWidget(productName);
    setLayout(layout);
    setCursor(Qt::PointingHandCursor); // Изменяем курсор при наведении
}

void ProductWidget::enterEvent(QEnterEvent *event) {
    // Код, который выполняется при наведении курсора
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, "#4A4947"); // Установите нужный цвет
    this->setPalette(palette);
    this->setAutoFillBackground(true); // Включаем заливку фона

}

void ProductWidget::leaveEvent(QEvent *event) {
    // Сбрасываем цвет фона при уходе курсора
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, "#333333"); // Установите цвет по умолчанию
    this->setPalette(palette);

    QWidget::leaveEvent(event); // Вызываем базовую реализацию
}

void ProductWidget::mousePressEvent(QMouseEvent *event) {
    emit clicked(); // Генерируем сигнал при нажатии
    QWidget::mousePressEvent(event); // Вызываем базовый реализацию
}

