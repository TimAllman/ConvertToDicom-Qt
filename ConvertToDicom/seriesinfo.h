#ifndef SERIESINFO_H
#define SERIESINFO_H

//
//  SeriesInfo.h
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

#include "itkheaders.pch.h"

#include <QDir>
#include <QString>
#include <QList>
#include <QDateTime>
#include <QLocale>

/**
 * @brief The SeriesInfo class
 * This class contains all of the DICOM and other information needed to do the conversions.
 * It is set up as a singleton class because only one should ever be created and it allows
 * the instance to be accessed globally.
 */
class SeriesInfo
{
    const Qt::DateFormat TimeFormat = Qt::ISODateWithMs;      //< Format used in program for times
    const Qt::DateFormat DateFormat = Qt::ISODate;            //< Format used in program for dates
    const Qt::DateFormat DateTimeFormat = Qt::ISODateWithMs;  //< Format used in program for datetimes

    const char* DicomTimeFormat = "HHmmss.zzz";               //< Format used to format DICOM times
    const char* DicomDateFormat = "YYYYMMdd";                 //< Format used to format DICOM dates

public:
    /**
     * @brief overwriteFiles
     * Get flag which indicates whether generated files will overwrite existing files.
     * @return true if generated files will overwrite existing files, false otherwise.
     */
    bool overwriteFiles() const
    {
        return m_overwriteFiles;
    }

    /**
     * @brief inputDir
     * Get the directory containing the files to be converted.
     * @return The current input directory.
     */
    QDir inputDir() const
    {
        return m_inputDir;
    }

    /**
     * @brief inputDirStr
     * @return The input directory as an absolute path string.
     * @sa inputDir()
     */
    QString inputDirStr() const
    {
        return m_inputDir.absolutePath();
    }

    /**
     * @brief outputDir
     * This is a base subdirectory for the output of this program.
     * @see outputPath().
     * @return The current output directory.
     */
    QDir outputDir() const
    {
        return m_outputDir;
    }

    /**
     * @brief outputDirStr
     * @return The output directory as an absolute path string.
     * @see outputDir()
     */
    QString outputDirStr() const
    {
        return m_outputDir.absolutePath();
    }

    /**
     * @brief outputPath
     * The full output path is a chain of subdirectories of
     * based upon outputDirStr(), patient's name, study description, study ID,
     * series description and series number.
     * @return The full absolute output path directory as a string.
     */
    QString outputPath() const
    {
        return m_outputPath;
    }

    QString patientName() const
    {
        return m_patientName;
    }

    QString patientID() const
    {
        return m_patientID;
    }

    QDate patientDOB() const
    {
        return m_patientDOB;
    }

    QString patientDOBStr() const
    {
        return m_patientDOB.toString(DateFormat);
    }

    QString patientSex() const
    {
        return m_patientSex;
    }

    QString studyDescription() const
    {
        return m_studyDescription;
    }

    QString studyID() const
    {
        return m_studyID;
    }

    QString studyModality() const
    {
        return m_studyModality;
    }

    QDateTime studyDateTime() const
    {
        return m_studyDateTime;
    }

    QString studyDateTimeStr() const
    {
        return m_studyDateTime.toString(DateTimeFormat);
    }

    QString studyInstanceUID() const
    {
        return m_StudyInstanceUID;
    }

    int seriesNumber() const
    {
        return m_seriesNumber;
    }

    QString seriesNumberStr() const
    {
        return locale.toString(m_seriesNumber);
    }

    QString seriesDescription() const
    {
        return m_seriesDescription;
    }

    QString seriesPositionPatient() const
    {
        return m_seriesPositionPatient;
    }

    /**
     * @brief seriesTimeIncrement
     * @return The time increment in ms.
     */
    double seriesTimeIncrement() const
    {
        return m_seriesTimeIncrement;
    }

    QString seriesTimeIncrementStr() const
    {
        return locale.toString(m_seriesTimeIncrement, 'f', 3);
    }

    QList<QTime>& acqTimes()
    {
        return m_acqTimes;
    }

    int imageNumberOfImages() const
    {
        return m_imageNumberOfImages;
    }

