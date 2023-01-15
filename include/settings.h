#ifndef SETTINGS_H
#define SETTINGS_H

namespace Settings
{
    /// @brief The batch of predefined constants for the settings file
    namespace Ini
    {
        [[maybe_unused]] inline const char *const FILE_PATH = "settings.ini";

        [[maybe_unused]] inline const char *const MAIN_WINDOW = "MainWindow";
        [[maybe_unused]] inline const char *const IS_MAXIMIZED = "IsMaximized";
        [[maybe_unused]] inline const char *const WIDTH = "Width";
        [[maybe_unused]] inline const char *const HEIGHT = "Height";
        [[maybe_unused]] inline const char *const POS_X = "PositionX";
        [[maybe_unused]] inline const char *const POS_Y = "PositionY";

        [[maybe_unused]] inline const char *const GAME = "Game";
        [[maybe_unused]] inline const char *const BEST = "Best";
        [[maybe_unused]] inline const char *const AREA_WIDTH = "AreaWidth";
        [[maybe_unused]] inline const char *const AREA_HEIGHT = "AreaHeight";
    } // namespace Ini

} // namespace Settings

#endif // SETTINGS_H
