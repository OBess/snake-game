#ifndef SOUNDS_H
#define SOUNDS_H

#include <QMediaPlayer>
#include <QMediaPlaylist>

class Sounds
{
public:
    enum class Type
    {
        Crunch,
        Ow,
        Hit
    };

    Sounds()
    {
        init();
    }

    inline void play(Type type) noexcept
    {
        if (type == Type::Crunch)
        {
            _crunchPlayer.play();
        }
        else if (type == Type::Ow)
        {
            _owPlayer.play();
        }
        else if (type == Type::Hit)
        {
            _hitPlayer.play();
        }
    }

private:
    inline void init()
    {
        {
            QMediaPlaylist *playlist = new QMediaPlaylist(&_crunchPlayer);
            playlist->addMedia(QUrl("qrc:/resources/sounds/crunch.wav"));
            playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

            _crunchPlayer.setPlaylist(playlist);
        }

        {
            QMediaPlaylist *playlist = new QMediaPlaylist(&_owPlayer);
            playlist->addMedia(QUrl("qrc:/resources/sounds/ow.mp3"));
            playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

            _owPlayer.setPlaylist(playlist);
        }

        {
            QMediaPlaylist *playlist = new QMediaPlaylist(&_hitPlayer);
            playlist->addMedia(QUrl("qrc:/resources/sounds/hit.wav"));
            playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

            _hitPlayer.setPlaylist(playlist);
        }
    }

private:
    QMediaPlayer _crunchPlayer;
    QMediaPlayer _owPlayer;
    QMediaPlayer _hitPlayer;
};

#endif // SOUNDS_H