    QString imageNumberOfImagesStr() const
    {
        return locale.toString(m_imageNumberOfImages);
    }

    int imageSlicesPerImage() const
    {
        return m_imageSlicesPerImage;
    }

    QString imageSlicesPerImageStr() const
    {
        return locale.toString(m_imageSlicesPerImage);
    }

    int imageNumberOfSlices() const
    {
        return m_imageNumberOfSlices;
    }

    QString imageNumberOfSlicesStr() const
    {
        return locale.toString(m_imageNumberOfSlices);
    }

    double imageSliceSpacing() const
    {
        return m_imageSliceSpacing;
    }

    QString imageSliceSpacingStr() const
    {
        return locale.toString(m_imageSliceSpacing, 'f', 3);
    }

    double imagePositionPatientX() const
    {
        return m_imagePositionPatient[0];
    }

    QString imagePositionPatientXStr() const
    {
        return locale.toString(m_imagePositionPatient[0], 'f', 3);
    }

    double imagePositionPatientY() const
    {
        return m_imagePositionPatient[1];
    }

    QString imagePositionPatientYStr() const
    {
        return locale.toString(m_imagePositionPatient[1], 'f', 3);
    }

    double imagePositionPatientZ() const
    {
        return m_imagePositionPatient[2];
    }

    QString imagePositionPatientZStr() const
    {
        return locale.toString(m_imagePositionPatient[2], 'f', 3);
    }

    QString imagePatientOrientation() const
    {
        return m_imageOrientationPatient;
    }

    /**
     * @brief setOverwriteFiles
     * Set flag which indicates whether generated files will overwrite existing files.
     * @param overwriteFiles Set flag to this value.
     */
    void setOverwriteFiles(bool overwriteFiles)
    {
        m_overwriteFiles = overwriteFiles;
    }

    /**
     * @brief setInputDir
     * Set the input directory path
     * @param inputDir The directory containing the files to be converted.
     */
    void setInputDir(const QDir& inputDir)
    {
        m_inputDir = inputDir;
    }

    void setOutputDir(const QDir& outputDir)
    {
        m_outputDir = outputDir;
    }

    void setOutputPath(const QString& outputPath)
    {
        m_outputPath = outputPath;
    }

    void setImageNumberOfImages(int numberOfImages)
    {
        m_imageNumberOfImages = numberOfImages;
    }

    void setImageSlicesPerImage(int slicesPerImage)
    {
        m_imageSlicesPerImage = slicesPerImage;
    }

    void setSeriesNumberOfSlices(int numberOfSlices)
    {
        m_imageNumberOfSlices = numberOfSlices;
    }

    void setPatientName(const QString& patientName)
    {
        m_patientName = patientName;
    }

    void setPatientID(const QString& patientID)
    {
        m_patientID = patientID;
    }

    void setPatientDOB(const QDate& patientDOB)
    {
        m_patientDOB = patientDOB;
    }

    void setPatientSex(const QString& patientSex)
    {
        m_patientSex = patientSex;
    }

    void setStudyDescription(const QString& studyDescription)
    {
        m_studyDescription = studyDescription;
    }

    void setStudyID(const QString& studyID)
    {
        m_studyID = studyID;
    }

    void setStudyModality(const QString& studyModality)
    {
        m_studyModality = studyModality;
    }

    void setStudyDateTime(const QDateTime& studyDateTime)
    {
        m_studyDateTime = studyDateTime;
    }

    void setStudyInstanceUID(const QString& studyInstanceUID)
    {
        m_StudyInstanceUID = studyInstanceUID;
    }

    void setSeriesNumber(const QString& seriesNumber)
    {
        m_seriesNumber = locale.toInt(seriesNumber);
    }

    void setSeriesNumber(int seriesNumber)
    {
        m_seriesNumber = seriesNumber;
    }

    void setSeriesDescription(const QString& seriesDescription)
    {
        m_seriesDescription = seriesDescription;
    }

    void setSeriesPositionPatient(const QString& seriesPositionPatient)
    {
        m_seriesPositionPatient = seriesPositionPatient;
    }

