#include "CurrentWeatherData.h"
#include "GetUserLocation.h"
#include <nlohmann/json.hpp>

int UiManagement(
        int argc,
        char *argv[],
        const CurrentWeatherData &currentWeatherData,
        const json &jsonWeatherData
);

using namespace std;
using json = nlohmann::json;

int main(int argc, char *argv[]) {
    CurrentWeatherData currentWeatherData;
    UserLocation userLocation;

    userLocation.getUserIP();
    userLocation.getUserCoords();

    currentWeatherData.enterUserCoords(userLocation.getLat(), userLocation.getLon());
    currentWeatherData.getCurrentCoordsWeather("https://api.openweathermap.org/data/2.5/weather");

    json jsonWeatherData = currentWeatherData.getJsonWeather();

    UiManagement(argc, argv, currentWeatherData, jsonWeatherData);
    // refresh
    // socket
}
