#ifndef SNAKE_SCORE_H
#define SNAKE_SCORE_H

#include <QOpenGLWidget>
#include <QPainter>

#include "palette.h"
#include "score.h"
#include "sprites.h"

namespace UI
{
    class SnakeScore : public QOpenGLWidget
    {
        Q_OBJECT

    public:
        explicit SnakeScore(const Score* score, QWidget *parent = nullptr)
            : QOpenGLWidget(parent), _score(score)
        {
            setFixedHeight(50);
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
            const QString bestScore(QString::number(_score->bestScore()));
            const QString curScore(QString::number(_score->currentScore()));

            painter.setFont(QFont("Arial", 20, QFont::DemiBold));

            //// Draws the best score
            painter.drawPixmap(QRect(0, 0, 50, 50), Sprites::getSprite(Sprites::Cup));

            painter.setPen(Palette::cup);
            painter.drawText(QRect(52, 0, 60, 50), Qt::AlignVCenter, bestScore);

            //// Draws the current score
            painter.drawPixmap(QRect(115, 0, 50, 50), Sprites::getSprite(Sprites::Goal));

            painter.setPen(Qt::white);
            painter.drawText(QRect(167, 0, 60, 50), Qt::AlignVCenter, curScore);

            painter.end();
        }

    private:
        const Score *_score;
    };

} // namespace UI

#endif // SNAKE_SCORE_H
