#include "../hfiles/ProductWidget.h"
#include <QMouseEvent>

ProductWidget::ProductWidget(const std::string &imagePath, const std::string &name, QWidget *parent)
    : QWidget(parent), imagePath(imagePath) {

    QHBoxLayout *layout = new QHBoxLayout(this);

    productImage = new QLabel();
    productImage->setPixmap(QPixmap(QString::fromStdString(imagePath+"/images/"+name+".jpg")).scaled(220, 150, Qt::KeepAspectRatio));
    productImage->setFixedSize(220, 150);

    // productName = new QLabel(QString::fromStdString(name));

    layout->addWidget(productImage);
    // layout->addWidget(productName);
    setLayout(layout);
    setCursor(Qt::PointingHandCursor); // Изменяем курсор при наведении
}

void ProductWidget::mousePressEvent(QMouseEvent *event) {
    emit clicked(); // Генерируем сигнал при нажатии
    QWidget::mousePressEvent(event); // Вызываем базовый реализацию
}
