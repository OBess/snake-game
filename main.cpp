#include "snake_game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SnakeGame w;

#ifdef Q_OS_ANDROID
    // This connect exists to work with android states
    QObject::connect(&a, &QGuiApplication::applicationStateChanged, &w, &SnakeGame::onAppStateEvent);
#endif // Q_OS_ANDROID

    w.show();
    return a.exec();
}
