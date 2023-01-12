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

constexpr Direction vectorToDir(QVector2D vector) noexcept
{
    if (vector.x() > 0)
        return Direction::Right;
    else if (vector.x() < 0)
        return Direction::Left;
    else if (vector.y() > 0)
        return Direction::Down;
    else if (vector.y() < 0)
        return Direction::Up;

    return {};
}

#endif // DIRECTION_H
