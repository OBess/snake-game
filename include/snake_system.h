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

        _body.reserve(_initTaleSize * 10);
        _body.resize(_initTaleSize);

        _body[0] = _headPosition + opositeDir;

        for (size_t i = 1; i < _body.size(); ++i)
        {
            _body[i] = _body[i - 1] + opositeDir;
        }
    }

    ~Snake() = default;

    inline void move() noexcept
    {
        // Moves tail
        for (size_t i = _body.size() - 1; i > 0; --i)
        {
            _body[i] = _body[i - 1];
        }

        _body[0] = _headPosition;

        // Moves head
        _headPosition += dirToVector(_direction);
    }

    constexpr void addTailPart()
    {
        _body.push_back(_body.back());
    }

    constexpr Direction getDirection() const noexcept
    {
        return _direction;
    }

    constexpr void setDirection(Direction direction) noexcept
    {
        _direction = direction;
    }

    constexpr QVector2D headPos() const noexcept
    {
        return _headPosition;
    }

    constexpr const std::vector<QVector2D> &body() const noexcept
    {
        return _body;
    }

private:
    Direction _direction;
    QVector2D _headPosition;

    const uint8_t _initTaleSize = 5;
    std::vector<QVector2D> _body;
};

#endif // SNAKE_SYSTEM_H
