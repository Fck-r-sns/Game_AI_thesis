#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QSqlDatabase database, QWidget *parent = 0);
    ~MainWindow();

private:
    void clearTable();
    void openFiles();
    void parseFiles();

private:
    Ui::MainWindow *ui;
    QSqlDatabase database;
    QStringList files;
};

#endif // MAINWINDOW_H
