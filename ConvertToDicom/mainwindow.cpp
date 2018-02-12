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

    // Gave the main window's previous size and position
    Settings settings;
    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(600, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();

    // Connect our signals and slots
    connect(ui->editDicomAttributesPushButton, SIGNAL(clicked()), this,
            SLOT(handleEditDicomAttributesButtonClicked()));
    connect(ui->sourceDirChoosePushButton, SIGNAL(clicked()), this,
            SLOT(handleSourceDirPushButtonClicked()));
    connect(ui->destDirChooseBushButton, SIGNAL(clicked()), this, SLOT(handleDestDirPushButtonClicked()));
    connect(ui->overwriteFilesCheckBox, SIGNAL(clicked(bool)), this,
            SLOT(handleOverwriteFilesCheckBoxClicked(bool)));
    connect(ui->convertPushButton, SIGNAL(clicked()), this, SLOT(handleConvertButtonClicked()));
    connect(ui->closePushButton, SIGNAL(clicked()), this, SLOT(handleCloseButtonClicked()));
    connect(ui->sourceDirLineEdit, SIGNAL(textChanged(const QString&)), this,
            SLOT(handleSourceDirLineEditTextEdited()));
    connect(ui->sourceDirLineEdit, SIGNAL(editingFinished()), this,
            SLOT(handleSourceDirLineEditEditingFinished()));
    connect(ui->destDirLineEdit, SIGNAL(textChanged(const QString&)), this,
            SLOT(handleDestDirLineEditTextEdited()));
    connect(ui->destDirLineEdit, SIGNAL(editingFinished()), this,
            SLOT(handleDestDirLineEditEditingFinished()));

    // Some values to start with
    loadWidgetInfo();
    LOG4CPLUS_INFO(logger, "MainWindow opened.");
}

MainWindow::~MainWindow()
{
    // Save the main window's size and position
    Settings settings;
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();

    saveWidgetInfo();
    seriesInfo->saveSettings();

    delete ui;
    delete dicomAttributesDialog;
    LOG4CPLUS_DEBUG(logger, "MainWindow closed.");
}

void MainWindow::loadWidgetInfo()
{
    // get the current information
    ui->sourceDirLineEdit->setText(seriesInfo->inputDirStr());
    ui->destDirLineEdit->setText(seriesInfo->outputDirStr());
    ui->overwriteFilesCheckBox->setChecked(seriesInfo->overwriteFiles());
}

void MainWindow::saveWidgetInfo()
{
    // save the current information
    seriesInfo->setInputDir(ui->sourceDirLineEdit->text());
    seriesInfo->setOutputDir(ui->destDirLineEdit->text());
    seriesInfo->setOverwriteFiles(ui->overwriteFilesCheckBox->isChecked());
}

bool MainWindow::isValidSourceDirectory(const QString& dirPath)
{
    bool valid = seriesConverter->isValidSourceDir(dirPath);

    std::string valStr = valid ? "valid" : "invalid";
    LOG4CPLUS_DEBUG(logger, "Source directory " << dirPath.toStdString() << " " << valStr);

    return valid;
}

void MainWindow::updatePreview()
{

}

bool MainWindow::isValidDestDirectory(const QString& dirPath)
{
    QDir dir(dirPath);

    if (!dir.exists())
    {
        LOG4CPLUS_DEBUG(logger, "Destination directory " << dirPath.toStdString() << " does not exist.");
        return false;
    }

    if (dir.isEmpty())
    {
        LOG4CPLUS_DEBUG(logger, "Destination directory " << dirPath.toStdString() << " is empty.");
        return true;
    }
    else
    {
        LOG4CPLUS_DEBUG(logger, "Destination directory " << dirPath.toStdString() << " is not empty.");

        bool overwrite = seriesInfo->overwriteFiles();
        if (overwrite)
            LOG4CPLUS_DEBUG(logger, "  Overwriting contents of " << dirPath.toStdString());
        else
            LOG4CPLUS_DEBUG(logger, "  Cannot overwrite contents of " << dirPath.toStdString());
        return (overwrite);
    }
}

