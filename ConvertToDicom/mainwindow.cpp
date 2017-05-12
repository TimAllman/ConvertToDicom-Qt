#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "seriesinfo.h"
#include "dicomattributesdialog.h"

#include "settings.h"

#include <QObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dicomAttributesDialog(0)
{
    ui->setupUi(this);

    QCoreApplication::setOrganizationName("Tim Allman");
    QCoreApplication::setOrganizationDomain("brasscats.ca");
    QCoreApplication::setApplicationName("ConvertToDicom");

    // Do this to show the DICOM dialog
    connect(ui->editDicomAttributesPushButton, SIGNAL(clicked()), this, SLOT(execDicomAttributesDialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dicomAttributesDialog;
}

void MainWindow::execDicomAttributesDialog()
{
    if (dicomAttributesDialog == 0)
    {
        dicomAttributesDialog = new DicomAttributesDialog(this);
    }

    // Load up the dialog from the SeriesInfo object
    SeriesInfo& info = SeriesInfo::getInstance();

    if (dicomAttributesDialog->exec() == QDialog::Accepted)
    {
        // Save all of the data into our SeriesInfo object
    }
}

void MainWindow::loadSettings()
{

}

void MainWindow::saveSettings()
{
    // save the current settings
    Settings settings;

    settings.setValue(Settings::LoggingLevelKey, logger.getLogLevel());

}

