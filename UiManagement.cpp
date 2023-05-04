#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QFontDatabase>
#include "CurrentWeatherData.h"
#include <QPushButton>
#include <QMenuBar>
#include <QWidgetAction>
#include <QScreen>
#include <nlohmann/json.hpp>
#include <utility>

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
        json jsonWeatherData,
        CurrentWeatherData currentWeatherData
);


class ButtonBar : public QObject {
Q_OBJECT
public:
    ButtonBar(QObject *parent, CurrentWeatherData currentWeatherData, string city);

    QPushButton *myButton{};
};

ButtonBar::ButtonBar(QObject *parent, CurrentWeatherData currentWeatherData, string city)
        : QObject(parent) {
    myButton = new QPushButton("Set City");
    connect(
            myButton, SIGNAL(clicked()), this,
            SLOT(setCity(currentWeatherData, city))
    );
}


json setCity(CurrentWeatherData currentWeatherData, string city) {
    currentWeatherData.enterUserCity(std::move(city));
    return currentWeatherData.getJsonWeather();
}


int UiManagement(
        int argc,
        char *argv[],
        CurrentWeatherData currentWeatherData,
        json jsonWeatherData
) {
    QApplication application(argc, argv);
    QMainWindow mainWindow;

    // menu bar
    auto *widgetActionInput = new QWidgetAction(&mainWindow);
    auto *widgetActionButton = new QWidgetAction(&mainWindow);
    auto *lineEdit = new QLineEdit(&mainWindow);
    lineEdit->setPlaceholderText("City Name");
    lineEdit->setStyleSheet("margin: 5px; background-color: transparent; "
                            "border-radius: 5px; border: 1px gray solid; padding-left: 7px");
    widgetActionInput->setDefaultWidget(lineEdit);

    ButtonBar buttonBar(&mainWindow, currentWeatherData, lineEdit->text().toStdString());
    auto *button = buttonBar.myButton;

    button->setStyleSheet(
            "background-color: transparent;"
    );
    widgetActionButton->setDefaultWidget(button);

    auto *menuBar = new QMenuBar(&mainWindow);

    auto *menu = new QMenu("Settings");
    menu->addAction(widgetActionInput);
    menu->addAction(widgetActionButton);
    menuBar->addAction(menu->menuAction());

    menuBar->setNativeMenuBar(true);
    menuBar->show();


    auto fontId = QFontDatabase::addApplicationFont(":/fonts/thickthinks.ttf");
    QFont font = QFont("Thick Thinks", 10, 1);

    mainWindow.setStyleSheet(
            "background: #FFF5EE;"
            "padding: 30px"
    );

    MainElement(argc, argv, &mainWindow, font, jsonWeatherData, currentWeatherData);
    TopBarElement(argc, argv, &mainWindow, font, jsonWeatherData);

    mainWindow.setWindowTitle("Weather Events");
    mainWindow.setFixedWidth(700);
    mainWindow.setFixedHeight(500);
    mainWindow.showMaximized();
    return QApplication::exec();
}