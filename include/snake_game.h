#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <QWidget>

namespace UI
{

    class SnakeField;

} // namespace UI
class Snake;
class Apple;

class SnakeGame : public QWidget
{
    Q_OBJECT

public:
    SnakeGame(QWidget *parent = nullptr);
    ~SnakeGame();

private:
    void keyPressEvent(QKeyEvent *event) override;

    void setupUI();

    UI::SnakeField *_field = nullptr;
    Snake *_snake = nullptr;
    class Apple *_apple = nullptr;
};
#endif // SNAKE_GAME_H
