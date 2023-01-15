#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <QWidget>

namespace UI
{

    class SnakeField;
    class SnakeScore;

} // namespace UI
class GameLogic;

class SnakeGame : public QWidget
{
    Q_OBJECT

public:
    SnakeGame(QWidget *parent = nullptr);
    ~SnakeGame();

    void onAppStateEvent(Qt::ApplicationState state);

private:
    void keyPressEvent(QKeyEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void timerEvent(QTimerEvent *event) override;

    void setupUI();

    void setup(unsigned &bestScore, QSize &area);

    void save();

    void restart();

    UI::SnakeField *_field = nullptr;
    UI::SnakeScore *_score = nullptr;
    GameLogic *_gameLogic = nullptr;

    int _timerId;

    QPoint fingerLastPos;
};
#endif // SNAKE_GAME_H
