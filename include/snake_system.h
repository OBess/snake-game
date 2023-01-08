#ifndef SNAKE_SYSTEM_H
#define SNAKE_SYSTEM_H

#include <vector>

#include <QVector2D>

enum Direction : uint8_t
{
    Up = 1,
    Right = 2,
    Down = 4,
    Left = 8,
    UpLeft = Up | Left,
    UpRight = Up | Right,
    LeftUp = Left | Up,
    RightUp = Right | Up,
    DownLeft = Down | Left,
    DownRight = Down | Right,
    LeftDown = Left | Down,
    RightDown = Right | Down
};

enum SnakeTiles : uint8_t
{
    Apple,
    Head,
    Body,
    Tail
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

constexpr Direction idDirection(QVector2D lhs, QVector2D rhs) noexcept
{
    const auto vector = lhs - rhs;

    int dir{};

    if (vector.x() < 0)
    {
        dir |= Direction::Left;
    }
    else if (vector.x() > 0)
    {
        dir |= Direction::Right;
    }

    if (vector.y() < 0)
    {
        dir |= Direction::Up;
    }
    else if (vector.y() > 0)
    {
        dir |= Direction::Down;
    }

    return static_cast<Direction>(dir);
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

class Apple
{
public:
    Apple(QVector2D pos = QVector2D(0, 0))
        : _pos{pos}
    {
    }

    ~Apple() = default;

    constexpr void setPos(QVector2D pos) noexcept
    {
        _pos = pos;
    }

    constexpr QVector2D getPos() const noexcept
    {
        return _pos;
    }

private:
    QVector2D _pos;
};

#endif // SNAKE_SYSTEM_H
