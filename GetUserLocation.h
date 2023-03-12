#include <cpr/cpr.h>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;
using namespace cpr;
using json = nlohmann::json;

class UserLocation {
public:
    string getLat() {
        return userLatCoord;
    }

    string getLon() {
        return userLonCoord;
    }

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
    string userIP, userLatCoord, userLonCoord;
};