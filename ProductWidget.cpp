#include "ProductWidget.h"
#include <QMouseEvent>

ProductWidget::ProductWidget(const QString &imagePath, const QString &name, QWidget *parent)
    : QWidget(parent), imagePath(imagePath) {

    QHBoxLayout *layout = new QHBoxLayout(this);

    productImage = new QLabel();
    productImage->setPixmap(QPixmap(imagePath).scaled(100, 100, Qt::KeepAspectRatio));
    productImage->setFixedSize(100, 100);

    productName = new QLabel(name);

    layout->addWidget(productImage);
    layout->addWidget(productName);
    setLayout(layout);
    setCursor(Qt::PointingHandCursor); // Изменяем курсор при наведении
}

void ProductWidget::mousePressEvent(QMouseEvent *event) {
    emit clicked(); // Генерируем сигнал при нажатии
    QWidget::mousePressEvent(event); // Вызываем базовый реализацию
}