void MainWindow::handleEditDicomAttributesButtonClicked()
{
    if (dicomAttributesDialog == 0)
    {
        dicomAttributesDialog = new DicomAttributesDialog(this);
    }

#if defined(Q_OS_MACOS) || defined(Q_OS_IOS)
    dicomAttributesDialog->setWindowFlags(Qt::Sheet);
#endif

    seriesConverter->setInputDir(seriesInfo->inputDir());

    if (seriesConverter->extractImageParameters() != ErrorCode::SUCCESS)
    {
        QString msg = tr("Could not read image file(s) in input directory.");
        QMessageBox::critical(this, seriesInfo->inputDirStr() +
                              " does not contain readable image files.", msg);

        LOG4CPLUS_INFO(logger, (msg + seriesInfo->inputDirStr()).toStdString());

        return;
    }

    // Load up the dialog from the SeriesInfo object
    dicomAttributesDialog->loadData();

    if (dicomAttributesDialog->exec() == QDialog::Accepted)
    {
        // Save all of the data into our SeriesInfo object
        dicomAttributesDialog->storeData();
    }
}

void MainWindow::handleSourceDirPushButtonClicked()
{
    QFileDialog dlg(this, "Source Directory", seriesInfo->inputDirStr());
    dlg.setAcceptMode(QFileDialog::AcceptOpen);
    dlg.setFileMode(QFileDialog::Directory);
    dlg.setOption(QFileDialog::ShowDirsOnly);
    dlg.setOption(QFileDialog::DontResolveSymlinks);
    dlg.setOption(QFileDialog::DontUseNativeDialog);

    if (dlg.exec())
    {
        seriesInfo->setInputDir(dlg.directory());
        ui->sourceDirLineEdit->setText(seriesInfo->inputDirStr());
    }
}

void MainWindow::handleDestDirPushButtonClicked()
{
    QFileDialog dlg(this, "Destination Directory", seriesInfo->outputDirStr());
    dlg.setAcceptMode(QFileDialog::AcceptOpen);
    dlg.setFileMode(QFileDialog::Directory);
    dlg.setOption(QFileDialog::ShowDirsOnly);
    dlg.setOption(QFileDialog::DontResolveSymlinks);
    dlg.setOption(QFileDialog::DontUseNativeDialog);

    if (dlg.exec())
    {
        seriesInfo->setOutputDir(dlg.directory());
        ui->destDirLineEdit->setText(seriesInfo->outputDirStr());
    }
}

void MainWindow::handleOverwriteFilesCheckBoxClicked(bool checked)
{
    seriesInfo->setOverwriteFiles(checked);
}

void MainWindow::handleConvertButtonClicked()
{
    //[self.convertButton setEnabled:NO];

    ErrorCode errCode = seriesConverter->makeFullOutputPathDir(seriesInfo->outputDirStr());

    // Cannot create the directory. Use the returned error to fill the alert.
    if (errCode == ErrorCode::ERROR_CREATING_DIRECTORY)
    {
        QString msg = "Could not create output path:" + seriesInfo->outputDirStr();
        QMessageBox::critical(this, "Error Creating Directory", msg);

        LOG4CPLUS_INFO(logger, msg.toStdString());

        return;
    }

    // Do this so that the user will be aware that he is about to overwrite a data set
    if ((errCode == ErrorCode::ERROR_DIRECTORY_NOT_EMPTY) && (!seriesInfo->overwriteFiles()))
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
        QString msg = "Could not read files in directory: " + seriesInfo->inputDirStr();
        QMessageBox::critical(this, "Error Reading Files", msg);

        LOG4CPLUS_INFO(logger, msg.toStdString());

        return;
    }
    else if (errCode == ErrorCode::ERROR_WRITING_FILE)
    {
        QString msg = "Could not write files to directory: " + seriesInfo->outputPath();
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

void MainWindow::handleCloseButtonClicked()
{
    QApplication::closeAllWindows();
}

void MainWindow::handleSourceDirLineEditEditingFinished()
{
    QString dirPath = ui->sourceDirLineEdit->text();

    if (isValidSourceDirectory(dirPath))
    {
        seriesInfo->setInputDir(dirPath);
    }
}

void MainWindow::handleSourceDirLineEditTextEdited()
{
    QString dirPath = ui->sourceDirLineEdit->text();

    if (isValidSourceDirectory(dirPath))
    {
        seriesInfo->setInputDir(dirPath);
    }
}

void MainWindow::handleDestDirLineEditEditingFinished()
{
    QString dirPath = ui->destDirLineEdit->text();

    if (isValidDestDirectory(dirPath))
    {
        seriesInfo->setOutputDir(dirPath);
    }
}

void MainWindow::handleDestDirLineEditTextEdited()
{
    QString dirPath = ui->destDirLineEdit->text();

    if (isValidDestDirectory(dirPath))
    {
        seriesInfo->setOutputDir(dirPath);
    }
}

