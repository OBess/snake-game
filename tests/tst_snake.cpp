#include <QTest>

#include "snake.h"

class SnakeTest : public QObject
{
    Q_OBJECT

private slots:
    inline void tConstructor()
    {
        // Create a snake on position {0, 0} and looks up
        {
            const QVector2D pos(0, 0);

            Snake snake(Direction::Up, pos);

            // Checks head pos
            QCOMPARE(snake.headPos(), pos);

            // Checks body pos
            QCOMPARE(snake.body().size(), 5);

            compareMoveY(snake, pos);
        }

        // Create a snake on position {6, 0} and looks left
        {
            const QVector2D pos(6, 0);

            Snake snake(Direction::Left, pos);

            // Checks head pos
            QCOMPARE(snake.headPos(), pos);

            // Checks body pos
            QCOMPARE(snake.body().size(), 5);

            compareMoveX(snake, pos);
        }
    }

    inline void tMove()
    {
        // Move up
        {
            const QVector2D pos(10, 10);

            Snake snake(Direction::Up, pos);
            snake.move();

            QCOMPARE(snake.headPos(), pos - QVector2D(0, 1));
            compareMoveY(snake, pos - QVector2D(0, 1));
        }

        // Move left
        {
            const QVector2D pos(10, 10);

            Snake snake(Direction::Left, pos);
            snake.move();

            QCOMPARE(snake.headPos(), pos - QVector2D(1, 0));
            compareMoveX(snake, pos - QVector2D(1, 0));
        }
    }

    inline void tZigzagMove()
    {
        const QVector2D pos(10, 10);

        /*
         *     H (10, 9)
         *     b
         *     b
         *     b
         *     b
         *     t
         */
        Snake snake(Direction::Up, pos);
        snake.move();

        /*    (9, 9)
         *   H b
         *     b
         *     b
         *     b
         *     t
         *
         */
        snake.setDirection(Direction::Left);
        snake.move();

        /*   H (9, 8)
         *   b b
         *     b
         *     b
         *     t
         *
         *
         */
        snake.setDirection(Direction::Up);
        snake.move();

        // Check head position
        QCOMPARE(snake.headPos(), QVector2D(9, 8));

        // Check body position
        const auto &body = snake.body();

        QCOMPARE(body[0], QVector2D(9, 9));
        QCOMPARE(body[1], QVector2D(10, 9));
        QCOMPARE(body[2], QVector2D(10, 10));
        QCOMPARE(body[3], QVector2D(10, 11));
        QCOMPARE(body[4], QVector2D(10, 12));
    }

    inline void tSetDirection()
    {
        const QVector2D pos(10, 10);

        Snake snake(Direction::Up, pos);
        // For trigger boolean
        snake.setDirection(Direction::Up);

        // Cannot be set, because we didn't move
        snake.setDirection(Direction::Down);

        // Just move corresponding to set direction (Direction::Up)
        snake.move();

        QCOMPARE(snake.headPos(), pos - QVector2D(0, 1));
        compareMoveY(snake, pos - QVector2D(0, 1));
    }

    inline void tAddTailPart()
    {
        const QVector2D pos(5, 0);

        Snake snake(Direction::Up, pos);

        // Check size of body first
        QCOMPARE(snake.body().size(), 5);
        snake.addTailPart();

        // Check size of body after adding new part
        QCOMPARE(snake.body().size(), 6);

        // Move to check if new part of body is valid
        snake.move();

        QCOMPARE(snake.headPos(), pos - QVector2D(0, 1));
        compareMoveY(snake, pos - QVector2D(0, 1));
    }

private:
    constexpr void compareMoveY(const Snake &snake, QVector2D pos) noexcept
    {
        const float x = pos.x();
        float y = pos.y() + 1;
        for (const auto &part : snake.body())
        {
            QCOMPARE(part, QVector2D(x, y));
            ++y;
        }
    }

    constexpr void compareMoveX(const Snake &snake, QVector2D pos) noexcept
    {
        float x = pos.x() + 1;
        const float y = pos.y();
        for (const auto &part : snake.body())
        {
            QCOMPARE(part, QVector2D(x, y));
            ++x;
        }
    }
};

QTEST_MAIN(SnakeTest)
#include "tst_snake.moc"
