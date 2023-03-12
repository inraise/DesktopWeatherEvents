#include <cpr/cpr.h>
#include <iostream>

using namespace std;
using namespace cpr;

class UserLocation {
public:
    void getUserCoordsFromIP() {
        Response request = Get(Url{"https://api.ipify.org?format=json"});
        userIP = request.text;
        cout << userIP;
        //Response requestCoords = Get(Url{"http://ip-api.com/json/24.48.0.1"})
    }

private:
    string userIP, userLocationData;
};