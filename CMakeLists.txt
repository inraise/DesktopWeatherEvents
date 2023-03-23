cmake_minimum_required(VERSION 3.20)
project(DesktopWeatherEvents)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/daniilharitonov/Documents/Felgo/Felgo/macos/lib/cmake/Qt6")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
        location
        )

add_executable(DesktopWeatherEvents main.cpp CurrentWeatherData.h TopBarElement.cpp UiManagement.cpp GetUserLocation.h MainElement.cpp)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(DesktopWeatherEvents
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Location
        cpr::cpr
        nlohmann_json::nlohmann_json
        )

