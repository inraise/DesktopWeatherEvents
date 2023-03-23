#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QColumnView>
#include <QFontDatabase>
#include "CurrentWeatherData.h"
#include <string>
#include <string>
#include <cctype>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

void TopBarElement(
        int argc, char *argv[],
        QMainWindow *mainWindow,
        const QFont &font,
        json jsonWeatherData
) {
    QLabel *appTitle = new QLabel(mainWindow);
    appTitle->setText("WEATHER EVENTS");
    appTitle->resize(450, 130);
    appTitle->setFont(font);
    appTitle->setStyleSheet(
            "width: 200px; color: #303030; font-size: 45px;");
    appTitle->show();

    string name = jsonWeatherData["name"];
    string country = jsonWeatherData["sys"]["country"];
    QString resultForm = QString::fromStdString(name + ", " + country);

    QLabel *appCityName = new QLabel(mainWindow);
    appCityName->setText(resultForm);
    appCityName->resize(700, 130);
    appCityName->setFont(font);
    appCityName->setStyleSheet(
            "margin-left: 440px; color: #303030; font-size: 20px;");
    appCityName->show();

    QWidget * line = new QLabel(mainWindow);
    line->resize(660, 1);
    line->setFixedHeight(1);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    line->move(20, 100);
    line->setStyleSheet(QString("background-color: #303030;"));
    line->show();
}