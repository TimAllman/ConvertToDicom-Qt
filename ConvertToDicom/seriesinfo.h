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
#include <log4cplus/loggingmacros.h>

#include <itkMetaDataDictionary.h>
#include <vnl/vnl_vector_fixed.h>

#include <QObject>
#include <QString>
#include <QVector>
#include <QDateTime>

/**
 * @brief The SeriesInfo class
 * This class contains all of the DICOM and other information needed to do the conversions.
 * It is set up as a singleton class because only one should ever be created and it allows
 * the instance to be accessed globally.
 */
class SeriesInfo : public QObject
{
    Q_OBJECT

    /**
     * @brief logger
     * log4cplus logger for this class.
     */
    log4cplus::Logger logger;

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
    QString inputDir() const
    {
        return m_inputDir;
    }

    QString outputDir() const
    {
        return m_outputDir;
    }

    QString outputPath() const
    {
        return m_outputPath;
    }

    int numberOfImages() const
    {
        return m_numberOfImages;
    }

    int slicesPerImage() const
    {
        return m_slicesPerImage;
    }

    int numberOfSlices() const
    {
        return m_numberOfSlices;
    }

    float timeIncrement() const
    {
        return m_timeIncrement;
    }

    QVector<float>& acqTimes()
    {
        return m_acqTimes;
    }

    QString patientsName() const
    {
        return m_patientsName;
    }

    QString patientsID() const
    {
        return m_patientsID;
    }

    QString patientsDOB() const
    {
        return m_patientsDOB;
    }

    QString patientsSex() const
    {
        return m_patientsSex;
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

    QString studyStudyUID() const
    {
        return m_StudyUID;
    }

    QString seriesNumber() const
    {
        return m_seriesNumber;
    }

    QString seriesDescription() const
    {
        return m_seriesDescription;
    }

    QString seriesPositionPatient() const
    {
        return m_seriesPositionPatient;
    }

    float imageSliceSpacing() const
    {
        return m_imageSliceSpacing;
    }

    float imagePositionPatientX() const
    {
        return m_imagePositionPatient[0];
    }

   float imagePositionPatientY() const
    {
        return m_imagePositionPatient[1];
    }

    float imagePositionPatientZ() const
    {
        return m_imagePositionPatient[2];
    }

    QString imagePatientOrientation() const
    {
        return m_imageOrientationPatient;
    }

public slots:
    /**
     * @brief setOverwriteFiles
     * Set flag which indicates whether generated files will overwrite existing files.
     * @param overwriteFiles Set flag to this value.
     */
    void setOverwriteFiles(bool overwriteFiles)
    {
        if (m_overwriteFiles != overwriteFiles)
        {
            m_overwriteFiles = overwriteFiles;
            emit overwriteFilesValueChanged(overwriteFiles);
        }
    }

    /**
     * @brief setInputDir
     * Set the input directory path
     * @param inputDir The directory containing the files to be converted.
     */
    void setInputDir(const QString& inputDir)
    {
        m_inputDir = inputDir;
    }

    void setOutputDir(const QString& outputDir)
    {
        m_outputDir = outputDir;
    }

    void setOutputPath(const QString& outputPath)
    {
        m_outputPath = outputPath;
    }

    void setNumberOfImages(int numberOfImages)
    {
        m_numberOfImages = numberOfImages;
    }

    void setSlicesPerImage(int slicesPerImage)
    {
        m_slicesPerImage = slicesPerImage;
    }

    void setNumberOfSlices(int numberOfSlices)
    {
        m_numberOfSlices = numberOfSlices;
    }

    void setTimeIncrement(float timeIncrement)
    {
        m_timeIncrement = timeIncrement;
    }

    void setPatientsName(const QString& patientsName)
    {
        m_patientsName = patientsName;
    }

    void setPatientsID(const QString& patientsID)
    {
        m_patientsID = patientsID;
    }

    void setPatientsDOB(const QString& patientsDOB)
    {
        m_patientsDOB = patientsDOB;
    }

    void setPatientsSex(const QString& patientsSex)
    {
        m_patientsSex = patientsSex;
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

    void setStudyDateTime(const QString& studyDateTime)
    {
        m_studyDateTime = QDateTime::fromString(studyDateTime);
    }

    void setStudyStudyUID(const QString& studyStudyUID)
    {
        m_StudyUID = studyStudyUID;
    }

    void setSeriesNumber(const QString& seriesNumber)
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

    void setImageSliceSpacing(float imageSliceSpacing)
    {
        m_imageSliceSpacing = imageSliceSpacing;
    }

    void setImagePositionPatientX(float imagePositionPatientX)
    {
        m_imagePositionPatient[0] = imagePositionPatientX;
    }

    void setImagePositionPatientY(float imagePositionPatientY)
    {
        m_imagePositionPatient[1] = imagePositionPatientY;
    }

    void setImagePositionPatientZ(float imagePositionPatientZ)
    {
        m_imagePositionPatient[2] = imagePositionPatientZ;
    }

    void setImagePatientOrientation(const QString& imageOrientationPatient)
    {
        m_imageOrientationPatient = imageOrientationPatient;
    }

    void loadSettings();

    void saveSettings();

private:
    bool m_overwriteFiles;
    QString m_inputDir;
    QString m_outputDir;
    QString m_outputPath;

    int m_numberOfImages;
    int m_slicesPerImage;
    int m_numberOfSlices;
    float m_timeIncrement;
    QVector<float> m_acqTimes;

    QString m_patientsName;
    QString m_patientsID;
    QString m_patientsDOB;
    QString m_patientsSex;

    QString m_studyDescription;
    QString m_studyID;
    QString m_studyModality;
    QDateTime m_studyDateTime;
    QString m_StudyUID;

    QString m_seriesNumber;
    QString m_seriesDescription;
    QString m_seriesPositionPatient;

    float m_imageSliceSpacing;
    vnl_vector_fixed<float, 3> m_imagePositionPatient;
    QString m_imageOrientationPatient;

    mutable itk::MetaDataDictionary dict;

public:
    static SeriesInfo& getInstance()
    {
        static SeriesInfo instance;
        return instance;
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
    itk::MetaDataDictionary dictionary() const;

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
     * @brief SeriesInfo
     * Assignment operator private and unimplemented.
     */
    SeriesInfo& operator=(const SeriesInfo&);

    itk::MetaDataDictionary makeDictionary() const;
    QString imagePositionPatientString() const;

    QString imagePositionPatientString(unsigned int sliceIdx) const;

};

#endif // SERIESINFO_H
