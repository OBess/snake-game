#ifndef SNAKE_FIELD_H
#define SNAKE_FIELD_H

#include <QOpenGLWidget>
#include <QPainter>
#include <QPaintEvent>

#include "apple.h"
#include "direction.h"
#include "game_logic.h"
#include "palette.h"
#include "snake.h"
#include "sprites.h"

namespace UI
{
    struct SnakeFieldArgs final
    {
        const Snake *snake;
        const struct Apple *apple;
        int32_t cols;
        int32_t rols;
    };

    class SnakeField : public QWidget
    {
        Q_OBJECT

    public:
        explicit SnakeField(SnakeFieldArgs args, QWidget *parent = nullptr)
            : QWidget{parent}, _snake{args.snake}, _apple{args.apple},
              _cols(args.cols), _rows(args.rols)
        {
            setMinimumSize(970, 500);
        }

        constexpr void setState(GameLogic::GameState state) noexcept
        {
            _state = state;
        }

        constexpr void setApple(const Apple *apple) noexcept
        {
            _apple = apple;
        }

        constexpr void setSnake(const Snake *snake) noexcept
        {
            _snake = snake;
        }

    private:
        void paintEvent(QPaintEvent *event) override
        {
            QPainter painter;
            painter.begin(this);

            // Calculates
            _tileSize = std::min(event->rect().width() / _cols, event->rect().height() / _rows);
            _offset = QVector2D((event->rect().width() - _tileSize * _cols) / 2,
                                (event->rect().height() - _tileSize * _rows) / 2);

            // Draws tiles for field
            paintField(painter, event);

            // Draws an apple
            painter.drawPixmap(getTileRect(_apple->position * _tileSize + _offset, _tileSize),
                               Sprites::getSprite(Sprites::Apple));

            // Draws a snake head
            const auto headPos = _snake->headPos();
            painter.drawPixmap(getTileRect(headPos * _tileSize + _offset, _tileSize),
                               Sprites::getSprite(_snake->getDirection(), Sprites::SnakeHead));

            // Draws a snake body
            const auto &body = _snake->body();

            //// Draws the first part of body
            const auto &bodyDir = getBodyDir(headPos - body[0], body[0] - body[1]);
            painter.drawPixmap(getTileRect(body[0] * _tileSize + _offset, _tileSize),
                               Sprites::getSprite(bodyDir, Sprites::SnakeBody));

            //// Draws rest parts
            for (size_t i = 1; i < body.size() - 1; ++i)
            {
                const auto &bodyDir = getBodyDir(body[i - 1] - body[i], body[i] - body[i + 1]);
                painter.drawPixmap(getTileRect(body[i] * _tileSize + _offset, _tileSize),
                                   Sprites::getSprite(bodyDir, Sprites::SnakeBody));
            }

            // Draws a snake tail
            painter.drawPixmap(getTileRect(body.back() * _tileSize + _offset, _tileSize),
                               Sprites::getSprite(vectorToDir(body.back() - body[body.size() - 2]),
                                                  Sprites::SnakeTail));

            // Draws menu
            if (_state == GameLogic::GameState::Pause ||
                _state == GameLogic::GameState::GameOver ||
                _state == GameLogic::GameState::EndGame)
            {
                paintMenu(painter, event);
            }

            painter.end();
        }

        /// @brief Draws tiles for grid
        /// @param painter Where to draw
        /// @param event Gets rect of the area
        inline void paintField(QPainter &painter, QPaintEvent *event)
        {
            painter.save();

            painter.fillRect(event->rect(), Palette::background);

            int32_t x = _offset.x();
            int32_t y = _offset.y();
            int32_t tile = 0;

            for (int32_t i = 0; i < _rows; ++i)
            {
                for (int32_t j = 0; j < _cols; ++j)
                {
                    painter.fillRect(x, y, _tileSize, _tileSize,
                                     tile % 2 ? Palette::tileGreen : Palette::tileYellow);

                    x += _tileSize;
                    ++tile;
                }

                x = _offset.x();
                y += _tileSize;
                ++tile;
            }

            painter.restore();
        }

        inline void paintMenu(QPainter &painter, QPaintEvent *event)
        {
            painter.save();

            // Calculates
            const QRect &rect = event->rect();

            const int32_t width = rect.width() * 0.5;
            const int32_t height = rect.height() * 0.5;
            const int32_t x = (rect.width() / 2) - (width / 2);
            const int32_t y = (rect.height() / 2) - (height / 2);

            const QPen pen(Palette::tileYellow, 10);

            // Draws rounded rect
            painter.setPen(pen);
            painter.setBrush(Palette::tileGreen);
            painter.drawRoundedRect(x, y, width, height, 30, 30);

            // Draws icon and text
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

            painter.restore();
        }

        inline void paintMenuContent(QPainter &painter, QRect area, Sprites::Type sprite,
                                     const QString &mainText, QColor mainTextColor, const QString &additionalText)
        {
            // Calculates
            const int32_t imageSize = area.height() / 3;
            const int32_t imageX = area.x() + area.width() / 5 - imageSize / 2;
            const int32_t imageY = area.y() + imageSize / 2;

            const int32_t textSize = area.width() / 14;
            const int32_t textX = imageX + imageSize + textSize / 3;
            const int32_t textY = imageY + imageSize / 2 + textSize / 2;

            const int32_t infoTextSize = textSize / 3.5;
            const int32_t infoTextX = imageX;
            const int32_t infoTextY = imageY + imageSize + infoTextSize * 2;

            // Draws the icon
            painter.drawPixmap(imageX, imageY, imageSize, imageSize, Sprites::getSprite(sprite));

            // Draws the main text
            painter.setFont(QFont("Arial", textSize, QFont::DemiBold));
            painter.setPen(mainTextColor);
            painter.drawText(textX, textY, mainText);

            // Draws the additional text
            painter.setFont(QFont("Arial", infoTextSize, QFont::DemiBold));
            painter.setPen(Palette::infoText);

#ifndef Q_OS_ANDROID
            painter.drawText(infoTextX, infoTextY, "Space to " + additionalText + " game");
            painter.drawText(infoTextX, infoTextY + infoTextSize * 2, "Arrows or AWSD to move");
#else  // Q_OS_ANDROID
            painter.drawText(infoTextX, infoTextY, "Touch to " + additionalText + " game");
            painter.drawText(infoTextX, infoTextY + infoTextSize * 2, "Move by fingers");
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
        const Snake *_snake;
        const struct Apple *_apple;

        int32_t _tileSize;
        QVector2D _offset;

        GameLogic::GameState _state{GameLogic::GameState::Pause};

        const int32_t _cols;
        const int32_t _rows;
    };

} // namespane UI

#endif // SNAKE_FIELD_H
