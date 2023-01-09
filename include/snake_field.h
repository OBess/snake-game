#ifndef SNAKE_FIELD_H
#define SNAKE_FIELD_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>

#include "palette.h"
#include "snake_system.h"

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
        const class Apple *apple;
        uint16_t rows;
        uint16_t cols;
    };

    class SnakeField : public QOpenGLWidget
    {
        Q_OBJECT

    public:
        explicit SnakeField(SnakeFieldArgs args, QWidget *parent = nullptr)
            : QOpenGLWidget{parent}, _snake{args.snake}, _apple{args.apple}, _cols{args.cols}, _rows{args.rows}
        {
        }

    private:
        void resizeEvent(QResizeEvent *event) override
        {
            paintField(event->size());
            update();
        }

        void paintEvent(QPaintEvent *event) override
        {
            QPainter painter;
            painter.begin(this);

            // Draws tiles for field
            painter.drawPixmap(0, 0, _cashedGrid);

            // Draws apple
            painter.drawPixmap(getTileRect(_apple->getPos() * _tileSize + _offset, _tileSize),
                               getTileSprite({}, SnakeTiles::Apple));

            // Draws snake head
            const auto headPos = _snake->headPos();
            painter.drawPixmap(getTileRect(headPos * _tileSize + _offset, _tileSize),
                               getTileSprite(_snake->getDirection(), SnakeTiles::Head));

            // Draws snake body
            const auto &tail = _snake->tail();

            //// Draws first part
            const auto &sprite = getBodyDir(headPos - tail[0], tail[0] - tail[1]);
            painter.drawPixmap(getTileRect(tail[0] * _tileSize + _offset, _tileSize),
                               getTileSprite(sprite, SnakeTiles::Body));

            for (size_t i = 1; i < tail.size() - 1; ++i)
            {
                const auto &sprite = getBodyDir(tail[i - 1] - tail[i], tail[i] - tail[i + 1]);
                painter.drawPixmap(getTileRect(tail[i] * _tileSize + _offset, _tileSize),
                                   getTileSprite(sprite, SnakeTiles::Body));
            }

            // Draws snake tail
            painter.drawPixmap(getTileRect(tail.back() * _tileSize + _offset, _tileSize),
                               getTileSprite(vectorToDir(tail.back() - tail[tail.size() - 2]), SnakeTiles::Tail));

            painter.end();
        }

        inline void paintField(const QSize &rect)
        {
            _cashedGrid = QPixmap(rect);
            _cashedGrid.fill(Palette::background);

            QPainter painter;
            painter.begin(&_cashedGrid);

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

        constexpr QRect getTileRect(QVector2D point, uint16_t size) const noexcept
        {
            return QRect(point.toPoint(), QSize{size, size});
        }

        inline const QPixmap &getTileSprite(Direction dir, SnakeTiles part) const
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
        const class Apple *_apple;

        uint16_t _tileSize = 1;
        QVector2D _offset;

        QPixmap _cashedGrid;

        const uint16_t _cols{28};
        const uint16_t _rows{14};
    };

} // namespane UI

#endif // SNAKE_FIELD_H
