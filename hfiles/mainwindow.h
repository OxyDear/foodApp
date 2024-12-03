// #ifndef MAINWINDOW_H
// #define MAINWINDOW_H

// #include <QMainWindow>
// #include <QPushButton>
// #include <QScrollArea>
// #include <QVBoxLayout>
// #include <QHBoxLayout>
// #include <QLabel>
// #include <QStackedWidget>

// class MainWindow : public QMainWindow {
//     Q_OBJECT

// public:
//     MainWindow(QWidget *parent = nullptr);
//     ~MainWindow();
//     std::string types = "Burger";

// private:
//     void setupUI();
//     void addCategoryButton(QHBoxLayout *categoryLayout, const QString &name);
//     void addAuthorizeButton(QHBoxLayout *categoryLayout, const QString &name);
//     void addProduct(const std::string &imagePath, const std::string &name);
//     void showProductPage(const std::string &imagePath);
//     void updateProductList();

// private:
//     QScrollArea *scrollArea;
//     QWidget *scrollWidget;
//     QVBoxLayout *scrollLayout;

//     QStackedWidget *stackedWidget;
//     QWidget *mainPage;
//     QWidget *productPage;

//     QLabel *mainImageLabel;
//     QPushButton *backButton;
// };

// #endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <string>
#include "../users/User.h" // Подключаем User.h

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::string types = "Burger";

private:
    void setupUI();
    void addCategoryButton(QHBoxLayout *categoryLayout, const QString &name);
    void addProduct(const std::string &imagePath, const std::string &name);
    void showProductPage(const std::string &imagePath);
    void updateProductList();
    void setCurrentUser(const std::string &username); // Метод для установки текущего пользователя
    void addAuthorizeButton(QHBoxLayout *categoryLayout, const QString &name);

private:
    QScrollArea *scrollArea;
    QWidget *scrollWidget;
    QVBoxLayout *scrollLayout;

    QStackedWidget *stackedWidget;
    QWidget *mainPage;
    QWidget *productPage;

    QLabel *mainImageLabel;
    QPushButton *backButton;

    QLabel *userLabel; // QLabel для отображения имени пользователя
    User *currentUser=nullptr; // Указатель на текущего пользователя
};

#endif // MAINWINDOW_H
