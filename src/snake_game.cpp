#include "snake_game.h"

#include <QDebug>
#include <QVBoxLayout>

#include "palette.h"
#include "snake.h"
#include "snake_field.h"
#include "snake_score.h"

SnakeGame::SnakeGame(QWidget *parent)
    : QWidget(parent)
{
    _snake = new Snake(Direction::Up, {0, 0});
    _apple = new Apple({5, 5});

    setupUI();
}

SnakeGame::~SnakeGame()
{
    delete _snake;
    delete _apple;
}

void SnakeGame::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
    {
        _snake->setDirection(Direction::Up);
    }
    else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
    {
        _snake->setDirection(Direction::Right);
    }
    else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
    {
        _snake->setDirection(Direction::Down);
    }
    else if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
    {
        _snake->setDirection(Direction::Left);
    }

    _snake->move();
    _field->update();
}

void SnakeGame::setupUI()
{
    setWindowTitle("SnakeGame");

    // Sets background color to widget
    QPalette windowPalette = palette();
    windowPalette.setColor(QPalette::Window, Palette::background);
    setPalette(windowPalette);

    QVBoxLayout *vLayout = new QVBoxLayout(this);

    _score = new UI::SnakeScore(10, this);
    vLayout->addWidget(_score);

    _field = new UI::SnakeField({_snake, _apple, {28, 14}}, this);
    vLayout->addWidget(_field);

    setLayout(vLayout);
}
