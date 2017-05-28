#ifndef PARSER_H
#define PARSER_H

#include <QSqlDatabase>


class Parser
{
    QSqlDatabase database;

public:
    Parser(QSqlDatabase database);

    void parseAndStore(const QStringList &files);
};

#endif // PARSER_H
