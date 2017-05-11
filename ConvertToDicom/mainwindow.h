#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

public slots:

    void execDicomAttributesDialog();

private:
    Ui::MainWindow *ui;

    DicomAttributesDialog* dicomAttributesDialog;
};

#endif // MAINWINDOW_H
