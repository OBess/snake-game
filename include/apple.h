#ifndef APPLE_H
#define APPLE_H

#include <QVector2D>

class Apple
{
public:
    Apple(QVector2D pos = {0, 0})
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

#endif // APPLE_H
