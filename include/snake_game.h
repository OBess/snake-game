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

private:
    void keyPressEvent(QKeyEvent *event) override;

    void timerEvent(QTimerEvent *event) override;

    void setupUI();

    UI::SnakeField *_field = nullptr;
    UI::SnakeScore *_score = nullptr;
    GameLogic *_gameLogic = nullptr;

    int _timerId;
};
#endif // SNAKE_GAME_H
