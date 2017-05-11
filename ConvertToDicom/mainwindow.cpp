#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "seriesinfo.h"
#include "dicomattributesdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dicomAttributesDialog(0)
{
    ui->setupUi(this);

    QCoreApplication::setOrganizationName("Tim Allman");
    QCoreApplication::setOrganizationDomain("brasscats.ca");
    QCoreApplication::setApplicationName("ConvertToDicom");

    // Here we connect the SeriesInfo instance to the appropriate widgets.
    SeriesInfo* seriesInfo = &SeriesInfo::getInstance();

    connect(ui->overWriteCheckBox, SIGNAL(toggled(bool)), seriesInfo, SLOT(setOverwrite(bool)));
    connect(ui->sourceDirLineEdit, SIGNAL(editingFinished()), seriesInfo, SLOT(setInputDir(const QString&)));
    connect(ui->destDirLineEdit, SIGNAL(editingFinished()), seriesInfo, SLOT(setOutputDir(const QString&)));
    connect(ui->editDicomAttributesPushButton, SIGNAL(clicked()), this, SLOT(execDicomAttributesDialog()));

    connect(seriesInfo, SIGNAL(setOverwriteFiles(bool)), ui->overWriteCheckBox, SLOT(setChecked(bool)));
    connect(seriesInfo, SIGNAL(setInputDir(const QString&)), ui->sourceDirLineEdit, SLOT(setText(const QString&)));
    connect(seriesInfo, SIGNAL(setOutputDir(const QString&)), ui->destDirLineEdit, SLOT(setText(const QString&)));

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
