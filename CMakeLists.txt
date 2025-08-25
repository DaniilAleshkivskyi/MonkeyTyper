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
        src/Game/GamePlay/WordEntity.cpp
        src/Game/GamePlay/WordEntity.hpp
        src/GameStates/GameState.hpp
        src/helpers/CenterEntity.cpp
        src/helpers/CenterEntity.hpp
        src/IOIteractions/MouseIteraction.hpp
        src/IOIteractions/MouseIteraction.cpp
        src/helpers/PlaceChooseMenu.cpp
        src/helpers/PlaceChooseMenu.hpp
        src/Game/ConfigMenu/ConfigOption.cpp
        src/Game/ConfigMenu/ConfigOption.hpp
        src/Game/ConfigMenu/ConfigClick.hpp
        src/Game/ConfigMenu/ConfigClick.cpp
        src/Game/GamePlay/GamePlay.hpp
        src/Game/GamePlay/GamePlay.cpp
        src/Game/Game.cpp
        src/Game/Game.hpp
        src/Game/MainMenu/MainMenu.cpp
        src/Game/MainMenu/MainMenu.hpp
        src/Game/Game.cpp
        src/Game/Game.hpp
        src/Game/BestScoresMenu/BestScoresMenu.cpp
        src/Game/BestScoresMenu/BestScoresMenu.hpp
        src/GameStates/IGameState.hpp
        src/Game/ConfigMenu/ConfigMenu.cpp
        src/Game/ConfigMenu/ConfigMenu.hpp
        src/Game/GamePlay/PauseMenu/PauseMenu.cpp
        src/Game/GamePlay/PauseMenu/PauseMenu.hpp
        src/Game/GamePlay/GameOver/GameOver.cpp
        src/Game/GamePlay/GameOver/GameOver.hpp
        src/helpers/Theme.cpp
        src/helpers/Theme.hpp
)
target_link_libraries(MonkeyTyper PRIVATE SFML::Graphics fmt)