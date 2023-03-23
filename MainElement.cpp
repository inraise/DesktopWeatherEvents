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

void MainElement(
        int argc, char *argv[],
        QMainWindow *mainWindow,
        const QFont &font,
        json jsonWeatherData
) {
    string imageString = "cloud.png";
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

    QLabel *imageLabel = new QLabel(mainWindow);
    imageLabel->setPixmap(image);
    imageLabel->resize(250, 250);
    imageLabel->setStyleSheet("background-color: none;");
    imageLabel->move(10, 85);
    imageLabel->show();

    string weatherNameDesc = jsonWeatherData["weather"][0]["description"];
    weatherNameDesc[0] = toupper(weatherNameDesc[0]);

    QLabel *weatherName = new QLabel(mainWindow);
    weatherName->setText(QString::fromStdString(weatherNameDesc));
    weatherName->resize(420, 100);
    weatherName->move(-70, 300);
    weatherName->setFont(font);
    weatherName->setAlignment(Qt::AlignCenter);
    weatherName->setStyleSheet(
            "color: #303030; font-size: 23px;");
    weatherName->show();

//    QWidget * line = new QLabel(mainWindow);
//    line->resize(1, 300);
//    line->setFixedHeight(1);
//    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
//    line->move(200, 200);
//    line->setStyleSheet(QString("background-color: #97928F;"));
//    line->show(); !!!it need horizontal line
}