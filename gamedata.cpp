#include "gamedata.h"


#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QStandardPaths>


// Function to get data files path
QString GameData::getDataFilePath()
{
    QString dataDir = QStandardPaths::writableLocation( QStandardPaths::AppDataLocation );
    return ( dataDir + "/games.json" );
}

// =====================================================================
// Function to save game data to a JSON file
// =====================================================================
// Function creates an array gamesArray and
// creates an object with all the data of the game
// which gets written to the json file
// =====================================================================
void GameData::saveGames( const QList<Game> &games )
{
    QJsonArray gamesArray{};

    for ( const Game &game : games )
    {
        QJsonObject obj;
        obj["name"] = game.name;
        obj["exePath"] = game.exePath;
        obj["coverImagePath"] = game.coverImagePath;
        obj["totalPlaytime"] = game.totalPlaytime;
        obj["lastPlayed"] = game.lastPlayed.toString( Qt::ISODate );
        gamesArray.append( obj );
    }

    QJsonDocument doc( gamesArray );
    QFile file( getDataFilePath() );

    if ( file.open(QIODevice::WriteOnly) )
    {
        file.write( doc.toJson() );
        file.close();
    }

}


// =====================================================================
// Function to read game data from a JSON file
// =====================================================================
// Function creates that reads from a json file
// and creates a list Game that gets filled up
// with all the different game data
// =====================================================================
QList<Game> GameData::loadGames()
{
    QList<Game> games;

    // Check: if game does not exist, return an empty list
    QFile file( getDataFilePath() );
    if ( file.open(QIODevice::ReadOnly) == false )
    {
        return games;
    }

    QJsonDocument doc = QJsonDocument::fromJson( file.readAll() );
    file.close();

    // Safety Check: incase file is corrupted or wrong format
    if ( doc.isArray() == false )
    {
        return games;
    }

    for ( const QJsonValue &val : doc.array() )
    {
        QJsonObject obj = val.toObject();
        Game game;
        game.name = obj["name"].toString();
        game.exePath = obj["exePath"].toString();
        game.coverImagePath = obj["coverImagePath"].toString();
        game.totalPlaytime = obj["totalPlaytime"].toInt();
        game.lastPlayed = QDateTime::fromString( obj["lastPlayed"].toString(), Qt::ISODate );
    }

    return games;
}
