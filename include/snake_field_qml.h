#ifndef SNAKE_FIELD_QML_H
#define SNAKE_FIELD_QML_H

#include <QPainter>
#include <QtQuick/QQuickPaintedItem>

#include "apple.h"
#include "direction.h"
#include "game_logic.h"
#include "palette.h"
#include "snake.h"
#include "sprites.h"

class SnakeFieldQmlItem : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(int32_t cols MEMBER _cols CONSTANT)
    Q_PROPERTY(int32_t rows MEMBER _rows CONSTANT)

    Q_PROPERTY(Snake * snake MEMBER _snake WRITE setSnake)
    Q_PROPERTY(Apple * apple MEMBER _apple WRITE setApple)
    Q_PROPERTY(GameLogic::GameState state MEMBER _state WRITE setState)

    QML_ELEMENT

public:
    explicit SnakeFieldQmlItem(QQuickItem *parent = nullptr)
        : QQuickPaintedItem(parent)
    {
//            setMinimumSize(970, 500);
    }

    constexpr void setState(GameLogic::GameState state) noexcept
    {
        _state = state;
    }

    constexpr void setApple(Apple *apple) noexcept
    {
        _apple = apple;
    }

    constexpr void setSnake(Snake *snake) noexcept
    {
        _snake = snake;
    }

