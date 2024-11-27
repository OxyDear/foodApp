#ifndef TYPESPAGE_H
#define TYPESPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>

class TypesPage : public QWidget {
    Q_OBJECT

public:
    explicit TypesPage(QWidget *parent = nullptr);

signals:
    void backToMain(const QString &type); // Сигнал для возврата на главную страницу с параметром

private:
    void setupUI();
};

#endif // TYPESPAGE_H
