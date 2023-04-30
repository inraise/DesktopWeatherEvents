#include <cpr/cpr.h>
#include <iostream>
#include <utility>
#include <nlohmann/json.hpp>

using namespace std;
using namespace cpr;
using json = nlohmann::json;

class CurrentWeatherData {
public:
    string getStringRequest() {
        return stringRequest;
    }

    void enterUserCity(string enterUserCity) {
        this->userCity = std::move(enterUserCity);
        getCurrentCityWeather("https://api.openweathermap.org/data/2.5/weather");
    }

    void enterUserCoords(string lat, string lon) {
        this->userLat = move(lat);
        this->userLon = move(lon);
    }

    json getJsonWeather() {
        json jsonWeatherData = json::parse(stringRequest);
        return jsonWeatherData;
    }

    void getCurrentCoordsWeather(string requestUrl) {
        Response request = Get(
                Url{
                        move(requestUrl)
                },
                Parameters{{"lat",   userLat},
                           {"lon",   userLon},
                           {"appid", "846bddc7aaba499cd60058e2d06ad6e7"},
                           {"units", "metric"}
                }
        );

        this->stringRequest = request.text;
    }


    void getCurrentCityWeather(string requestUrl) {
        Response
                request = Get(
                Url{
                        move(requestUrl)
                },
                Parameters{{"q",     userCity},
                           {"appid", "846bddc7aaba499cd60058e2d06ad6e7"},
                           {"units", "metric"}}
        );

        this->stringRequest = request.text;
    }

private:
    string userCity, userLat, userLon, stringRequest;
};