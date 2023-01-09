#ifndef SNAKE_SYSTEM_H
#define SNAKE_SYSTEM_H

#include <vector>

#include <QVector2D>

#include "apple.h"

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

class Snake
{
public:
    Snake(Direction direction, QVector2D headPosition)
        : _direction{direction}, _headPosition{headPosition}
    {
        const QVector2D opositeDir = dirToVector(direction) * -1;

        _tail.reserve(_initTaleSize * 10);
        _tail.resize(_initTaleSize);

        _tail[0] = _headPosition + opositeDir;

        for (size_t i = 1; i < _tail.size(); ++i)
        {
            _tail[i] = _tail[i - 1] + opositeDir;
        }
    }

    ~Snake() = default;

    inline void move() noexcept
    {
        // Moves tail
        for (size_t i = _tail.size() - 1; i > 0; --i)
        {
            _tail[i] = _tail[i - 1];
        }

        _tail[0] = _headPosition;

        // Moves head
        _headPosition += dirToVector(_direction);
    }

    constexpr void addTailPart()
    {
        _tail.push_back(_tail.back());
    }

    constexpr Direction getDirection() const noexcept
    {
        return _direction;
    }

    constexpr void setDirection(Direction direction) noexcept
    {
        _direction = direction;
    }

    constexpr void rotateLeft() noexcept
    {
        _direction = static_cast<Direction>((_direction - 1) % 2);
    }

    constexpr void rotateRight() noexcept
    {
        _direction = static_cast<Direction>((_direction + 1) % 2);
    }

    constexpr QVector2D headPos() const noexcept
    {
        return _headPosition;
    }

    constexpr const std::vector<QVector2D>& tail() const noexcept
    {
        return _tail;
    }

private:
    Direction _direction;
    QVector2D _headPosition;

    const uint8_t _initTaleSize = 5;
    std::vector<QVector2D> _tail;
};

#endif // SNAKE_SYSTEM_H
