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

    ~Sounds()
    {
        delete _crunchPlayer;
        delete _owPlayer;
        delete _hitPlayer;
    }

    inline void play(Type type) const noexcept
    {
        if (_inited == false)
        {
            return;
        }
        else if (type == Type::Crunch)
        {
            _crunchPlayer->play();
        }
        else if (type == Type::Ow)
        {
            _owPlayer->play();
        }
        else if (type == Type::Hit)
        {
            _hitPlayer->play();
        }
    }

private:
    inline void init()
    {
        {
            _crunchPlayer = new QMediaPlayer;

            QMediaPlaylist *playlist = new QMediaPlaylist(_crunchPlayer);
            playlist->addMedia(QUrl("qrc:/resources/sounds/crunch.wav"));
            playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

            _crunchPlayer->setPlaylist(playlist);
        }

        {
            _owPlayer = new QMediaPlayer;

            QMediaPlaylist *playlist = new QMediaPlaylist(_owPlayer);
            playlist->addMedia(QUrl("qrc:/resources/sounds/ow.mp3"));
            playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

            _owPlayer->setPlaylist(playlist);
        }

        {
            _hitPlayer = new QMediaPlayer;

            QMediaPlaylist *playlist = new QMediaPlaylist(_hitPlayer);
            playlist->addMedia(QUrl("qrc:/resources/sounds/hit.wav"));
            playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

            _hitPlayer->setPlaylist(playlist);
        }

        _inited = true;
    }

private:
    bool _inited = false;

    QMediaPlayer *_crunchPlayer = nullptr;
    QMediaPlayer *_owPlayer = nullptr;
    QMediaPlayer *_hitPlayer = nullptr;
};

#endif // SOUNDS_H
