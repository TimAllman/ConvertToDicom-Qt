#-------------------------------------------------
#
# Project created by QtCreator 2017-04-30T13:02:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ConvertToDicom
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
        seriesinfo.cpp \
    loggerutils.cpp \
    settings.cpp \
    dumpmetadatadictionary.cpp \
    dicomattributesdialog.cpp

HEADERS  += mainwindow.h \
        seriesinfo.h \
    loggername.h \
    loggerutils.h \
    settings.h \
    dumpmetadatadictionary.h \
    typedefs.h \
    dicomattributesdialog.h

FORMS    += mainwindow.ui \
    dicomattributesdialog.ui

##QMAKE_LFLAGS += -F/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/

ITKLIBDIR = -L/Users/tim/usr/local/ITK-4.11/x86_64/Release/lib

ITKLIBS +=  -lITKBiasCorrection-4.11 \
            -lITKBioCell-4.11 \
            -lITKCommon-4.11 \
            -lITKDICOMParser-4.11 \
            -lITKEXPAT-4.11 \
            -lITKFEM-4.11 \
            -lITKIOBMP-4.11 \
            -lITKIOBioRad-4.11 \
            -lITKIOCSV-4.11 \
            -lITKIOGDCM-4.11 \
            -lITKIOGE-4.11 \
            -lITKIOGIPL-4.11 \
            -lITKIOHDF5-4.11 \
            -lITKIOIPL-4.11 \
            -lITKIOImageBase-4.11 \
            -lITKIOJPEG-4.11 \
            -lITKIOLSM-4.11 \
            -lITKIOMRC-4.11 \
            -lITKIOMesh-4.11 \
            -lITKIOMeta-4.11 \
            -lITKIONIFTI-4.11 \
            -lITKIONRRD-4.11 \
            -lITKIOPNG-4.11 \
            -lITKIOSiemens-4.11 \
            -lITKIOSpatialObjects-4.11 \
            -lITKIOStimulate-4.11 \
            -lITKIOTIFF-4.11 \
            -lITKIOTransformBase-4.11 \
            -lITKIOTransformHDF5-4.11 \
            -lITKIOTransformInsightLegacy-4.11 \
            -lITKIOTransformMatlab-4.11 \
            -lITKIOVTK-4.11 \
            -lITKIOXML-4.11 \
            -lITKKLMRegionGrowing-4.11 \
            -lITKLabelMap-4.11 \
            -lITKMesh-4.11 \
            -lITKMetaIO-4.11 \
            -lITKNrrdIO-4.11 \
            -lITKOptimizers-4.11 \
            -lITKOptimizersv4-4.11 \
            -lITKPath-4.11 \
            -lITKPolynomials-4.11 \
            -lITKQuadEdgeMesh-4.11 \
            -lITKSpatialObjects-4.11 \
            -lITKStatistics-4.11 \
            -lITKTransform-4.11 \
            -lITKTransformFactory-4.11 \
            -lITKVNLInstantiation-4.11 \
            -lITKVTK-4.11 \
            -lITKVideoCore-4.11 \
            -lITKVideoIO-4.11 \
            -lITKWatersheds-4.11 \
            -lITKgiftiio-4.11 \
            -lITKniftiio-4.11 \
            -lITKznz-4.11 \
            -lITKNetlibSlatec-4.11 \
            -lITKdouble-conversion-4.11 \
            -lITKgdcmCommon-4.11 \
            -lITKgdcmDICT-4.11 \
            -lITKgdcmDSED-4.11 \
            -lITKgdcmIOD-4.11 \
            -lITKgdcmMEXD-4.11 \
            -lITKgdcmMSFF-4.11 \
            -lITKgdcmcharls-4.11 \
            -lITKgdcmjpeg12-4.11 \
            -lITKgdcmjpeg16-4.11 \
            -lITKgdcmjpeg8-4.11 \
            -lITKgdcmopenjpeg-4.11 \
            -lITKgdcmsocketxx-4.11 \
            -lITKgdcmuuid-4.11 \
            -lITKhdf5 \
            -lITKhdf5_cpp \
            -lITKhdf5_cpp_debug \
            -lITKhdf5_debug \
            -lITKjpeg-4.11 \
            -lITKnetlib-4.11 \
            -lITKpng-4.11 \
            -lITKsys-4.11 \
            -lITKtestlib-4.11 \
            -lITKtiff-4.11 \
            -lITKv3p_netlib-4.11 \
            -lITKvcl-4.11 \
            -lITKvnl-4.11 \
            -lITKvnl_algo-4.11 \
            -lITKzlib-4.11

win32:CONFIG(release, debug|release): LIBS += $$ITKLIBDIR $$ITKLIBS
else:win32:CONFIG(debug, debug|release): LIBS += $$ITKLIBDIR $$ITKLIBS
else:unix:
{
    LIBS += $$ITKLIBDIR $$ITKLIBS

    # this is required because of linker errors with the ITK libs
    LIBS += -F/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/
    LIBS += -framework Foundation
}

INCLUDEPATH += $$PWD/../../../usr/local/include
INCLUDEPATH += /opt/local/include
INCLUDEPATH += $$PWD/../../../usr/local/ITK-4.11/x86_64/Release/include/ITK-4.11

DEPENDPATH += $$PWD/../../../usr/local/ITK-4.11/x86_64/Release/include/ITK-4.11

DISTFILES += \
    licence.txt

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/release/ -llog4cplusS
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/debug/ -llog4cplusS
else:unix: LIBS += -L$$PWD/../../../usr/local/lib/ -llog4cplusS

INCLUDEPATH += $$PWD/../../../usr/local/include
DEPENDPATH += $$PWD/../../../usr/local/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/release/liblog4cplusS.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/debug/liblog4cplusS.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/release/log4cplusS.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/debug/log4cplusS.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/liblog4cplusS.a
