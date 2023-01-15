#ifndef DIRECTION_H
#define DIRECTION_H

#include <QVector2D>

enum Direction : uint8_t
{
    Invalid = 0,

    Up,
    Right,
    Down,
    Left,

    Horizontal,
    Vertical,

    UpLeft,
    UpRight,
    LeftUp,
    RightUp,
    DownLeft,
    DownRight,
    LeftDown,
    RightDown
};

/// @brief It gets direction like an enum and converts to a vector object
/// @param direction Direction
/// @return QVector2D
constexpr QVector2D dirToVector(Direction direction) noexcept
{
    switch (direction)
    {
    case Direction::Up:
        return QVector2D(0, -1);
        break;

    case Direction::Right:
        return QVector2D(1, 0);
        break;

    case Direction::Down:
        return QVector2D(0, 1);
        break;

    case Direction::Left:
        return QVector2D(-1, 0);
        break;

    default:
        return QVector2D(0, 0);
        break;
    }
}

/// @brief It gets direction like a vector and converts to an enum Direction
/// @param vector QVector2D
/// @returnDirection
constexpr Direction vectorToDir(QVector2D direction) noexcept
{
    if (direction.x() > 0)
        return Direction::Right;
    else if (direction.x() < 0)
        return Direction::Left;
    else if (direction.y() > 0)
        return Direction::Down;
    else if (direction.y() < 0)
        return Direction::Up;

    return {};
}

/// @brief It gets two directions and checks if they are opposite
/// @param lhs Direction
/// @param rhs Direction
/// @return True, if lhs and rhs are opposite directions, otherwise False
constexpr bool isOpposite(Direction lhs, Direction rhs) noexcept
{
    return (lhs == Direction::Left && rhs == Direction::Right) || (lhs == Direction::Right && rhs == Direction::Left) ||
           (lhs == Direction::Up && rhs == Direction::Down) || (lhs == Direction::Down && rhs == Direction::Up);
}

#endif // DIRECTION_H
