#include <QApplication>
#include <QFont>
#include <QFontDatabase>
#include "../hfiles/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;

    // QString fontPath = ":/assets/Circular Std Book.ttf"; // Укажите путь к вашему шрифту
    // int fontId = QFontDatabase::addApplicationFont(fontPath);

    // if (fontId != -1) {
    //     QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    //     if (!fontFamilies.isEmpty()) {
    //         QFont customFont(fontFamilies.at(0)); // Используйте первый шрифт из списка
    //         app.setFont(customFont); // Устанавливаем шрифт для всего приложения
    //     } else {
    //         qDebug() << "Не удалось получить шрифты из файла.";
    //     }
    // } else {
    //     qDebug() << "Не удалось загрузить шрифт!";
    // }

    window.setMaximumSize(420, 460);
    window.setMinimumSize(420, 460);
    window.show();
    return app.exec();
}
