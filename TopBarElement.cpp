#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QColumnView>
#include <QFontDatabase>
#include "CurrentWeatherData.h"
#include <string>

using namespace std;

void TopBarElement(int argc, char *argv[], QMainWindow *mainWindow, const QFont& font) {
    QLabel *appTitle = new QLabel(mainWindow);
    appTitle->setText("WEATHER EVENTS");
    appTitle->resize(450, 130);
    appTitle->setFont(font);
    appTitle->setStyleSheet(
            "width: 200px; color: #303030; font-size: 45px;");
    appTitle->show();


}