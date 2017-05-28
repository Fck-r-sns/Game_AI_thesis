#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <stdexcept>
#include "parser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("D:\\Education\\Game_AI_thesis\\VectorTacticsAgentsStats\\Files\\stats.sqlite");
    if (!database.open()) {
        throw std::runtime_error("Failed to open database");
    }

    MainWindow w(database);
    w.show();

    return a.exec();
}
