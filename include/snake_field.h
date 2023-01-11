#ifndef SNAKE_FIELD_H
#define SNAKE_FIELD_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>

#include "apple.h"
#include "palette.h"
#include "snake.h"

namespace UI
{
    enum SnakeTiles : uint8_t
    {
        Apple,
        Head,
        Body,
        Tail
    };

    struct SnakeFieldArgs final
    {
        const Snake *snake;
        const struct Apple *apple;
        QSize fieldSize;
    };

    class SnakeField : public QOpenGLWidget
    {
        Q_OBJECT

    public:
        explicit SnakeField(SnakeFieldArgs args, QWidget *parent = nullptr)
            : QOpenGLWidget{parent}, _snake{args.snake}, _apple{args.apple},
              _cols(args.fieldSize.width()), _rows(args.fieldSize.height())
        {
            setMinimumSize(970, 500);
        }

    private:
        void resizeEvent(QResizeEvent *event) override
        {
            paintField(event->size());
            update();
        }

        void paintEvent(QPaintEvent *event) override
        {
            Q_UNUSED(event);

            QPainter painter;
            painter.begin(this);

            // Draws cached tiles for field
            painter.drawPixmap(0, 0, _cachedGrid);

            // Draws apple
            painter.drawPixmap(getTileRect(_apple->position * _tileSize + _offset, _tileSize),
                               getSprite({}, SnakeTiles::Apple));

            // Draws snake head
            const auto headPos = _snake->headPos();
            painter.drawPixmap(getTileRect(headPos * _tileSize + _offset, _tileSize),
                               getSprite(_snake->getDirection(), SnakeTiles::Head));

            // Draws snake body
            const auto &body = _snake->body();

            //// Draws first part of body
            const auto &sprite = getBodyDir(headPos - body[0], body[0] - body[1]);
            painter.drawPixmap(getTileRect(body[0] * _tileSize + _offset, _tileSize),
                               getSprite(sprite, SnakeTiles::Body));

            //// Draws rest parts
            for (size_t i = 1; i < body.size() - 1; ++i)
            {
                const auto &sprite = getBodyDir(body[i - 1] - body[i], body[i] - body[i + 1]);
                painter.drawPixmap(getTileRect(body[i] * _tileSize + _offset, _tileSize),
                                   getSprite(sprite, SnakeTiles::Body));
            }

            // Draws snake tail
            painter.drawPixmap(getTileRect(body.back() * _tileSize + _offset, _tileSize),
                               getSprite(vectorToDir(body.back() - body[body.size() - 2]), SnakeTiles::Tail));

            painter.end();
        }

        /// @brief Redraws tiles for grid and caches to QPixmap
        /// @param rect Size of the field
        inline void paintField(const QSize &rect)
        {
            _cachedGrid = QPixmap(rect);
            _cachedGrid.fill(Palette::background);

            QPainter painter;
            painter.begin(&_cachedGrid);

            painter.setPen(QPen(Palette::transparency));

            _tileSize = rect.width() / _cols;
            _offset = QVector2D((rect.width() - _tileSize * _cols) / 2,
                                (rect.height() - _tileSize * _rows) / 2);

            uint16_t x = _offset.x();
            uint16_t y = _offset.y();
            uint16_t step = 0;

            for (uint16_t i = 0; i < _rows; ++i)
            {
                for (uint16_t j = 0; j < _cols; ++j)
                {
                    painter.setBrush(step % 2 ? Palette::tileGreen : Palette::tileYellow);
                    painter.drawRect(x, y, _tileSize, _tileSize);

                    x += _tileSize;
                    ++step;
                }

                x = _offset.x();
                y += _tileSize;
                ++step;
            }

            painter.end();
        }

        /// @brief Gets position and size and creates QRect
        /// @param point Position to start draw a tile
        /// @param size Size of one tile
        /// @return QRect for one tile
        constexpr QRect getTileRect(QVector2D point, uint16_t size) const noexcept
        {
            return QRect(point.toPoint(), QSize{size, size});
        }

        /// @brief 
        /// @param dir 
        /// @param part 
        /// @return 
        inline const QPixmap &getSprite(Direction dir, SnakeTiles part) const
        {
            static const QPixmap empty;

            static const QPixmap apple("://resources/apple.png");

            static const QPixmap headUp("://resources/head_up.png");
            static const QPixmap headRight("://resources/head_right.png");
            static const QPixmap headDown("://resources/head_down.png");
            static const QPixmap headLeft("://resources/head_left.png");

            static const QPixmap bodyHorizontal("://resources/body_horizontal.png");
            static const QPixmap bodyVertical("://resources/body_vertical.png");
            static const QPixmap bodyBottomLeft("://resources/body_bottomleft.png");
            static const QPixmap bodyBottomRight("://resources/body_bottomright.png");
            static const QPixmap bodyTopLeft("://resources/body_topleft.png");
            static const QPixmap bodyTopRight("://resources/body_topright.png");

            static const QPixmap tailEndUp("://resources/tail_up.png");
            static const QPixmap tailEndRight("://resources/tail_right.png");
            static const QPixmap tailEndDown("://resources/tail_down.png");
            static const QPixmap tailEndLeft("://resources/tail_left.png");

            if (part == SnakeTiles::Apple)
            {
                return apple;
            }
            else if (part == SnakeTiles::Head)
            {
                if (dir == Direction::Up)
                    return headUp;
                else if (dir == Direction::Right)
                    return headRight;
                else if (dir == Direction::Down)
                    return headDown;
                else if (dir == Direction::Left)
                    return headLeft;
            }
            else if (part == SnakeTiles::Body)
            {
                if (dir == Direction::Vertical)
                    return bodyVertical;
                else if (dir == Direction::Horizontal)
                    return bodyHorizontal;
                else if (dir == Direction::DownLeft)
                    return bodyBottomLeft;
                else if (dir == Direction::DownRight)
                    return bodyBottomRight;
                else if (dir == Direction::LeftUp)
                    return bodyTopRight;
                else if (dir == Direction::RightUp)
                    return bodyTopLeft;
            }
            else if (part == SnakeTiles::Tail)
            {
                if (dir == Direction::Up)
                    return tailEndUp;
                else if (dir == Direction::Right)
                    return tailEndRight;
                else if (dir == Direction::Down)
                    return tailEndDown;
                else if (dir == Direction::Left)
                    return tailEndLeft;
            }

            return empty;
        }

        /// @brief 
        /// @param lhs 
        /// @param rhs 
        /// @return 
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

        uint16_t _tileSize = 1;
        QVector2D _offset;

        QPixmap _cachedGrid;

        const uint16_t _cols{28};
        const uint16_t _rows{14};
    };

} // namespane UI

#endif // SNAKE_FIELD_H
