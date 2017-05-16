#include "mainwindow.h"
#include "loggerutils.h"
#include "logger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SetupLogger(LOGGER_NAME, LogLevel::LOG_LEVEL_TRACE);

    MainWindow w;
    w.show();

    return a.exec();
}
