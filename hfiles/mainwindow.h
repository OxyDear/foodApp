#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString types = "Burger";

private:
    void setupUI();
    void addCategoryButton(QHBoxLayout *categoryLayout, const QString &name);
    void addAuthorizeButton(QHBoxLayout *categoryLayout, const QString &name);
    void addProduct(const QString &imagePath, const QString &name);
    void showProductPage(const QString &imagePath);

private:
    QScrollArea *scrollArea;
    QWidget *scrollWidget;
    QVBoxLayout *scrollLayout;

    QStackedWidget *stackedWidget;
    QWidget *mainPage;
    QWidget *productPage;

    QLabel *mainImageLabel;
    QPushButton *backButton;
};

#endif // MAINWINDOW_H
