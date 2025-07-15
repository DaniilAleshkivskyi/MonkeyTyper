#pragma once
enum class GameState {
    MainMenu,
    ConfigurationMenu,
    Gameplay,
    BestScores,
    Settings,
    GameOver
};

enum class IsPaused {
    Paused,
    Unpaused,
    SettingsPaused
};
