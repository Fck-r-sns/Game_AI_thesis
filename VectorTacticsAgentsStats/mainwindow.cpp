#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include "parser.h"

MainWindow::MainWindow(QSqlDatabase database, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    database(database)
{
    ui->setupUi(this);
    connect(ui->clearTableButton, &QPushButton::clicked, this, &MainWindow::clearTable);
    connect(ui->openFilesButton, &QPushButton::clicked, this, &MainWindow::openFiles);
    connect(ui->parseFilesButton, &QPushButton::clicked, this, &MainWindow::parseFiles);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearTable()
{
    QSqlQuery query;
    if (!query.exec("DELETE FROM 'stats'")) {
        throw std::runtime_error(query.lastError().text().toStdString());
    }
}

void MainWindow::openFiles()
{
    files = QFileDialog::getOpenFileNames(this);
    ui->filesToParse->clear();
    for (const auto &file : files) {
        ui->filesToParse->appendPlainText(file);
    }
}

void MainWindow::parseFiles()
{
    Parser(database).parseAndStore(files);
}
