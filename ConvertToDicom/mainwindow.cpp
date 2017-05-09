#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QCoreApplication::setOrganizationName("Tim Allman");
    QCoreApplication::setOrganizationDomain("brasscats.ca");
    QCoreApplication::setApplicationName("ConvertToDicom");

}

MainWindow::~MainWindow()
{
    delete ui;
}
