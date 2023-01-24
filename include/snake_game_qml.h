#ifndef SNAKE_GAME_QML_H
#define SNAKE_GAME_QML_H

#include <QObject>

namespace UI
{

class SnakeField;
class SnakeScore;

} // namespace UI
class GameLogic;

class SnakeGameQml : public QObject
{
    Q_OBJECT

public:
    SnakeGameQml(QObject *parent = nullptr);
    ~SnakeGameQml();

public slots:
    void onAppStateEvent(Qt::ApplicationState state);

private:
//    void keyPressEvent(QKeyEvent *event) override;

//    void mousePressEvent(QMouseEvent *event) override;

//    void mouseMoveEvent(QMouseEvent *event) override;

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


#endif // SNAKE_GAME_QML_H
