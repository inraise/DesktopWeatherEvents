#include <cpr/cpr.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <QGeoPositionInfoSource>
#include <QGeoCoordinate>

using namespace std;
using namespace cpr;
using json = nlohmann::json;

class UserLocation {
public:
    string getLat() {
        return to_string(userLatCoord);
    }

    string getLon() {
        return to_string(userLonCoord);
    }

//    void getUserLocation() {
//        QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(0);
//        if (source)
//            source->setUpdateInterval(100000);
//    }

    void getUserIP() {
        Response requestIp = Get(Url{"https://api.ipify.org?format=json"});
        json dataIp = json::parse(requestIp.text);
        userIP = dataIp["ip"];
    }

    void getUserCoords() {
        Response requestCoords = Get(Url{"http://ip-api.com/json/" + userIP});
        json dataCoords = json::parse(requestCoords.text);
        userLatCoord = dataCoords["lat"];
        userLonCoord = dataCoords["lon"];
    }

private:
    string userIP;
    double userLatCoord, userLonCoord;
};