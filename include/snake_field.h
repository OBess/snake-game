#ifndef SNAKE_FIELD_H
#define SNAKE_FIELD_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>

#include "apple.h"
#include "direction.h"
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

    class SnakeField : public QOpenGLWidget
    {
        Q_OBJECT

    public:
        explicit SnakeField(SnakeFieldArgs args, QWidget *parent = nullptr)
            : QOpenGLWidget{parent}, _snake{args.snake}, _apple{args.apple},
              _cols(args.cols), _rows(args.rols)
        {
            setMinimumSize(970, 500);
        }

    private:
        void paintEvent(QPaintEvent *event) override
        {
            QPainter painter;
            painter.begin(this);

            // Draws tiles for field
            paintField(painter, event);

            // Draws apple
            painter.drawPixmap(getTileRect(_apple->position * _tileSize + _offset, _tileSize),
                               Sprites::getSprite(Sprites::Apple));

            // Draws snake head
            const auto headPos = _snake->headPos();
            painter.drawPixmap(getTileRect(headPos * _tileSize + _offset, _tileSize),
                               Sprites::getSprite(_snake->getDirection(), Sprites::SnakeHead));

            // Draws snake body
            const auto &body = _snake->body();

            //// Draws first part of body
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

            // Draws snake tail
            painter.drawPixmap(getTileRect(body.back() * _tileSize + _offset, _tileSize),
                               Sprites::getSprite(vectorToDir(body.back() - body[body.size() - 2]),
                                                  Sprites::SnakeTail));

            painter.end();
        }

        /// @brief Draws tiles for grid
        /// @param painter Where to draw
        /// @param event Gets rect of the area
        inline void paintField(QPainter &painter, QPaintEvent *event)
        {
            painter.save();

            const auto rect = event->rect();

            painter.fillRect(rect, Palette::background);

            _tileSize = std::min(rect.width() / _cols, rect.height() / _rows);
            _offset = QVector2D((rect.width() - _tileSize * _cols) / 2,
                                (rect.height() - _tileSize * _rows) / 2);

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

        int32_t _tileSize = 1;
        QVector2D _offset;

        const int32_t _cols;
        const int32_t _rows;
    };

} // namespane UI

#endif // SNAKE_FIELD_H
