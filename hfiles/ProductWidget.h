#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPixmap>

class ProductWidget : public QWidget {
    Q_OBJECT

public:
    explicit ProductWidget( const std::string &imagePath, const std::string &name, const std::string &mass, const std::string &price, QWidget *parent = nullptr);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel *productImage;
    QLabel *productName;
    const std::string imagePath;
};

#endif // PRODUCTWIDGET_H
