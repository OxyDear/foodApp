#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPixmap>

class ProductWidget : public QWidget {
    Q_OBJECT

public:
    explicit ProductWidget(const QString &imagePath, const QString &name, QWidget *parent = nullptr);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel *productImage;
    QLabel *productName;
    QString imagePath;
};

#endif // PRODUCTWIDGET_H
