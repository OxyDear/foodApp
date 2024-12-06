#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QWidget>
#include <QString>
#include <QVBoxLayout>

class AdminPage : public QWidget {
    Q_OBJECT

public:
    explicit AdminPage(QWidget *parent = nullptr);

private:
    void showUsernameInput(QVBoxLayout *layout, const std::string &action);

signals:
    void backToMain(); // Signal to go back to the main page
    void adminActionTriggeredAdd(const std::string &username); // Signal for admin actions
    void adminActionTriggeredDelete(const std::string &username); // Signal for admin actions

private:
    void setupUI(); // Sets up the user interface
};

#endif // ADMINPAGE_H
