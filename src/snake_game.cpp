#include "snake_game.h"

#include <QVBoxLayout>

#include "direction.h"
#include "game_logic.h"
#include "palette.h"
#include "snake_field.h"
#include "snake_score.h"

SnakeGame::SnakeGame(QWidget *parent)
    : QWidget(parent)
{
    _gameLogic = new GameLogic({28, 14}, 0);

    setupUI();

    _timerId = startTimer(150);
}

SnakeGame::~SnakeGame()
{
    killTimer(_timerId);

    delete _gameLogic;
}

void SnakeGame::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
    {
        _gameLogic->setDirection(Direction::Up);
    }
    else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
    {
        _gameLogic->setDirection(Direction::Right);
    }
    else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
    {
        _gameLogic->setDirection(Direction::Down);
    }
    else if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
    {
        _gameLogic->setDirection(Direction::Left);
    }
    // TODO: Delete this branch
    else if (event->key() == Qt::Key_Space)
    {
        _gameLogic->start();
    }
}

void SnakeGame::timerEvent(QTimerEvent *event)
{
    _gameLogic->update();
    _field->update();
    _score->update();
}

void SnakeGame::setupUI()
{
    setWindowTitle("SnakeGame");

    // Sets the background color to widget
    QPalette windowPalette = palette();
    windowPalette.setColor(QPalette::Window, Palette::background);
    setPalette(windowPalette);

    QVBoxLayout *vLayout = new QVBoxLayout(this);

    // Creates the snake score widget
    _score = new UI::SnakeScore(_gameLogic->score(), this);
    vLayout->addWidget(_score);

    // Creates the snake field widget
    const auto area = _gameLogic->area();

    _field = new UI::SnakeField({_gameLogic->snake(), _gameLogic->apple(),
                                 area.width(), area.height()}, this);
    vLayout->addWidget(_field);

    // Sets the layout
    setLayout(vLayout);
}
