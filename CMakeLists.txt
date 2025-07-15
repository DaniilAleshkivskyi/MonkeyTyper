cmake_minimum_required(VERSION 3.30)
project(MonkeyTyper)

set(CMAKE_CXX_STANDARD 20)


include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 11.0.2
)

FetchContent_MakeAvailable(fmt)



FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)


FetchContent_MakeAvailable(SFML)

add_executable(MonkeyTyper main.cpp
        src/WordEntity.cpp
        src/WordEntity.hpp
        src/GameState.hpp
        src/helpers/CenterEntity.cpp
        src/helpers/CenterEntity.hpp
        src/IOIteractions/MouseIteraction.hpp
        src/IOIteractions/MouseIteraction.cpp
        src/helpers/PlaceChooseMenu.cpp
        src/helpers/PlaceChooseMenu.hpp
        src/Configuration/ConfigOption.cpp
        src/Configuration/ConfigOption.hpp
        src/Configuration/ConfigClick.hpp
        src/Configuration/ConfigClick.cpp
        src/GamePlay/GamePlay.hpp
        src/GamePlay/GamePlay.cpp)
target_link_libraries(MonkeyTyper PRIVATE SFML::Graphics fmt)