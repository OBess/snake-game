#include <QTest>

#include "direction.h"

class DirectionTest : public QObject
{
    Q_OBJECT

private slots:
    inline void tDirToVector() noexcept
    {
        // Four main directions
        QCOMPARE(dirToVector(Direction::Up), QVector2D(0, -1));
        QCOMPARE(dirToVector(Direction::Right), QVector2D(1, 0));
        QCOMPARE(dirToVector(Direction::Down), QVector2D(0, 1));
        QCOMPARE(dirToVector(Direction::Left), QVector2D(-1, 0));

        // Any other direction
        QCOMPARE(dirToVector(Direction::Invalid), QVector2D(0, 0));
        QCOMPARE(dirToVector(Direction::Horizontal), QVector2D(0, 0));
        QCOMPARE(dirToVector(Direction::Vertical), QVector2D(0, 0));
        QCOMPARE(dirToVector(Direction::UpLeft), QVector2D(0, 0));
        QCOMPARE(dirToVector(Direction::UpRight), QVector2D(0, 0));
        QCOMPARE(dirToVector(Direction::LeftUp), QVector2D(0, 0));
        QCOMPARE(dirToVector(Direction::RightUp), QVector2D(0, 0));
        QCOMPARE(dirToVector(Direction::DownLeft), QVector2D(0, 0));
        QCOMPARE(dirToVector(Direction::DownRight), QVector2D(0, 0));
        QCOMPARE(dirToVector(Direction::LeftDown), QVector2D(0, 0));
        QCOMPARE(dirToVector(Direction::RightDown), QVector2D(0, 0));
    }

    inline void tVectorToDir() noexcept
    {
        // Four main directions
        QCOMPARE(vectorToDir(QVector2D(0, -1)), Direction::Up);
        QCOMPARE(vectorToDir(QVector2D(1, 0)), Direction::Right);
        QCOMPARE(vectorToDir(QVector2D(0, 1)), Direction::Down);
        QCOMPARE(vectorToDir(QVector2D(-1, 0)), Direction::Left);

        // Any other direction
        QCOMPARE(vectorToDir(QVector2D(-1, -1)), Direction::Invalid);
        QCOMPARE(vectorToDir(QVector2D(1, 1)), Direction::Invalid);
        QCOMPARE(vectorToDir(QVector2D(0, 0)), Direction::Invalid);
    }

    inline void tIsOpposite() noexcept
    {
        // Four main directions
        QVERIFY(isOpposite(Direction::Left, Direction::Right));
        QVERIFY(isOpposite(Direction::Right, Direction::Left));
        QVERIFY(isOpposite(Direction::Up, Direction::Down));
        QVERIFY(isOpposite(Direction::Down, Direction::Up));

        // Any other direction
        QCOMPARE(isOpposite(Direction::Left, Direction::Up), false);
        QCOMPARE(isOpposite(Direction::Left, Direction::Down), false);
        QCOMPARE(isOpposite(Direction::Down, Direction::Left), false);
        QCOMPARE(isOpposite(Direction::Up, Direction::Left), false);
        QCOMPARE(isOpposite(Direction::Right, Direction::Up), false);
        QCOMPARE(isOpposite(Direction::Right, Direction::Down), false);
        QCOMPARE(isOpposite(Direction::Down, Direction::Right), false);
        QCOMPARE(isOpposite(Direction::Up, Direction::Right), false);
    }
};

QTEST_MAIN(DirectionTest)
#include "tst_direction.moc"
