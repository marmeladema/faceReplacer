#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QStringList>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::cout << ui->frameListWidget->acceptDrops() << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

