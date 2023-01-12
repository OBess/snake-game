#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <QWidget>

class Snake;
struct Apple;
class Score;

class SnakeGame : public QWidget
{
    Q_OBJECT

public:
    SnakeGame(QWidget *parent = nullptr);
    ~SnakeGame();

private:
    void keyPressEvent(QKeyEvent *event) override;

    void setupUI();

    Snake *_snake = nullptr;
    Apple *_apple = nullptr;
    Score *_score = nullptr;
};
#endif // SNAKE_GAME_H
