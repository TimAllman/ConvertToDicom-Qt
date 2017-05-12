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

#include "loggername.h"
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
      m_overwriteFiles(false), m_numberOfImages(0), m_slicesPerImage(0), m_numberOfSlices(0),
      m_timeIncrement(0.0f), m_imageSliceSpacing(0.0),
      m_imageOrientationPatient("1\\0\\0\\0\\1\\0")
{
     m_imagePositionPatient[0] = 0.0;
     m_imagePositionPatient[1] = 0.0;
     m_imagePositionPatient[2] = 0.0;


};

void SeriesInfo::loadSettings()
{
    LOG4CPLUS_TRACE(logger, "Enter");

    // Fill up with the saved settings
    // The defaults are set here as well.
    Settings settings; // uses preset program information

    setOverwriteFiles(settings.value(Settings::OverwriteFilesKey, false).toBool());
    setInputDir(settings.value(Settings::InputDirKey, QDir::homePath()).toString());
    setOutputDir(settings.value(Settings::OutputDirKey, QDir::homePath()).toString());
    setTimeIncrement(settings.value(Settings::TimeIncrementKey, 1.0).toFloat());
    setPatientsName(settings.value(Settings::PatientsNameKey, "").toString());
    setPatientsID(settings.value(Settings::PatientsIDKey, 0).toString());
    setPatientsDOB(settings.value(Settings::PatientsDOBKey, QDateTime::currentDateTime()).toString());
    setPatientsSex(settings.value(Settings::PatientsSexKey, "Unspecified").toString());
    setSeriesDescription(settings.value(Settings::SeriesDescriptionKey, "").toString());
    setSeriesNumber(settings.value(Settings::SeriesNumberKey, "0").toString());
    setSeriesPositionPatient(settings.value(Settings::SeriesPatientPositionKey, "FFS").toString());
    setStudyDescription(settings.value(Settings::StudyDescriptionKey, "").toString());
    setStudyID(settings.value(Settings::StudyIDKey, "0").toString());
    setStudyModality(settings.value(Settings::StudyModalityKey, "Unknown").toString());
    setStudyDateTime(settings.value(Settings::StudyDateTimeKey, QDateTime::currentDateTime()).toString());
    setStudyStudyUID(settings.value(Settings::StudyStudyUIDKey, "").toString());


    ******************************************
    check types in settings get and set.

    setImageSliceSpacing(settings.value(Settings::ImageSliceSpacingKey, ))

    LOG4CPLUS_DEBUG(logger, "Loaded current settings and set default settings.");
}

void SeriesInfo::saveSettings()
{
    LOG4CPLUS_TRACE(logger, "Enter");

    Settings settings; // uses preset program information

    settings.setValue(Settings::OverwriteFilesKey, overwriteFiles());
    settings.setValue(Settings::InputDirKey, inputDir());
    settings.setValue(Settings::OutputDirKey, outputDir());
    settings.setValue(Settings::TimeIncrementKey, timeIncrement());
    settings.setValue(Settings::PatientsNameKey, patientsName());
    settings.setValue(Settings::PatientsIDKey, patientsID());
    settings.setValue(Settings::PatientsDOBKey, patientsDOB());
    settings.setValue(Settings::PatientsSexKey, patientsSex());
    settings.setValue(Settings::SeriesDescriptionKey, seriesDescription());
    settings.setValue(Settings::SeriesNumberKey, seriesNumber());
    settings.setValue(Settings::SeriesPatientPositionKey, seriesPositionPatient());
    settings.setValue(Settings::StudyDescriptionKey, studyDescription());
    settings.setValue(Settings::StudyIDKey, studyID());
    settings.setValue(Settings::StudyModalityKey, studyModality());
    settings.setValue(Settings::StudyDateTimeKey, studyDateTime());
    settings.setValue(Settings::StudyStudyUIDKey, studyStudyUID());
    settings.setValue(Settings::ImageSliceSpacingKey, imageSliceSpacing());
    settings.setValue(Settings::ImagePatientPositionXKey, imagePositionPatientX());
    settings.setValue(Settings::ImagePatientPositionYKey, imagePositionPatientY());
    settings.setValue(Settings::ImagePatientPositionZKey, imagePositionPatientZ());
    settings.setValue(Settings::ImagePatientOrientationKey, imagePatientOrientation());

    LOG4CPLUS_DEBUG(logger, "Saved settings.");
}

