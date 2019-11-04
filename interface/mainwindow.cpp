#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtDebug>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    renderWidget = new RenderWidget(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

