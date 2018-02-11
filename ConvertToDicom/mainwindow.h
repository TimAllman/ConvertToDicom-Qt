#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "logger.h"
#include "seriesinfo.h"

class DicomAttributesDialog;
class SeriesConverter;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /**
     * @brief loadSettings
     * Load application wide settings.
     */
    void loadWidgetInfo();

    /**
     * @brief saveSettings
     * Save application wide settings.
     */
    void saveWidgetInfo();

public slots:
    /**
     * @brief execDicomAttributesDialog
     * Show the DICOM attributes dialog
     */
    void handleEditDicomAttributesButtonClicked();

    /**
     * @brief handleSourceDirPushButtonClicked
     * The source directory chooser button was clicked. This shows a QFileDialog.
     */
    void handleSourceDirPushButtonClicked();

    /**
     * @brief handleDestinationDirPushButtonClicked
     * The destination directory chooser button was clicked. This shows a QFileDialog.
     */
    void handleDestDirPushButtonClicked();

    /**
     * @brief handleOverwriteFilesCheckBoxClicked
     * User selects whether ConvertToDicom will write into an existing directory containing files.
     * @param checked Write files into an existing directory containing files if true. Refuse otherwise.
     */
    void handleOverwriteFilesCheckBoxClicked(bool checked);

    /**
     * @brief handleConvertButtonClicked
     * Start the conversion process.
     */
    void handleConvertButtonClicked();

    /**
     * @brief handleCloseButtonClicked
     *
     */
    void handleCloseButtonClicked();

    /**
     * The user has finished editing the source directory name.
     */
    void handleSourceDirLineEditEditingFinished();

    /**
     * The user has made an edit to the source directory name.
     */
    void handleSourceDirLineEditTextEdited();

    /**
     * The user has finished editing the destination directory name.
     */
    void handleDestDirLineEditEditingFinished();

    /**
     * The user has made an edit to the destination directory name.
     */
    void handleDestDirLineEditTextEdited();

    /**
     * Determines whether the source directory string describes a directory containing readable image files.
     * @param dirName The directory to be tested.
     * @return true if valid, false if not.
     */
    bool isValidSourceDirectory(const QString& dirName);

    /**
     * Determines whether the destination directory string describes a suitable output directory.
     * The directory must exist (or be creatable) and be writeable. If the directory is not empty and
     * seriesInfo->overwriteFiles() is false we will refuse to write to the directory. Otherwise
     * the files will be written, overwriting any that are in he way.
     * @param dirName The directory to be tested.
     * @return true if valid, false if not.
     */
    bool isValidDestDirectory(const QString& dirName);


private:
    Ui::MainWindow *ui;

    SeriesInfo* seriesInfo;

    DicomAttributesDialog* dicomAttributesDialog;

    SeriesConverter* seriesConverter;

    Logger logger;

};

#endif // MAINWINDOW_H
