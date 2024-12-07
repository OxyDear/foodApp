#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QLineEdit>

class AdminPage : public QWidget {
    Q_OBJECT

public:
    explicit AdminPage(QWidget *parent = nullptr);

private:
    void showUsernameInput(QVBoxLayout *layout, const std::string &action);
    void showNameInput(QVBoxLayout *layout, const std::string &action);
    void showDeleteInput(QVBoxLayout *layout, const std::string &action);
    void showAddInput(QVBoxLayout *layout, const std::string &action);

signals:
    void backToMain(); // Signal to go back to the main page
    void adminActionTriggeredAdd(const std::string &username); // Signal for admin actions
    void adminActionTriggeredDelete(const std::string &username); // Signal for admin actions
    void adminActionTriggeredChange(const std::string &name, const std::string &editedName); // Signal for admin actions
    void adminActionTriggeredDeleteOne(const std::string &name); // Signal for admin actions
    void adminActionTriggeredAddOne(const std::string &name, const std::string &desc); // Signal for admin actions


private:
    void setupUI(); // Sets up the user interface
};

#endif // ADMINPAGE_H
