#include "parser.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QTextStream>
#include <stdexcept>

const QString INSERT_QUERY_TEXT = "INSERT INTO 'stats' (gameIndex, timestamp, controllerType, dead, "
                                  "damageGiven, damageTaken, healthPackCollected, framesTime, framesCount, averageFrameTime) "
                                  "VALUES (:gameIndex, :timestamp, :controllerType, :dead, "
                                  ":damageGiven, :damageTaken, :healthPackCollected, :framesTime, :framesCount, :averageFrameTime)";

Parser::Parser(QSqlDatabase database) :
    database(database)
{
}

void Parser::parseAndStore(const QStringList &files)
{
    int maxGameIndex = 0;
    int gameIndexOffset = 0;
    database.transaction();
    for (const auto &fileName : files) {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly)) {
            throw std::runtime_error(QString("Failed to open: " + fileName).toStdString());
        }

        gameIndexOffset += maxGameIndex;
        try {
            QTextStream in(&file);
            while(!in.atEnd()) {
                QStringList fields = in.readLine().split(";", QString::SplitBehavior::SkipEmptyParts);
                QSqlQuery query;
                query.prepare(INSERT_QUERY_TEXT);
                query.bindValue(":gameIndex", fields[0].toInt() + gameIndexOffset);
                query.bindValue(":timestamp", fields[1].toInt());
                query.bindValue(":controllerType", fields[2]);
                query.bindValue(":dead", QVariant(fields[3]).toBool() ? 1 : 0);
                query.bindValue(":damageGiven", fields[4].toFloat());
                query.bindValue(":damageTaken", fields[5].toFloat());
                query.bindValue(":healthPackCollected", QVariant(fields[6]).toBool() ? 1 : 0);
                query.bindValue(":framesTime", fields[7].toFloat());
                query.bindValue(":framesCount", fields[8].toInt());
                query.bindValue(":averageFrameTime", fields[9].toFloat());
                if (!query.exec()) {
                    throw std::runtime_error(query.lastError().text().toStdString());
                }
                maxGameIndex = std::max(maxGameIndex, fields[0].toInt() + 1);
            }
            file.close();
        } catch (std::runtime_error &e) {
            file.close();
            database.rollback();
            throw e;
        }
    }
    database.commit();
}
