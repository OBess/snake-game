#include "snake_game.h"

#include <QScreen>
#include <QSettings>
#include <QVector2D>
#include <QVBoxLayout>

#include "direction.h"
#include "game_logic.h"
#include "palette.h"
#include "settings.h"
#include "snake_field.h"
#include "snake_score.h"

SnakeGame::SnakeGame(QWidget *parent)
    : QWidget(parent)
{
    _gameLogic = new GameLogic({28, 14}, 0);

    setupUI();
    setup();

    _timerId = startTimer(150);
}

SnakeGame::~SnakeGame()
{
    killTimer(_timerId);

    save();

    delete _gameLogic;
}

void SnakeGame::onAppStateEvent(Qt::ApplicationState state)
{
#ifdef Q_OS_ANDROID

    static bool paused = false;

    // When user hide application on android OS
    if (state == Qt::ApplicationInactive ||
        state == Qt::ApplicationSuspended ||
        state == Qt::ApplicationHidden)
    {
        save();

        if (_gameLogic->doesGameGoOn())
        {
            _gameLogic->pause();
            paused = true;
        }
    }
    else if (state == Qt::ApplicationActive)
    {
        if (paused)
        {
            _gameLogic->play();
            paused = false;
        }
    }

#endif // Q_OS_ANDROID
}


void SnakeGame::keyPressEvent(QKeyEvent *event)
{
#ifndef Q_OS_ANDROID
    if (_gameLogic->doesGameGoOn())
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
        else if (event->key() == Qt::Key_R)
        {
            restart();
        }
    }
    else if (event->key() == Qt::Key_Space)
    {
        restart();
    }
#endif // Q_OS_ANDROID
}

void SnakeGame::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_ANDROID
    if (_gameLogic->doesGameGoOn() == false)
    {
        restart();
    }

    fingerLastPos = event->pos();
#endif // Q_OS_ANDROID
}

void SnakeGame::mouseMoveEvent(QMouseEvent *event)
{
#ifdef Q_OS_ANDROID
    static const float lengthToMove = 5;

    if (_gameLogic->doesGameGoOn())
    {
        QVector2D vector(event->pos() - fingerLastPos);

        if (vector.length() > lengthToMove)
        {
            vector.normalize();

            //
            auto closeX = 1 - std::abs(vector.x());
            auto closeY = 1 - std::abs(vector.y());

            //
            if (closeX < closeY)
            {
                closeX = 1 * (vector.x() < 0 ? -1 : 1);
                closeY = 0;
            }
            else
            {
                closeX = 0;
                closeY = 1 * (vector.y() < 0 ? -1 : 1);
            }

            _gameLogic->setDirection(vectorToDir({closeX, closeY}));
        }

        //
        fingerLastPos = event->pos();
    }
#endif // Q_OS_ANDROID
}

void SnakeGame::timerEvent(QTimerEvent *event)
{
    _gameLogic->update();
    _score->update();

    _field->setState(_gameLogic->gameState());
    _field->update();
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

void SnakeGame::setup()
{
    QSettings settings(Settings::Ini::FILE_PATH, QSettings::IniFormat);

#ifndef Q_OS_ANDROID
    settings.beginGroup(Settings::Ini::MAIN_WINDOW);

    if (settings.value(Settings::Ini::IS_MAXIMIZED, false).toBool())
    {
        showMaximized();
    }
    else
    {
        resize(settings.value(Settings::Ini::WIDTH, 640).toInt(),
               settings.value(Settings::Ini::HEIGHT, 480).toInt());

        // Keep the application in the screen area
        const QSize screenSize = screen()->size();

        int pos_x = settings.value(Settings::Ini::POS_X, 0).toInt();
        int pos_y = settings.value(Settings::Ini::POS_Y, 0).toInt();

        if (pos_x + width() > screenSize.width())
        {
            pos_x = screenSize.width() - width();
        }
        else if (pos_x < 0)
        {
            pos_x = 0;
        }

        if (pos_y + height() > screenSize.height())
        {
            pos_y = screenSize.height() - height();
        }
        else if (pos_y < 0)
        {
            pos_y = 0;
        }

        move(pos_x, pos_y);
    }

    settings.endGroup();
#endif // Q_OS_ANDROID

    // Reades best score
    settings.beginGroup(Settings::Ini::GAME);

    const int bestScore = settings.value(Settings::Ini::BEST, 0).toInt();
    _gameLogic->score()->setBestScore(bestScore);

    settings.endGroup();
}

void SnakeGame::save()
{
    QSettings settings(Settings::Ini::FILE_PATH, QSettings::IniFormat);

#ifndef Q_OS_ANDROID
    settings.beginGroup(Settings::Ini::MAIN_WINDOW);

    settings.setValue(Settings::Ini::IS_MAXIMIZED, isMaximized());
    settings.setValue(Settings::Ini::WIDTH, width());
    settings.setValue(Settings::Ini::HEIGHT, height());
    settings.setValue(Settings::Ini::POS_X, pos().x());
    settings.setValue(Settings::Ini::POS_Y, pos().y() - 38); // 38 it is the height of title bar

    settings.endGroup();
#endif // Q_OS_ANDROID

    settings.beginGroup(Settings::Ini::GAME);
    settings.setValue(Settings::Ini::BEST, QString::number(_gameLogic->score()->bestScore()));
    settings.endGroup();
}

void SnakeGame::restart()
{
    _gameLogic->restart();

    _field->setApple(_gameLogic->apple());
    _field->setSnake(_gameLogic->snake());
}