private:
    void paint(QPainter *painter) override
    {
        const auto rect = QRect(0, 0, textureSize().width(), textureSize().height());
        // Calculates
        _tileSize = std::min(rect.width() / _cols, rect.height() / _rows);
        _offset = QVector2D((rect.width() - _tileSize * _cols) / 2,
                            (rect.height() - _tileSize * _rows) / 2);

        // Draws tiles for field
        paintField(painter, rect);

        // Draws an apple
        painter->drawPixmap(getTileRect(_apple->position * _tileSize + _offset, _tileSize),
                           Sprites::getSprite(Sprites::Apple));

        // Draws a snake head
        const auto headPos = _snake->headPos();
        painter->drawPixmap(getTileRect(headPos * _tileSize + _offset, _tileSize),
                           Sprites::getSprite(_snake->getDirection(), Sprites::SnakeHead));

        // Draws a snake body
        const auto &body = _snake->body();

        //// Draws the first part of body
        const auto &bodyDir = getBodyDir(headPos - body[0], body[0] - body[1]);
        painter->drawPixmap(getTileRect(body[0] * _tileSize + _offset, _tileSize),
                           Sprites::getSprite(bodyDir, Sprites::SnakeBody));

        //// Draws rest parts
        for (size_t i = 1; i < body.size() - 1; ++i)
        {
            const auto &bodyDir = getBodyDir(body[i - 1] - body[i], body[i] - body[i + 1]);
            painter->drawPixmap(getTileRect(body[i] * _tileSize + _offset, _tileSize),
                               Sprites::getSprite(bodyDir, Sprites::SnakeBody));
        }

        // Draws a snake tail
        painter->drawPixmap(getTileRect(body.back() * _tileSize + _offset, _tileSize),
                           Sprites::getSprite(vectorToDir(body.back() - body[body.size() - 2]),
                                              Sprites::SnakeTail));

        // Draws menu
        if (_state == GameLogic::GameState::Pause ||
            _state == GameLogic::GameState::GameOver ||
            _state == GameLogic::GameState::EndGame)
        {
            paintMenu(painter, rect);
        }
    }

    /// @brief Draws tiles for grid
    /// @param painter
    /// @param event Gets rect of the area
    inline void paintField(QPainter *painter, QRect rect)
    {
        painter->save();

        painter->fillRect(rect, Palette::background);

        int32_t x = _offset.x();
        int32_t y = _offset.y();
        int32_t tile = 0;

        for (int32_t i = 0; i < _rows; ++i)
        {
            for (int32_t j = 0; j < _cols; ++j)
            {
                painter->fillRect(x, y, _tileSize, _tileSize,
                                 tile % 2 ? Palette::tileGreen : Palette::tileYellow);

                x += _tileSize;
                ++tile;
            }

            x = _offset.x();
            y += _tileSize;
            ++tile;
        }

        painter->restore();
    }

    /// @brief Draws menu
    /// @param painter
    /// @param event Gets rect of the area
    inline void paintMenu(QPainter *painter, QRect rect)
    {
        painter->save();

        // Calculates
        const int32_t width = rect.width() * 0.5;
        const int32_t height = rect.height() * 0.5;
        const int32_t x = (rect.width() / 2) - (width / 2);
        const int32_t y = (rect.height() / 2) - (height / 2);

        const QPen pen(Palette::tileYellow, 10);

        // Draws rounded rect
        painter->setPen(pen);
        painter->setBrush(Palette::tileGreen);
        painter->drawRoundedRect(x, y, width, height, 30, 30);

        // Draws content
        if (_state == GameLogic::GameState::Pause)
        {
            paintMenuContent(painter, {x, y, width, height},
                             Sprites::Icon, "Welcome", Palette::iconText, "start");
        }
        else if (_state == GameLogic::GameState::GameOver)
        {
            paintMenuContent(painter, {x, y, width, height},
                             Sprites::RedCross, "Game Over", Palette::redCrossText, "restart");
        }
        else if (_state == GameLogic::GameState::EndGame)
        {
            paintMenuContent(painter, {x, y, width, height},
                             Sprites::Cup, "End Game", Palette::cup, "restart");
        }

        painter->restore();
    }

    /// @brief Draws main content for menu
    /// @param painter
    /// @param area Where to draw
    /// @param spriteType The menu image
    /// @param title The menu title
    /// @param titleColor Color of the menu title
    /// @param hint The menu hint
    inline void paintMenuContent(QPainter *painter, QRect area, Sprites::Type spriteType,
                                 const QString &title, QColor titleColor, const QString &hint)
    {
        // Calculates
        const int32_t imageSize = area.height() / 3;
        const int32_t imageX = area.x() + area.width() / 5 - imageSize / 2;
        const int32_t imageY = area.y() + imageSize / 2;

        const int32_t titleSize = area.width() / 14;
        const int32_t titleX = imageX + imageSize + titleSize / 3;
        const int32_t titleY = imageY + imageSize / 2 + titleSize / 2;

        const int32_t hintsSize = titleSize / 3.5;
        const int32_t hintsX = imageX;
        const int32_t hintsY = imageY + imageSize + hintsSize * 2;

        // Draws the icon
        painter->drawPixmap(imageX, imageY, imageSize, imageSize, Sprites::getSprite(spriteType));

        // Draws the main text
        painter->setFont(QFont("Arial", titleSize, QFont::DemiBold));
        painter->setPen(titleColor);
        painter->drawText(titleX, titleY, title);

        // Draws the additional text
        painter->setFont(QFont("Arial", hintsSize, QFont::DemiBold));
        painter->setPen(Palette::infoText);

#ifndef Q_OS_ANDROID
        painter->drawText(hintsX, hintsY, "Space to " + hint + " game");
        painter->drawText(hintsX, hintsY + hintsSize * 2, "Arrows or AWSD to move");
#else  // Q_OS_ANDROID
        painter->drawText(hintsX, hintsY, "Touch to " + hint + " game");
        painter->drawText(hintsX, hintsY + hintsSize * 2, "Move by fingers");
#endif // Q_OS_ANDROID
    }

    /// @brief Gets position and size and creates QRect
    /// @param point Position to start draw a tile
    /// @param size Size of one tile
    /// @return QRect for one tile
    constexpr QRect getTileRect(QVector2D point, int32_t size) const noexcept
    {
        return QRect(point.toPoint(), QSize(size, size));
    }

    /// @brief Gets vectors to and from the current body and returns proper direction for getting sprite
    /// @param lhs A vector that directed to the current body part
    /// @param rhs A vector that directed from the current body part
    /// @return Direction
    constexpr Direction getBodyDir(QVector2D lhs, QVector2D rhs) noexcept
    {
        if (lhs.x() == 0 && rhs.x() == 0)
        {
            return Direction::Vertical;
        }
        else if (lhs.y() == 0 && rhs.y() == 0)
        {
            return Direction::Horizontal;
        }
        else if ((lhs.x() < 0 && rhs.y() < 0) || (lhs.y() > 0 && rhs.x() > 0))
        {
            return Direction::DownLeft;
        }
        else if ((lhs.y() > 0 && rhs.x() < 0) || (lhs.x() > 0 && rhs.y() < 0))
        {
            return Direction::DownRight;
        }
        else if ((lhs.y() < 0 && rhs.x() > 0) || (lhs.x() < 0 && rhs.y() > 0))
        {
            return Direction::RightUp;
        }
        else if ((lhs.y() < 0 && rhs.x() < 0) || (lhs.x() > 0 && rhs.y() > 0))
        {
            return Direction::LeftUp;
        }

        return Direction::Invalid;
    }

private:
    Snake *_snake;
    struct Apple *_apple;

    int32_t _tileSize;
    QVector2D _offset;

    GameLogic::GameState _state{GameLogic::GameState::Pause};

    int32_t _cols;
    int32_t _rows;
};

#endif // SNAKE_FIELD_QML_H
