#include <QApplication>
#include "../hfiles/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.setMaximumSize(420, 460);
    window.setMinimumSize(420, 460);
    window.show();
    return app.exec();
}
