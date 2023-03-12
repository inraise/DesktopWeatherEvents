#include <cpr/cpr.h>
#include <iostream>
#include <utility>

using namespace std;
using namespace cpr;

class CurrentWeatherData {
public:
    string getStringRequest() {
        return stringRequest;
    }

    void enterUserCity() {
        string enterUserCity;
        cout << "Enter the name of the city: ";
        cin >> enterUserCity;

        this->userCity = enterUserCity;
    }

    void enterUserCoords(string lat, string lon) {
        this->userLat = lat;
        this->userLon = lon;
    }

    string getCurrentCoordsWeather(string requestUrl) {
        Response request = Get(
                Url{
                        move(requestUrl)
                },
                Parameters{{"lat", userLat},
                           {"lon", userLon},
                           {"appid", "846bddc7aaba499cd60058e2d06ad6e7"},
                           {"units", "metric"},
                           {"lang", "ru"}}
        );

        this->stringRequest = request.text;
        return request.text;
    }

private:
    string userCity, userLat, userLon, stringRequest;
};