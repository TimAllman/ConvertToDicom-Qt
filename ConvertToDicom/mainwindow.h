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

    void handleSourceDirPushButtonClicked();

    void handleDestDirPushButtonClicked();

    void handleOverwriteFilesCheckBoxClicked(bool checked);

    void handleConvertButtonClicked();

    void handleCloseButtonClicked();

private:
    Ui::MainWindow *ui;

    SeriesInfo* seriesInfo;

    DicomAttributesDialog* dicomAttributesDialog;

    SeriesConverter* seriesConverter;

    Logger logger;

};

#endif // MAINWINDOW_H
