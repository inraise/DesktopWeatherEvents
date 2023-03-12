#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QFontDatabase>
#include "CurrentWeatherData.h"
#include <QScreen>

int TopBarElement(int argc, char *argv[], QMainWindow *mainWindow, const QFont& font);

using namespace std;

int UiManagement(int argc, char *argv[], const CurrentWeatherData& currentWeatherData) {
    QApplication application(argc, argv);
    QMainWindow mainWindow;

    auto fontId = QFontDatabase::addApplicationFont(":/fonts/thickthinks.ttf");
    QFont font = QFont("Thick Thinks", 10, 1);

    mainWindow.setStyleSheet(
            "background: #FFF5EE;"
            "padding: 30px"
    );

    TopBarElement(argc, argv, &mainWindow, font);

    mainWindow.showMaximized();
    return QApplication::exec();
}