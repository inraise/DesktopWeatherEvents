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
QLineEdit *lineEdit;

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
    int argc{};
    char *argv{};
    json jsonData;
    string city;
    QFont font;
    QMainWindow *mainWindow{};
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
    buttonBar.mainWindow = &mainWindow;
    buttonBar.argc = argc;
    buttonBar.argv = *argv;

    // menu bar
    auto *widgetActionInput = new QWidgetAction(&mainWindow);
    auto *widgetActionButton = new QWidgetAction(&mainWindow);
    lineEdit = new QLineEdit(&mainWindow);
    lineEdit->setPlaceholderText("City Name");
    lineEdit->setStyleSheet("margin: 5px; background-color: transparent; "
                            "border-radius: 5px; border: 1px gray solid; padding-left: 7px");
    widgetActionInput->setDefaultWidget(lineEdit);

    auto *button = new QPushButton("Set City");
    //buttonBar.city = lineEdit->text().toStdString();

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
    buttonBar.font = font;

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
    city = lineEdit->text().toStdString();
    currentWeatherData.enterUserCity(city);
    jsonData = currentWeatherData.getJsonWeather();

    if (!city.empty()) {
        MainElement(argc, &argv, mainWindow, font,
                    jsonData,
                    currentWeatherData);
        TopBarElement(argc, &argv, mainWindow, font,
                      jsonData);
    }
}

#include "UiManagement.moc"