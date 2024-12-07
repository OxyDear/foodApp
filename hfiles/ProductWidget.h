#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPixmap>
#include <map>

class ProductWidget : public QWidget {
    Q_OBJECT

public:
    explicit ProductWidget( const std::string &imagePath, const std::string name, QWidget *parent = nullptr);

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
