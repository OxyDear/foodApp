#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>

class RegisterPage : public QWidget {
    Q_OBJECT

public:
    explicit RegisterPage(QWidget *parent = nullptr);

signals:
    void backToMain();
    void switchToLogin();
    void userRegIn(const std::string &username, const std::string mode);

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *registerButton;
    QPushButton *backButton;
    // void addLoginButton(QHBoxLayout *categoryLayout, const QString &name);

private slots:
    void handleRegister();
};

#endif // REGISTERPAGE_H
