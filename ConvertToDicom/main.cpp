#include "mainwindow.h"
#include "logger.h"
#include "logger.h"
#include "itkheaders.pch.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Tim Allman");
    QCoreApplication::setOrganizationDomain("brasscats.ca");
    QCoreApplication::setApplicationName("ConvertToDicom-Qt");

    SetupLogger(LOGGER_NAME, LogLevel::LOG_LEVEL_ALL, LogLevel::LOG_LEVEL_ALL);

    // Possible valuse are "Windows", "Fusion", Macintosh"
    //    a.setStyle(QStyleFactory::create("Windows"));
    //    a.setStyle(QStyleFactory::create("Fusion"));
    //    a.setStyle(QStyleFactory::create("Macintosh"));

    // Register all of the image I/O factories.
    itk::BMPImageIOFactory::RegisterOneFactory();
    itk::BYUMeshIOFactory::RegisterOneFactory();
    itk::BioRadImageIOFactory::RegisterOneFactory();
    itk::FileListVideoIOFactory::RegisterOneFactory();
    itk::FreeSurferAsciiMeshIOFactory::RegisterOneFactory();
    itk::FreeSurferBinaryMeshIOFactory::RegisterOneFactory();
    itk::GDCMImageIOFactory::RegisterOneFactory();
    itk::GE4ImageIOFactory::RegisterOneFactory();
    itk::GE5ImageIOFactory::RegisterOneFactory();
    itk::GEAdwImageIOFactory::RegisterOneFactory();
    itk::GiftiMeshIOFactory::RegisterOneFactory();
    itk::GiplImageIOFactory::RegisterOneFactory();
    itk::HDF5ImageIOFactory::RegisterOneFactory();
    itk::HDF5TransformIOFactory::RegisterOneFactory();
    itk::JPEGImageIOFactory::RegisterOneFactory();
    itk::LSMImageIOFactory::RegisterOneFactory();
    itk::MRCImageIOFactory::RegisterOneFactory();
    itk::MatlabTransformIOFactory::RegisterOneFactory();
    itk::MetaImageIOFactory::RegisterOneFactory();
    itk::NiftiImageIOFactory::RegisterOneFactory();
    itk::NrrdImageIOFactory::RegisterOneFactory();
    itk::OBJMeshIOFactory::RegisterOneFactory();
    itk::OFFMeshIOFactory::RegisterOneFactory();
    itk::PNGImageIOFactory::RegisterOneFactory();
    itk::SiemensVisionImageIOFactory::RegisterOneFactory();
    itk::StimulateImageIOFactory::RegisterOneFactory();
    itk::TIFFImageIOFactory::RegisterOneFactory();
    itk::TxtTransformIOFactory::RegisterOneFactory();
    itk::VTKImageIOFactory::RegisterOneFactory();
    itk::VTKPolyDataMeshIOFactory::RegisterOneFactory();

    MainWindow w;
    w.show();

    return a.exec();
}
