//
//  SeriesInfo.cpp
//  ConvertToDicom
//

/* ConvertToDicom converts a series of images to DICOM format from any format recognized
 * by ITK (http://www.itk.org).
 * Copyright (C) 2017  Tim Allman
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "logger.h"
#include "seriesinfo.h"
#include "settings.h"
#include "dumpmetadatadictionary.h"
#include "dicomattributesdialog.h"

#include <QDir>

#include <string>
#include <iomanip>

#include <itkMetaDataObject.h>
#include <gdcmUIDGenerator.h>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

SeriesInfo::SeriesInfo()
    : logger(log4cplus::Logger::getInstance(std::string(LOGGER_NAME) + ".SeriesInfo")),
      locale(),
      m_imageSlicesPerImage(0),
      m_imageNumberOfImages(0),
      m_imageSliceSpacing(0.0),
      m_imageNumberOfSlices(0),
      m_imageOrientationPatient("1\\0\\0\\0\\1\\0")
{
     m_imagePositionPatient[0] = 0.0;
     m_imagePositionPatient[1] = 0.0;
     m_imagePositionPatient[2] = 0.0;

     loadSettings();
};

SeriesInfo::~SeriesInfo()
{
    saveSettings();
}

void SeriesInfo::loadSettings()
{
    LOG4CPLUS_TRACE(logger, "Enter");

    // Fill up with the saved settings
    // The defaults are set here as well.
    Settings settings; // uses preset program information

    // The image parameters are calculated based upon the image that is loaded
    // and so are neither saved nor read.
    setOverwriteFiles(settings.value(Settings::OverwriteFilesKey, 0).toBool());
    setInputDir(settings.value(Settings::InputDirKey, QDir::homePath()).toString());
    setOutputDir(settings.value(Settings::OutputDirKey, QDir::homePath()).toString());

    setPatientName(settings.value(Settings::PatientNameKey, "").toString());
    QString todayDateStr(QDate::currentDate().toString(DateFormat));
    QString dobStr = settings.value(Settings::PatientDOBKey, todayDateStr).toString();
    setPatientDOB(QDate::fromString(dobStr, DateFormat));
    setPatientID(settings.value(Settings::PatientIDKey, 0).toString());
    setPatientSex(settings.value(Settings::PatientSexKey, "Unspecified").toString());

    QString todayDateTimeStr(QDate::currentDate().toString(DateTimeFormat));
    QString studyDateTimeStr = settings.value(Settings::StudyDateTimeKey, todayDateTimeStr).toString();
    setStudyDateTime(QDateTime::fromString(studyDateTimeStr, DateTimeFormat));
    setStudyDescription(settings.value(Settings::StudyDescriptionKey, "").toString());
    setStudyID(settings.value(Settings::StudyIDKey, "0").toString());
    setStudyModality(settings.value(Settings::StudyModalityKey, "Unknown").toString());
    setStudyInstanceUID(settings.value(Settings::StudyInstanceUIDKey, "").toString());

    setSeriesTimeIncrement(settings.value(Settings::SeriesTimeIncrementKey, 1.0).toDouble());
    setSeriesDescription(settings.value(Settings::SeriesDescriptionKey, "").toString());
    setSeriesNumber(settings.value(Settings::SeriesNumberKey, 0).toInt());
    setSeriesPositionPatient(settings.value(Settings::SeriesPatientPositionKey, "FFS").toString());


    LOG4CPLUS_DEBUG(logger, "Loaded current settings and set default settings.");
}

void SeriesInfo::saveSettings()
{
    LOG4CPLUS_TRACE(logger, "Enter");

    Settings settings; // uses preset program information

    // The image parameters are calculated based upon the image that is loaded
    // and so are neither saved nor read.
    settings.setValue(Settings::OverwriteFilesKey, overwriteFiles());
    settings.setValue(Settings::InputDirKey, inputDir().path());
    settings.setValue(Settings::OutputDirKey, outputDir().path());
    settings.setValue(Settings::PatientNameKey, patientName());
    settings.setValue(Settings::PatientIDKey, patientID());
    settings.setValue(Settings::PatientDOBKey, patientDOB().toString(DateFormat));
    settings.setValue(Settings::PatientSexKey, patientSex());
    settings.setValue(Settings::SeriesDescriptionKey, seriesDescription());
    settings.setValue(Settings::SeriesNumberKey, seriesNumber());
    settings.setValue(Settings::SeriesPatientPositionKey, seriesPositionPatient());
    settings.setValue(Settings::SeriesTimeIncrementKey, seriesTimeIncrement());
    settings.setValue(Settings::StudyDescriptionKey, studyDescription());
    settings.setValue(Settings::StudyIDKey, studyID());
    settings.setValue(Settings::StudyModalityKey, studyModality());
    settings.setValue(Settings::StudyDateTimeKey, studyDateTime());
    settings.setValue(Settings::StudyInstanceUIDKey, studyInstanceUID());
    //    settings.setValue(Settings::ImageSliceSpacingKey, imageSliceSpacing());
    //    settings.setValue(Settings::ImagePatientPositionXKey, imagePositionPatientX());
    //    settings.setValue(Settings::ImagePatientPositionYKey, imagePositionPatientY());
    //    settings.setValue(Settings::ImagePatientPositionZKey, imagePositionPatientZ());
    //    settings.setValue(Settings::ImagePatientOrientationKey, imagePatientOrientation());

    settings.sync();

    LOG4CPLUS_DEBUG(logger, "Saved settings.");
}

itk::MetaDataDictionary SeriesInfo::makeMetaDataDictionary() const
{
    LOG4CPLUS_TRACE(logger, "Enter");

    // fill the dictionary from our Dicom
    if (dict.GetKeys().size() == 0)
    {
        std::string studyDate = m_studyDateTime.toString(DicomDateFormat).toStdString();
        std::string studyTime = m_studyDateTime.toString(DicomTimeFormat).toStdString();
        std::string dobDate = m_patientDOB.toString(DicomDateFormat).toStdString();

        itk::EncapsulateMetaData<std::string>(dict, "0010|0010", m_patientName.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0010|0020", m_patientID.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0010|0030", dobDate);
        itk::EncapsulateMetaData<std::string>(dict, "0010|0040", m_patientSex.toStdString());

        itk::EncapsulateMetaData<std::string>(dict, "0008|1030", m_studyDescription.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0020|0010", m_studyID.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0008|0060", m_studyModality.toStdString());

        itk::EncapsulateMetaData<std::string>(dict, "0008|0020", studyDate);
        itk::EncapsulateMetaData<std::string>(dict, "0008|0031", studyTime);
        itk::EncapsulateMetaData<std::string>(dict, "0020|000d", m_StudyInstanceUID.toStdString());

        gdcm::UIDGenerator suidGen;
        std::string seriesUID = suidGen.Generate();
        gdcm::UIDGenerator fuidGen;
        std::string frameOfReferenceUID = fuidGen.Generate();
        itk::EncapsulateMetaData<std::string>(dict, "0020|000e", seriesUID);
        itk::EncapsulateMetaData<std::string>(dict, "0020|0052", frameOfReferenceUID);
        itk::EncapsulateMetaData<std::string>(dict, "0020|0011", seriesNumberStr().toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0008|103e", m_seriesDescription.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0018|5100", m_seriesPositionPatient.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0008|0021", studyDate); // just use study date
        itk::EncapsulateMetaData<std::string>(dict, "0008|0030", studyTime); // just use study time

        QString spacing;
        spacing.setNum(m_imageSliceSpacing, 'f', 2);
        //itk::EncapsulateMetaData<std::string>(dict, "0018|0050", spacing.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0020|0037", m_imageOrientationPatient.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0020|0032", imagePositionPatientString().toStdString());
    }

    LOG4CPLUS_TRACE(logger, "Initial MetaDataDictionary:\n" << DumpDicomMetaDataDictionary(dict));

    return dict;
}

itk::MetaDataDictionary SeriesInfo::metaDataDictionary() const
{
    return dict;
}

QString SeriesInfo::imagePositionPatientString() const
{
    std::stringstream sstr;
    sstr << std::fixed << std::setprecision(2) << m_imagePositionPatient[0] << "\\"
    << m_imagePositionPatient[1] << "\\" << m_imagePositionPatient[2] << "\\";
    return QString::fromStdString(sstr.str());
}

QString SeriesInfo::imagePositionPatientString(int sliceIdx) const
{
    //LOG4CPLUS_TRACE(logger_, "Enter");

    vnl_matrix_fixed<double, 3, 3> rot;   // the rotation matrix
    vnl_vector_fixed<double, 3> ipp;      // the IPP (column) vector

    // Create the rotation matrix from IOP
    sscanf(m_imageOrientationPatient.toStdString().c_str(), "%lf\\%lf\\%lf\\%lf\\%lf\\%lf",
           &rot(0, 0), &rot(0, 1), &rot(0, 2), &rot(1, 0), &rot(1, 1), &rot(1, 2));

    // Compute the remaining orthogonal vector to complete the matrix
    rot(2,0) = rot(0, 1) * rot(1, 2) - rot(0, 2) * rot(1, 1);
    rot(2,1) = rot(0, 2) * rot(1, 0) - rot(0, 0) * rot(1, 2);
    rot(2,2) = rot(0, 0) * rot(1, 1) - rot(0, 1) * rot(1, 0);

    // IPP as a vector
    ipp[0] =  imagePositionPatientX();
    ipp[1] =  imagePositionPatientY();
    ipp[2] =  imagePositionPatientZ();

    LOG4CPLUS_DEBUG(logger, "Initial IPP = " << imagePositionPatientString().toStdString());

    ipp = rot * ipp;                            // rotate ipp into image coordinates
    ipp[2] += m_imageSliceSpacing * sliceIdx;    // increment Z component
    ipp = rot.inplace_transpose() * ipp;        // rotate back into patient coordinates

    char ippStr[30];
    sprintf(ippStr, "%.2f\\%.2f\\%.2f", ipp(0), ipp(1), ipp(2));
    LOG4CPLUS_DEBUG(logger, "Incremented IPP = " << ippStr);

    return ippStr;

    /* extracted from osirix, reflected in above code
     float vec[3];
     vec[0] = iop[1]*iop[5] - iop[2]*iop[4];
     vec[1] = iop[2]*iop[3] - iop[0]*iop[5];
     vec[2] = iop[0]*iop[4] - iop[1]*iop[3];
     */

}

