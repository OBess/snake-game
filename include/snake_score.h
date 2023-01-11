#ifndef SNAKE_SCORE_H
#define SNAKE_SCORE_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QPainter>

#include "palette.h"

namespace UI
{
    enum Score
    {
        Best,
        Goal
    };

    class SnakeScore : public QOpenGLWidget
    {
        Q_OBJECT

    public:
        explicit SnakeScore(uint32_t bestScore, QWidget *parent = nullptr)
            : QOpenGLWidget(parent), _bestScore(bestScore)
        {
            setMinimumHeight(50);
        }

        constexpr uint32_t bestScore() const noexcept
        {
            return _bestScore;
        }

        constexpr void incrementScroe() noexcept
        {
            ++_currentScore;

            if (_currentScore > _bestScore)
                _bestScore = _currentScore;
        }

    private:
        void paintEvent(QPaintEvent *event) override
        {
            Q_UNUSED(event);

            QPainter painter;
            painter.begin(this);

            // Fills background
            painter.fillRect(rect(), Palette::background);

            // Draws texts
            const QString bestScore(QString::number(_bestScore));
            const QString curScore(QString::number(_currentScore));

            painter.setFont(QFont("Arial", 20, QFont::DemiBold));

            //// Draws best score
            painter.drawPixmap(QRect(0, 0, 50, 50), getSprite(Score::Best));

            painter.setPen(Palette::cup);
            painter.drawText(QRect(52, 0, 60, 50), Qt::AlignVCenter, bestScore);

            //// Draws current score
            painter.drawPixmap(QRect(115, 0, 50, 50), getSprite(Score::Goal));

            painter.setPen(Qt::white);
            painter.drawText(QRect(167, 0, 60, 50), Qt::AlignVCenter, curScore);

            painter.end();
        }

        inline const QPixmap& getSprite(Score type)
        {
            static const QPixmap empty;
            static const QPixmap cup("://resources/cup.png");
            static const QPixmap goal("://resources/goal.png");

            if (type == Score::Best)
                return cup;
            else if (type == Score::Goal)
                return goal;

            return empty;
        }

    private:
        uint32_t _bestScore;
        uint32_t _currentScore{0};
    };

} // namespace UI

#endif // SNAKE_SCORE_H