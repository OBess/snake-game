#include <QTest>

#include "game_logic.h"

class LogicTest : public QObject
{
    Q_OBJECT

private slots:
    inline void tState()
    {
        const QSize area(2, 10);

        GameLogic gameLogic(area, 0);

        // Check init state
        QCOMPARE(gameLogic.gameState(), GameLogic::GameState::Pause);
        QCOMPARE(gameLogic.doesGameGoOn(), false);

        // Check play state
        gameLogic.start();
        QCOMPARE(gameLogic.gameState(), GameLogic::GameState::Play);
        QCOMPARE(gameLogic.doesGameGoOn(), true);

        // Check pause state
        gameLogic.pause();
        QCOMPARE(gameLogic.gameState(), GameLogic::GameState::Pause);
        QCOMPARE(gameLogic.doesGameGoOn(), false);

        // Check end game state
        gameLogic.start();

        const size_t appleToWin = (area.height() * area.width()) * 0.7;

        for (size_t i = 0; i < appleToWin; ++i)
        {
            gameLogic.apple()->position = gameLogic.snake()->headPos() - QVector2D(0, 1);
            gameLogic.update();
        }

        QCOMPARE(gameLogic.gameState(), GameLogic::GameState::EndGame);
        QCOMPARE(gameLogic.doesGameGoOn(), false);
    }

    inline void tSetDirection()
    {
        const QSize area(2, 2);

        GameLogic gameLogic(area, 0);
        // Check init direction
        QCOMPARE(gameLogic.getDirection(), Direction::Up);

        // Check set direction
        gameLogic.setDirection(Direction::Left);
        QCOMPARE(gameLogic.getDirection(), Direction::Left);

        // Check if we cannot set opposite direction
        gameLogic.setDirection(Direction::Right);
        QCOMPARE(gameLogic.getDirection(), Direction::Left);
    }

    inline void tHitTheWall()
    {
        const QSize area(2, 2);

        GameLogic gameLogic(area, 0);
        gameLogic.start();

        // Some updates to hit the wall
        gameLogic.update();
        gameLogic.update();
        gameLogic.update();
        gameLogic.update();

        QCOMPARE(gameLogic.gameState(), GameLogic::GameState::GameOver);
    }

    inline void tHitTheBody()
    {
        const QSize area(2, 2);

        GameLogic gameLogic(area, 0);
        gameLogic.start();

        // Some updates to hit the body
        gameLogic.setDirection(Direction::Left);
        gameLogic.update();

        gameLogic.setDirection(Direction::Down);
        gameLogic.update();

        gameLogic.setDirection(Direction::Right);
        gameLogic.update();

        QCOMPARE(gameLogic.gameState(), GameLogic::GameState::GameOver);
    }
};

QTEST_MAIN(LogicTest)
#include "tst_logic.moc"