itk::MetaDataDictionary SeriesInfo::makeDictionary() const
{
    LOG4CPLUS_TRACE(logger, "Enter");

    // fill the dictionary from our Dicom
    if (dict.GetKeys().size() == 0)
    {
        std::string date = m_studyDateTime.toString().toStdString();
        std::string time = m_studyDateTime.toString("HHmmss").toStdString();

        itk::EncapsulateMetaData<std::string>(dict, "0010|0010", m_patientsName.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0010|0020", m_patientsID.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0010|0030", m_patientsDOB.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0010|0040", m_patientsSex.toStdString());

        itk::EncapsulateMetaData<std::string>(dict, "0008|1030", m_studyDescription.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0020|0010", m_studyID.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0008|0060", m_studyModality.toStdString());

        itk::EncapsulateMetaData<std::string>(dict, "0008|0020", date);
        itk::EncapsulateMetaData<std::string>(dict, "0008|0031", time);
        itk::EncapsulateMetaData<std::string>(dict, "0020|000d", m_StudyUID.toStdString());

        gdcm::UIDGenerator suidGen;
        std::string seriesUID = suidGen.Generate();
        gdcm::UIDGenerator fuidGen;
        std::string frameOfReferenceUID = fuidGen.Generate();
        itk::EncapsulateMetaData<std::string>(dict, "0020|000e", seriesUID);
        itk::EncapsulateMetaData<std::string>(dict, "0020|0052", frameOfReferenceUID);
        itk::EncapsulateMetaData<std::string>(dict, "0020|0011", m_seriesNumber.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0008|103e", m_seriesDescription.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0018|5100", m_seriesPositionPatient.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0008|0021", date); // just use study date
        itk::EncapsulateMetaData<std::string>(dict, "0008|0030", time); // just use study time

        QString spacing;
        spacing.setNum(m_imageSliceSpacing, 'f', 2);
        //itk::EncapsulateMetaData<std::string>(dict, "0018|0050", spacing.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0020|0037", m_imageOrientationPatient.toStdString());
        itk::EncapsulateMetaData<std::string>(dict, "0020|0032", imagePositionPatientString().toStdString());
    }

    LOG4CPLUS_TRACE(logger, "Initial MetaDataDictionary:\n" << DumpDicomMetaDataDictionary(dict));

    return dict;
}

itk::MetaDataDictionary SeriesInfo::dictionary() const
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

QString SeriesInfo::imagePositionPatientString(unsigned int sliceIdx) const
{
    //LOG4CPLUS_TRACE(logger_, "Enter");

    vnl_matrix_fixed<float, 3, 3> rot;   // the rotation matrix
    vnl_vector_fixed<float, 3> ipp;      // the IPP (column) vector

    // Create the rotation matrix from IOP
    sscanf(m_imageOrientationPatient.toStdString().c_str(), "%f\\%f\\%f\\%f\\%f\\%f",
           &rot(0, 0), &rot(0, 1), &rot(0, 2), &rot(1, 0), &rot(1, 1), &rot(1, 2));

    // Compute the remaining orthogonal vector to complete the matrix
    rot(2,0) = rot(0, 1) * rot(1, 2) - rot(0, 2) * rot(1, 1);
    rot(2,1) = rot(0, 2) * rot(1, 0) - rot(0, 0) * rot(1, 2);
    rot(2,2) = rot(0, 0) * rot(1, 1) - rot(0, 1) * rot(1, 0);

    // IPP as a vector
    ipp = m_imagePositionPatient;

    //LOG4CPLUS_DEBUG(logger_, "Initial IPP = " << imagePositionPatientString());

    ipp = rot * ipp;                            // rotate ipp into image coordinates
    ipp[2] += m_imageSliceSpacing * sliceIdx;    // increment Z component
    ipp = rot.inplace_transpose() * ipp;        // rotate back into patient coordinates

    char  ippStr[30];
    sprintf(ippStr, "%.2f\\%.2f\\%.2f", double(ipp(0)), double(ipp(1)), double(ipp(2)));
    LOG4CPLUS_DEBUG(logger, "Incremented IPP = " << ippStr);

    return ippStr;

    /* extracted from osirix, reflected in above code
     float vec[3];
     vec[0] = iop[1]*iop[5] - iop[2]*iop[4];
     vec[1] = iop[2]*iop[3] - iop[0]*iop[5];
     vec[2] = iop[0]*iop[4] - iop[1]*iop[3];
     */

}

