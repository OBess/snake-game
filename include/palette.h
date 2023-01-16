#ifndef PALETTE_H
#define PALETTE_H

#include <QColor>

namespace Palette
{
    [[maybe_unused]] constexpr QColor background(0, 122, 0);

    [[maybe_unused]] constexpr QColor tileGreen(0, 133, 0);
    [[maybe_unused]] constexpr QColor tileYellow(255, 255, 0);

    [[maybe_unused]] constexpr QColor transparency(0, 0, 0, 0);

    [[maybe_unused]] constexpr QColor cup(255, 210, 0);

    [[maybe_unused]] constexpr QColor iconText(149, 252, 149);
    [[maybe_unused]] constexpr QColor redCrossText(255, 0, 0);
    [[maybe_unused]] constexpr QColor infoText(255, 255, 255);
} // namespace Palette

#endif // PALETTE_H
