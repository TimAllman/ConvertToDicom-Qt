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

//    /**
//     * @brief setOverwriteFiles
//     * Set flag which indicates whether generated files will overwrite existing files.
//     * @param overwriteFiles Set flag to this value.
//     */
//    void setOverwriteFiles(bool overwriteFiles)
//    {
//        m_overwriteFiles = overwriteFiles;
//    }

    /**
     * @brief inputDir
     * Get the directory containing the files to be converted.
     * @return The current input directory.
     */
    QString inputDir() const
    {
        return m_inputDir;
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

    QString outputDir() const
    {
        return m_outputDir;
    }

    void setOutputDir(const QString& outputDir)
    {
        m_outputDir = outputDir;
    }

    QString outputPath() const
    {
        return m_outputPath;
    }

    void setOutputPath(const QString& outputPath)
    {
        m_outputPath = outputPath;
    }

    int numberOfImages() const
    {
        return m_numberOfImages;
    }

    void setNumberOfImages(int numberOfImages)
    {
        m_numberOfImages = numberOfImages;
    }

    int slicesPerImage() const
    {
        return m_slicesPerImage;
    }

    void setSlicesPerImage(int slicesPerImage)
    {
        m_slicesPerImage = slicesPerImage;
    }

    int numberOfSlices() const
    {
        return m_numberOfSlices;
    }

    void setNumberOfSlices(int numberOfSlices)
    {
        m_numberOfSlices = numberOfSlices;
    }

    float timeIncrement() const
    {
        return m_timeIncrement;
    }

    void setTimeIncrement(float timeIncrement)
    {
        m_timeIncrement = timeIncrement;
    }

    QVector<float>& acqTimes()
    {
        return m_acqTimes;
    }

    QString patientsName() const
    {
        return m_patientsName;
    }

    void setPatientsName(const QString& patientsName)
    {
        m_patientsName = patientsName;
    }

    QString patientsID() const
    {
        return m_patientsID;
    }

    void setPatientsID(const QString& patientsID)
    {
        m_patientsID = patientsID;
    }

    QString patientsDOB() const
    {
        return m_patientsDOB;
    }

    void setPatientsDOB(const QString& patientsDOB)
    {
        m_patientsDOB = patientsDOB;
    }

    QString patientsSex() const
    {
        return m_patientsSex;
    }

    void setPatientsSex(const QString& patientsSex)
    {
        m_patientsSex = patientsSex;
    }

    QString studyDescription() const
    {
        return m_studyDescription;
    }

    void setStudyDescription(const QString& studyDescription)
    {
        m_studyDescription = studyDescription;
    }

    QString studyID() const
    {
        return m_studyID;
    }

    void setStudyID(const QString& studyID)
    {
        m_studyID = studyID;
    }

    QString studyModality() const
    {
        return m_studyModality;
    }

    void setStudyModality(const QString& studyModality)
    {
        m_studyModality = studyModality;
    }

    QDateTime studyDateTime() const
    {
        return m_studyDateTime;
    }

    void setStudyDateTime(const QString& studyDateTime)
    {
        m_studyDateTime = QDateTime::fromString(studyDateTime);
    }

    QString studyStudyUID() const
    {
        return m_StudyUID;
    }

    void setStudyStudyUID(const QString& studyStudyUID)
    {
        m_StudyUID = studyStudyUID;
    }

    QString seriesNumber() const
    {
        return m_seriesNumber;
    }

    void setSeriesNumber(const QString& seriesNumber)
    {
        m_seriesNumber = seriesNumber;
    }

    QString seriesDescription() const
    {
        return m_seriesDescription;
    }

    void setSeriesDescription(const QString& seriesDescription)
    {
        m_seriesDescription = seriesDescription;
    }

    QString seriesPositionPatient() const
    {
        return m_seriesPositionPatient;
    }

    void setSeriesPositionPatient(const QString& seriesPositionPatient)
    {
        m_seriesPositionPatient = seriesPositionPatient;
    }

    float imageSliceSpacing() const
    {
        return m_imageSliceSpacing;
    }

    void setImageSliceSpacing(float imageSliceSpacing)
    {
        m_imageSliceSpacing = imageSliceSpacing;
    }

    float imagePositionPatientX() const
    {
        return m_imagePositionPatient[0];
    }

    void setImagePositionPatientX(float imagePositionPatientX)
    {
        m_imagePositionPatient[0] = imagePositionPatientX;
    }

    float imagePositionPatientY() const
    {
        return m_imagePositionPatient[1];
    }

    void setImagePositionPatientY(float imagePositionPatientY)
    {
        m_imagePositionPatient[1] = imagePositionPatientY;
    }

    float imagePositionPatientZ() const
    {
        return m_imagePositionPatient[2];
    }

    void setImagePositionPatientZ(float imagePositionPatientZ)
    {
        m_imagePositionPatient[2] = imagePositionPatientZ;
    }

    QString imagePatientOrientation() const
    {
        return m_imageOrientationPatient;
    }

    void setImagePatientOrientation(const QString& imageOrientationPatient)
    {
        m_imageOrientationPatient = imageOrientationPatient;
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

signals:
    void overwriteFilesValueChanged(bool overwriteFiles);

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
    /**
     * Default constructor. Sets initial values of members.
     */
    explicit SeriesInfo();

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
    itk::MetaDataDictionary makeDictionary() const;
    QString imagePositionPatientString() const;

    QString imagePositionPatientString(unsigned int sliceIdx) const;

};

#endif // SERIESINFO_H
