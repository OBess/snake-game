#ifndef SPRITES_H
#define SPRITES_H

#include <QPixmap>

#include "direction.h"

namespace Sprites
{

    enum Type : uint8_t
    {
        Invalid = 0,

        Apple,

        SnakeHead,
        SnakeBody,
        SnakeTail,

        Cup,
        Goal,

        Icon,
        RedCross,
        Crown
    };

    /// @brief Returns a loaded sprite corresponding to the direction and type of sprite
    /// @param dir Direction of the sprite
    /// @param type Sprite type
    /// @return Image
    inline const QPixmap &getSprite(Direction dir, Type type)
    {
        // Invalid type
        static const QPixmap empty;

        static const QPixmap apple("://resources/images/apple.png");

        static const QPixmap headUp("://resources/images/head_up.png");
        static const QPixmap headRight("://resources/images/head_right.png");
        static const QPixmap headDown("://resources/images/head_down.png");
        static const QPixmap headLeft("://resources/images/head_left.png");

        static const QPixmap bodyHorizontal("://resources/images/body_horizontal.png");
        static const QPixmap bodyVertical("://resources/images/body_vertical.png");
        static const QPixmap bodyBottomLeft("://resources/images/body_bottomleft.png");
        static const QPixmap bodyBottomRight("://resources/images/body_bottomright.png");
        static const QPixmap bodyTopLeft("://resources/images/body_topleft.png");
        static const QPixmap bodyTopRight("://resources/images/body_topright.png");

        static const QPixmap tailEndUp("://resources/images/tail_up.png");
        static const QPixmap tailEndRight("://resources/images/tail_right.png");
        static const QPixmap tailEndDown("://resources/images/tail_down.png");
        static const QPixmap tailEndLeft("://resources/images/tail_left.png");

        static const QPixmap cup("://resources/images/cup.png");
        static const QPixmap goal("://resources/images/goal.png");

        static const QPixmap icon("://resources/images/icon.png");
        static const QPixmap redCross("://resources/images/red_cross.png");
        static const QPixmap crown("://resources/images/crown.png");

        if (type == Type::Apple)
        {
            return apple;
        }
        else if (type == Type::SnakeHead)
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
        else if (type == Type::SnakeBody)
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
        else if (type == Type::SnakeTail)
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
        else if (type == Type::Cup)
        {
            return cup;
        }
        else if (type == Type::Goal)
        {
            return goal;
        }
        else if (type == Type::Icon)
        {
            return icon;
        }
        else if (type == Type::RedCross)
        {
            return redCross;
        }
        else if (type == Type::Crown)
        {
            return crown;
        }

        return empty;
    }

    /// @brief Returns a loaded sprite corresponding only to the type of sprite
    /// @param type Sprite type
    /// @return Image
    inline const QPixmap &getSprite(Type type)
    {
        return getSprite({}, type);
    }

} // namespace Sprites

#endif // SPRITES_H
