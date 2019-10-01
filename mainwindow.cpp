#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    render_widget = new RenderWidget(this);
    Cube cube(4, 50, 50, 50);
    render_widget->renderModel(Qt::red, cube);
}

MainWindow::~MainWindow()
{
    delete ui;
}
