#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <random>

#include <QSize>
#include <QVector2D>

#include "apple.h"
#include "score.h"
#include "snake.h"

class GameLogic
{
private:
    enum class CollisionType : uint8_t
    {
        Nothing = 0,

        Apple,
        Body,
        Wall
    };

public:
    GameLogic(QSize area, uint32_t bestScore)
        : _area(area), _gameGoesOn(false), _gen(_rd())
    {
        _snake = new Snake(Direction::Up, QVector2D(_area.width() / 2, _area.height() / 2));
        _apple = new Apple(randomApplePos());
        _score = new Score(bestScore);
    }

    ~GameLogic()
    {
        delete _apple;
        delete _score;
        delete _snake;
    }

    void start()
    {
        _gameGoesOn = true;
    }

    void update()
    {
        if (_gameGoesOn == false)
            return;

        _snake->move();

        const auto collisionType = checkCollision();

        if (collisionType == CollisionType::Apple)
        {
            _score->incrementScore();
            _snake->addTailPart();
            _apple->position = randomApplePos();
        }
        else if (collisionType == CollisionType::Body ||
                 collisionType == CollisionType::Wall)
        {
            _gameGoesOn = false;
        }
    }

    void restart()
    {
        delete _snake;
        _snake = new Snake(Direction::Up, QVector2D(_area.width() / 2, _area.height() / 2));

        _apple->position = randomApplePos();

        _gameGoesOn = true;
    }

    constexpr void setDirection(Direction dir) noexcept
    {
        if (isOpposite(dir, _snake->getDirection()) == false)
        {
            _snake->setDirection(dir);
        }
    }

    constexpr Direction getDirection() const noexcept
    {
        return _snake->getDirection();
    }

    constexpr QSize area() const noexcept
    {
        return _area;
    }

    constexpr bool doesGameGoOn() const noexcept
    {
        return _gameGoesOn;
    }

    constexpr const Apple* apple() const noexcept
    {
        return _apple;
    }

    constexpr const Score* score() const noexcept
    {
        return _score;
    }

    constexpr const Snake* snake() const noexcept
    {
        return _snake;
    }

private:
    constexpr CollisionType checkCollision() const noexcept
    {
        const auto headPos = _snake->headPos();

        // Checks apple collision
        if (headPos == _apple->position)
        {
            return CollisionType::Apple;
        }

        // Checks wall collision
        const auto wallCollision = (headPos.x() < 0) + (headPos.y() < 0) +
                (headPos.x() >= _area.width()) + (headPos.y() >= _area.height());

        if (wallCollision)
        {
            return CollisionType::Wall;
        }

        // Checks body collision
        if (checkBodyCollision(headPos))
        {
            return CollisionType::Body;
        }

        return {};
    }

    constexpr bool checkBodyCollision(QVector2D pos) const noexcept
    {
        for (const auto& part : _snake->body())
        {
            if (pos == part)
            {
                return true;
            }
        }

        return false;
    }

    constexpr bool checkAppleCollision(QVector2D pos) const noexcept
    {
        return pos == _snake->headPos() || checkBodyCollision(pos);
    }

    inline QVector2D randomApplePos() noexcept
    {
        std::uniform_int_distribution distribX(0, _area.width() - 1);
        std::uniform_int_distribution distribY(0, _area.height() - 1);

        QVector2D newPos(0, 0);

        do
        {
            newPos.setX(distribX(_gen));
            newPos.setY(distribY(_gen));

        } while(checkAppleCollision(newPos));

        return newPos;
    }

private:
    Apple* _apple = nullptr;
    Score* _score = nullptr;
    Snake* _snake = nullptr;

    QSize _area;
    bool _gameGoesOn = false;

    std::random_device _rd;
    std::mt19937 _gen;
};

#endif // GAME_LOGIC_H
