#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <log4cplus/logger.h>

class DicomAttributesDialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadSettings();
    void saveSettings();
public slots:

    void execDicomAttributesDialog();

private:
    Ui::MainWindow *ui;

    DicomAttributesDialog* dicomAttributesDialog;
    log4cplus::Logger logger;

};

#endif // MAINWINDOW_H
