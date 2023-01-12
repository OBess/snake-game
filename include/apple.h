#ifndef APPLE_H
#define APPLE_H

#include <QVector2D>

struct Apple final
{
    QVector2D position;

    constexpr Apple(QVector2D pos = {0, 0}) noexcept
        : position{pos}
    {
    }
};

#endif // APPLE_H
