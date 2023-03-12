#include "CurrentWeatherData.h"
#include "GetUserLocation.h"

int UiManagement(int argc, char *argv[], CurrentWeatherData currentWeatherData);

using namespace std;


int main(int argc, char *argv[]) {
    CurrentWeatherData currentWeatherData;
    UserLocation userLocation;
    //currentWeatherData.enterUserCity(); // user parameter need to get in program !!
    userLocation.getUserCoordsFromIP();

    //UiManagement(argc, argv, currentWeatherData);
}
