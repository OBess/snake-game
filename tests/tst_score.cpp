#include <QTest>

#include "score.h"

class ScoreTest : public QObject
{
    Q_OBJECT

private slots:
    inline void tConstructor() noexcept
    {
        // The current score 0 by default
        {
            Score score(10);

            QCOMPARE(score.bestScore(), 10);
            QCOMPARE(score.currentScore(), 0);
        }

        // Pass a current score
        {
            Score score(10, 9);

            QCOMPARE(score.bestScore(), 10);
            QCOMPARE(score.currentScore(), 9);
        }
    }

    inline void tIncrementScore() noexcept
    {
        // Just increment the current score
        {
            Score score(5);
            score.incrementScore();

            QCOMPARE(score.bestScore(), 5);
            QCOMPARE(score.currentScore(), 1);
        }

        // Increment the current score by 1 to be equal to the best score
        {
            Score score(5, 4);
            score.incrementScore();

            QCOMPARE(score.bestScore(), 5);
            QCOMPARE(score.currentScore(), 5);
        }

        // Inrement the current score with the best score
        {
            Score score(5, 5);
            score.incrementScore();

            QCOMPARE(score.bestScore(), 6);
            QCOMPARE(score.currentScore(), 6);

            score.incrementScore();
            QCOMPARE(score.bestScore(), 7);
            QCOMPARE(score.currentScore(), 7);
        }
    }

    inline void tClearCurrentScore() noexcept
    {
        // Just clear nothing
        {
            Score score(5);
            score.clearCurrentScore();

            QCOMPARE(score.currentScore(), 0);
        }

        // Clear score
        {
            Score score(5, 1);
            score.clearCurrentScore();

            QCOMPARE(score.currentScore(), 0);
        }
    }
};

QTEST_MAIN(ScoreTest)
#include "tst_score.moc"