    /**
     * @brief setSeriesTimeIncrement
     * @param timeIncrement The time increment in seconds.
     */
    void setSeriesTimeIncrement(double timeIncrement)
    {
        m_seriesTimeIncrement = timeIncrement;
    }

    void setImageSliceSpacing(double imageSliceSpacing)
    {
        m_imageSliceSpacing = imageSliceSpacing;
    }

    void setImagePositionPatientX(double imagePositionPatientX)
    {
        m_imagePositionPatient[0] = imagePositionPatientX;
    }

    void setImagePositionPatientY(double imagePositionPatientY)
    {
        m_imagePositionPatient[1] = imagePositionPatientY;
    }

    void setImagePositionPatientZ(double imagePositionPatientZ)
    {
        m_imagePositionPatient[2] = imagePositionPatientZ;
    }

    void setImagePatientOrientation(const QString& imageOrientationPatient)
    {
        m_imageOrientationPatient = imageOrientationPatient;
    }

    /**
     * @brief loadSettings
     * Fills a data structure using the saved settings.
     */
    void loadSettings();

    /**
     * @brief saveSettings
     * Saves the contents of info to persistent storage.
     */
    void saveSettings();

private:
    /**
     * @brief logger
     * log4cplus logger for this class.
     */
    Logger m_logger;

    QLocale locale;

    bool m_overwriteFiles;
    QDir m_inputDir;
    QDir m_outputDir;
    QString m_outputPath;

    QList<QTime> m_acqTimes;

    QString m_patientName;
    QString m_patientID;
    QDate m_patientDOB;
    QString m_patientSex;

    QString m_studyDescription;
    QString m_studyID;
    QString m_studyModality;
    QDateTime m_studyDateTime;
    QString m_StudyInstanceUID;

    int m_seriesNumber;
    QString m_seriesDescription;
    QString m_seriesPositionPatient;
    double m_seriesTimeIncrement;

    int m_imageSlicesPerImage;
    int m_imageNumberOfImages;
    double m_imageSliceSpacing;
    int m_imageNumberOfSlices;
    vnl_vector_fixed<double, 3> m_imagePositionPatient;
    QString m_imageOrientationPatient;

    mutable itk::MetaDataDictionary dict;

public:
    /**
     * Get the global instance of this class.
     * @return Pointer to single instance of this class.
     */
    static SeriesInfo* getInstance()
    {
        static SeriesInfo instance;
        return &instance;
    }

    /**
     * Get a tempory instance of this class. The new instance is a copy of the global
     * instance.
     * @return Pointer to a temporary instance of this class. It must be <code>delete</code>d
     * when no longer needed.
     */
    static SeriesInfo* getTempInstance()
    {
        SeriesInfo *instance = getInstance();
        SeriesInfo *tempInstance = new SeriesInfo;

        *tempInstance = *instance;
        return tempInstance;
    }

    /**
     * Check for internal completeness and conistency.
     * Used for debugging.
     * return YES if conistent, NO otherwise.
     */
    bool isConistent();

    /**
     * Get the parameters as a DICOM dictionary.
     * @return The dictionary.
     */
    itk::MetaDataDictionary metaDataDictionary() const;

    /**
     * @brief imagePositionPatientString
     * @return The ImagePositionPatient as a DICOM compatible string.
     */
    QString imagePositionPatientString() const;

    /**
     * @brief imagePositionPatientString
     * @param sliceIdx The slice whose position we want.
     * @return The ImagePositionPatient for this slice as a DICOM compatible string.
     */
    QString imagePositionPatientString(int sliceIdx) const;

private:
    /**
     * Default constructor. Sets initial values of members.
     */
    SeriesInfo();

    /**
     * @brief SeriesInfo
     * Copy constructor private and unimplemented.
     */
    SeriesInfo(const SeriesInfo&);

    /**
     * Destructor
     */
    ~SeriesInfo();

    /**
     * @brief SeriesInfo
     * Assignment operator private and unimplemented.
     */
    SeriesInfo& operator=(const SeriesInfo&);

    itk::MetaDataDictionary makeMetaDataDictionary() const;
};

#endif // SERIESINFO_H
