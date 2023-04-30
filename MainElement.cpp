#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QColumnView>
#include <QFontDatabase>
#include <QMenuBar>
#include <QLineEdit>
#include <QPushButton>
#include <QWidgetAction>
#include "CurrentWeatherData.h"
#include <string>
#include <cctype>
#include <nlohmann/json.hpp>
#include <utility>

using namespace std;
using json = nlohmann::json;

QLineEdit *lineEdit;

void setCity() {
    QString cityName = lineEdit->text();
    cout << cityName.toStdString();
}

void MainElement(
        int argc, char *argv[],
        QMainWindow *mainWindow,
        const QFont &font,
        json jsonWeatherData,
        CurrentWeatherData currentWeatherData
) {
    string imageString;

    switch (to_string(jsonWeatherData["weather"][0]["id"])[0]) {
        case ('2'):
            imageString = "thunder.png";
            break;
        case ('3'):
            imageString = "rain.png";
            break;
        case ('5'):
            imageString = "rain.png";
            break;
        case ('6'):
            imageString = "snow.png";
            break;
        case ('7'):
            imageString = "wind.png";
            break;
        default:
            if (jsonWeatherData["weather"][0]["id"] == 800)
                imageString = "sun.png";
            else
                imageString = "cloud.png";
            break;
    }
    QPixmap imageRaw(QString::fromStdString(imageString));
    QPixmap image = imageRaw.scaled(QSize(192, 192),
                                    Qt::IgnoreAspectRatio,
                                    Qt::SmoothTransformation);

    auto *imageLabel = new QLabel(mainWindow);
    imageLabel->setPixmap(image);
    imageLabel->resize(250, 250);
    imageLabel->setStyleSheet("background-color: none;");
    imageLabel->move(10, 85);
    imageLabel->show();

    string weatherNameDesc = jsonWeatherData["weather"][0]["description"];
    weatherNameDesc[0] = toupper(weatherNameDesc[0]);

    auto *weatherName = new QLabel(mainWindow);
    weatherName->setText(QString::fromStdString(weatherNameDesc));
    weatherName->resize(420, 100);
    weatherName->move(-70, 300);
    weatherName->setFont(font);
    weatherName->setAlignment(Qt::AlignCenter);
    weatherName->setStyleSheet(
            "color: #303030; font-size: 23px;");
    weatherName->show();

    auto *widgetActionInput = new QWidgetAction(mainWindow);
    auto *widgetActionButton = new QWidgetAction(mainWindow);
    lineEdit = new QLineEdit(mainWindow);
    lineEdit->setPlaceholderText("City Name");
    lineEdit->setStyleSheet("margin: 5px; background-color: transparent; "
                            "border-radius: 5px; border: 1px gray solid; padding-left: 7px");
    widgetActionInput->setDefaultWidget(lineEdit);

    auto *button = new QPushButton("Set City");

    QObject::connect(button, &QPushButton::clicked, setCity);
    button->setStyleSheet(
            "background-color: transparent;"
    );
    widgetActionButton->setDefaultWidget(button);

    auto *menuBar = new QMenuBar(mainWindow);

    auto *menu = new QMenu("Settings");
    menu->addAction(widgetActionInput);
    menu->addAction(widgetActionButton);
    menuBar->addAction(menu->menuAction());

    menuBar->setNativeMenuBar(true);
    menuBar->show();

    string weatherTempValue = to_string(jsonWeatherData["main"]["temp"]);

    auto *weatherTemp = new QLabel(mainWindow);
    weatherTemp->setText(QString::fromStdString(weatherTempValue) + "˙C");
    weatherTemp->resize(300, 140);
    weatherTemp->move(370, 110);
    weatherTemp->setFont(font);
    weatherTemp->setAlignment(Qt::AlignCenter);
    weatherTemp->setStyleSheet(
            "color: #303030; font-size: 45px;");
    weatherTemp->show();

    QPixmap imageTempRaw(QString::fromStdString("tempp.png"));
    QPixmap imageTemp = imageTempRaw.scaled(QSize(64, 64),
                                            Qt::IgnoreAspectRatio,
                                            Qt::SmoothTransformation);

    auto *imageTempLabel = new QLabel(mainWindow);
    imageTempLabel->setPixmap(imageTemp);
    imageTempLabel->resize(150, 150);
    imageTempLabel->setStyleSheet("background-color: none;");
    imageTempLabel->move(350, 95);
    imageTempLabel->show();

    auto *weatherHumidity = new QLabel(mainWindow);
    weatherHumidity->setText(
            "◦ Humidity: " + QString::fromStdString(to_string(jsonWeatherData["main"]["humidity"])) + "%\n" +
            "◦ Pressure: " + QString::fromStdString(to_string(jsonWeatherData["main"]["pressure"])) + " hPa\n" +
            "◦ Wind Speed: " + QString::fromStdString(to_string(jsonWeatherData["wind"]["speed"])) + " m/s\n" +
            "◦ Clouds: " + QString::fromStdString(to_string(jsonWeatherData["clouds"]["all"])) + "%"
    );
    weatherHumidity->resize(300, 210);
    weatherHumidity->move(300, 230);
    weatherHumidity->setFont(font);
    weatherHumidity->setAlignment(Qt::AlignLeft);
    weatherHumidity->setStyleSheet(
            "color: #303030; font-size: 25px;");
    weatherHumidity->show();

    QWidget *line = new QLabel(mainWindow);
    line->resize(380, 1);
    line->setFixedHeight(1);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    line->move(300, 230);
    line->setStyleSheet(QString("background-color: #303030;"));
    line->show();
}