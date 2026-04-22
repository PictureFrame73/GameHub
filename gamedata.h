#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QString>
#include <QDateTime>
#include <QList>

// Game data
struct Game
{
    QString name;
    QString exePath;
    QString coverImagePath;
    int totalPlaytime{ 0 };
    QDateTime lastPlayed;
};

class GameData
{
public:
    static void saveGames( const QList<Game> &games );
    static QList<Game> loadGames();
    static QString getDataFilePath();

};

#endif // GAMEDATA_H
