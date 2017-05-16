#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "seriesinfo.h"
#include "seriesconverter.h"
#include "dicomattributesdialog.h"
#include "logger.h"

#include "settings.h"

#include <string>

#include <QObject>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    seriesInfo(SeriesInfo::getInstance()),
    dicomAttributesDialog(0),
    seriesConverter(new SeriesConverter()),
    logger(Logger::getInstance(std::string(LOGGER_NAME) + ".MainWindow"))
{
    ui->setupUi(this);

    QCoreApplication::setOrganizationName("Tim Allman");
    QCoreApplication::setOrganizationDomain("brasscats.ca");
    QCoreApplication::setApplicationName("ConvertToDicom");

    // Do this to show the DICOM dialog
    connect(ui->editDicomAttributesPushButton, SIGNAL(clicked()), this, SLOT(execDicomAttributesDialog()));
    connect(ui->sourceDirChoosePushButton, SIGNAL(clicked()), this, SLOT(handleSourceDirPushButtonClicked()));
    connect(ui->destDirChooseBushButton, SIGNAL(clicked()), this, SLOT(handleDestDirPushButtonClicked()));

    ui->sourceDirLineEdit->setText(seriesInfo.inputDirStr());
    ui->destDirLineEdit->setText(seriesInfo.outputDirStr());
    ui->overWriteCheckBox->setCheckState(seriesInfo.overwriteFiles() ? Qt::Checked : Qt::Unchecked);

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
    dicomAttributesDialog->loadData(seriesInfo);

    if (dicomAttributesDialog->exec() == QDialog::Accepted)
    {
        // Save all of the data into our SeriesInfo object
        dicomAttributesDialog->storeData(seriesInfo);
    }
}

void MainWindow::handleSourceDirPushButtonClicked()
{
    QFileDialog dlg(this, "Source Directory", seriesInfo.inputDirStr());
    dlg.setAcceptMode(QFileDialog::AcceptOpen);
    dlg.setFileMode(QFileDialog::Directory);
    dlg.setOption(QFileDialog::ShowDirsOnly);
    dlg.setOption(QFileDialog::DontResolveSymlinks);
    dlg.setOption(QFileDialog::DontUseNativeDialog);

    if (dlg.exec())
    {
        seriesInfo.setInputDir(dlg.directory());
        ui->sourceDirLineEdit->setText(seriesInfo.inputDirStr());
    }
}

void MainWindow::handleDestDirPushButtonClicked()
{
    QFileDialog dlg(this, "Destination Directory", seriesInfo.outputDirStr());
    dlg.setAcceptMode(QFileDialog::AcceptOpen);
    dlg.setFileMode(QFileDialog::Directory);
    dlg.setOption(QFileDialog::ShowDirsOnly);
    dlg.setOption(QFileDialog::DontResolveSymlinks);
    dlg.setOption(QFileDialog::DontUseNativeDialog);

    if (dlg.exec())
    {
        seriesInfo.setOutputDir(dlg.directory());
        ui->destDirLineEdit->setText(seriesInfo.outputDirStr());
    }
}

void MainWindow::handleOverwriteFilesCheckBoxClicked(bool checked)
{
    seriesInfo.setOverwriteFiles(checked);
}

void MainWindow::handleConvertButtonClicked()
{
    //[self.convertButton setEnabled:NO];

    ErrorCode errCode = seriesConverter->makeOutputPathDir(seriesInfo.outputDirStr());

    // Cannot create the directory. Use the returned error to fill the alert.
    if (errCode == ErrorCode::ERROR_CREATING_DIRECTORY)
    {
        QString msg = "Could not create output path:" + seriesInfo.outputDirStr();
        QMessageBox::critical(this, "Error Creating Directory", msg);

        LOG4CPLUS_INFO(logger, msg.toStdString());

        return;
    }

    // Do this so that the user will be aware that he is about to overwrite a data set
    if ((errCode == ErrorCode::ERROR_DIRECTORY_NOT_EMPTY) && (!seriesInfo.overwriteFiles()))
    {
        QString msg = "Check the \'Overwrite files\' box to overwrite the"
                                 " contents of the output directory.";
        QMessageBox::critical(this, "Output directory is not empty.", msg);

        LOG4CPLUS_INFO(logger, msg.toStdString());

        return;
    }

    errCode = seriesConverter->convertFiles();

    if (errCode == ErrorCode::SUCCESS)
    {
        QString msg = "Converted files successfully.";
        QMessageBox::information(this, "", msg);

        LOG4CPLUS_INFO(logger, msg.toStdString());

        return;
    }
    else if (errCode == ErrorCode::ERROR_FILE_NOT_FOUND)
    {
        QString msg = "Could not read files in directory: " + seriesInfo.inputDirStr();
        QMessageBox::critical(this, "Error Reading Files", msg);

        LOG4CPLUS_INFO(logger, msg.toStdString());

        return;
    }
    else if (errCode == ErrorCode::ERROR_WRITING_FILE)
    {
        QString msg = "Could not write files to directory: " + seriesInfo.outputPath();
        QMessageBox::critical(this, "Error Writing Files", msg);

        LOG4CPLUS_INFO(logger, msg.toStdString());

        return;
    }
    else
    {
        QString msg = "Invalid ErrorCode value: " + QString::number(int(errCode));
        QMessageBox::critical(this, "", msg);

        LOG4CPLUS_ERROR(logger, msg.toStdString());

        return;
    }

}

void MainWindow::loadWidgetInfo()
{
    // get the current information
    SeriesInfo& info = SeriesInfo::getInstance();

    ui->sourceDirLineEdit->setText(info.inputDirStr());
    ui->destDirLineEdit->setText(info.outputDirStr());
    ui->overWriteCheckBox->setChecked(info.overwriteFiles());
}

void MainWindow::getWidgetInfo()
{
    // get the current information
    SeriesInfo& info = SeriesInfo::getInstance();

    info.setInputDir(ui->sourceDirLineEdit->text());
    info.setOutputDir(ui->destDirLineEdit->text());
    info.setOverwriteFiles(ui->overWriteCheckBox->isChecked());
}



