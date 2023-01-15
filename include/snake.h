#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include <QVector2D>

#include "direction.h"

class Snake
{
public:
    Snake(Direction direction, QVector2D headPosition)
        : _direction{direction}, _headPosition{headPosition}
    {
        init();
    }

    /// @brief Moves the snake head forward corresponding to direction,
    /// saving rest done rotations
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

        // Sets to allow next set direction
        _canSetDir = true;
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
        if (_canSetDir)
        {
            _direction = direction;
            _canSetDir = false;
        }
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
    /// @brief Initialize the snake body on the constructor
    inline void init()
    {
        const QVector2D opositeDir = dirToVector(_direction) * -1;

        _body.reserve(_initTaleSize * 10);
        _body.resize(_initTaleSize);

        _body[0] = _headPosition + opositeDir;

        for (size_t i = 1; i < _body.size(); ++i)
        {
            _body[i] = _body[i - 1] + opositeDir;
        }
    }

private:
    Direction _direction;
    QVector2D _headPosition;

    const uint8_t _initTaleSize = 5;
    std::vector<QVector2D> _body;

    bool _canSetDir = true;
};

#endif // SNAKE_H
