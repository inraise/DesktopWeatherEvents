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
public slots:

    void setCity();

public:
    json jsonData;
    string city;
    CurrentWeatherData currentWeatherData;
};


int UiManagement(
        int argc,
        char *argv[],
        CurrentWeatherData currentWeatherData,
        json jsonWeatherData
) {
    QApplication application(argc, argv);
    QMainWindow mainWindow;
    ButtonBar buttonBar;
    buttonBar.currentWeatherData = currentWeatherData;
    buttonBar.jsonData = jsonWeatherData;

    // menu bar
    auto *widgetActionInput = new QWidgetAction(&mainWindow);
    auto *widgetActionButton = new QWidgetAction(&mainWindow);
    auto *lineEdit = new QLineEdit(&mainWindow);
    lineEdit->setPlaceholderText("City Name");
    lineEdit->setStyleSheet("margin: 5px; background-color: transparent; "
                            "border-radius: 5px; border: 1px gray solid; padding-left: 7px");
    widgetActionInput->setDefaultWidget(lineEdit);

    auto *button = new QPushButton("Set City");
    buttonBar.city = lineEdit->text().toStdString();

    QObject::connect(button, SIGNAL(clicked()), &buttonBar, SLOT(setCity()));

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

    MainElement(argc, argv, &mainWindow, font,
                buttonBar.jsonData,
                buttonBar.currentWeatherData);
    TopBarElement(argc, argv, &mainWindow, font,
                  buttonBar.jsonData);

    mainWindow.setWindowTitle("Weather Events");
    mainWindow.setFixedWidth(700);
    mainWindow.setFixedHeight(500);
    mainWindow.showMaximized();
    return QApplication::exec();
}

void ButtonBar::setCity() {
    currentWeatherData.enterUserCity(std::move(city));
    jsonData = currentWeatherData.getJsonWeather();
}

#include "UiManagement.moc"