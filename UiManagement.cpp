#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QFontDatabase>
#include "CurrentWeatherData.h"
#include <QScreen>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

void TopBarElement(
        int argc, char *argv[],
        QMainWindow *mainWindow,
        const QFont &font,
        json jsonWeatherData
);

void MainElement(
        int argc, char *argv[],
        QMainWindow *mainWindow,
        const QFont &font,
        json jsonWeatherData
);

int UiManagement(
        int argc,
        char *argv[],
        CurrentWeatherData currentWeatherData,
        const json& jsonWeatherData
) {
    QApplication application(argc, argv);
    QMainWindow mainWindow;

    auto fontId = QFontDatabase::addApplicationFont(":/fonts/thickthinks.ttf");
    QFont font = QFont("Thick Thinks", 10, 1);

    mainWindow.setStyleSheet(
            "background: #FFF5EE;"
            "padding: 30px"
    );

    MainElement(argc, argv, &mainWindow, font, jsonWeatherData);
    TopBarElement(argc, argv, &mainWindow, font, jsonWeatherData);

    mainWindow.setFixedWidth(700);
    mainWindow.setFixedHeight(500);
    mainWindow.showMaximized();
    return QApplication::exec();
}