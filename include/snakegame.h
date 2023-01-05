#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <QWidget>

class SnakeGame : public QWidget
{
    Q_OBJECT

public:
    SnakeGame(QWidget *parent = nullptr);
    ~SnakeGame();
};
#endif // SNAKEGAME_H
