//
//  dicommetadatainterface.h
//  ConvertToDicom
//

/* ConvertToDicom converts a series of images to DICOM format from any format recognized
 * by ITK (http://www.itk.org).
 * Copyright (C) 2017 Tim Allman
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
#ifndef DICOMDICTIONARYINTERFACE_H
#define DICOMDICTIONARYINTERFACE_H

#include <QVariant>

#include <itkMetaDataDictionary.h>

/**
 * @brief The DicomDictionaryInterface class
 * This class provides a convenient to get and set data in an instance of
 * itk::MetaDataDictionaryArray.
 */
class DicomDictionaryInterface
{
public:
    typedef std::vector<itk::MetaDataDictionary*> DictionaryArrayType;

    /**
     * Constructor with dictionary array. Subsequent operations are performed on the
     * dictionaries pointed to by the array of pointers.
     * @param dictionaryArray The array of pointers to the slice dictionaries.
     */
    DicomDictionaryInterface(DictionaryArrayType dictionaryArray);

    /**
     * @brief setAttribute
     * Set the value corresponding the tag. Although this method is public, the setters for
     * specific attribute values should be used.
     * @param tag A DICOM tag in the format "0010|0010".
     * @param value The value to be stored. May be string or numeric.
     * @param sliceIndex The index of the slice within the series to receive the new value. Set to -1 to
     * set all slices.
     * @return true if successful, false if not. This fails only if the tag is invalid or
     * is one (such as image location) that is valid only for one slice.
     */
    bool setAttribute(const QString &tag, const QVariant &value, int sliceIndex);

    /**
     * @brief attribute
     * Get the value of the attribute corresponding to the tag. Although this method is public,
     * the getters for specific attribute values should be used.
     * @param tag The tag of the attribute desired in the format "0010|0010"
     * @param sliceIndex The index of the slice within the series to query.
     * @return The value if successful or an invalid QVariant if not.
     */
    QVariant attribute(const QString &tag, int sliceIndex);


    /**
     * Get the value of Patient's Name, "0010|0010".
     * @return The patient's name
     */
    QString patientsName();

    /**
     * Set the value of Patient's Name, "0010|0010".
     * @param patientsName The patient's name. The length limit is 64 characters enforced by truncation.
     */
    void setPatientsName(const QString &patientsName);

    /**
     * Get the value of Patient ID, "0010|0020".
     * @return The patient's ID.
     */
    QString patientID();

    /**
     * Set the value of Patient ID, "0010|0020".
     * @param patientID The patient's ID. The length limit is 64 characters enforced by truncation.
     */
    void setPatientID(const QString &patientID);

    /**
     * Get the value of Patient's Birth Date, "0010|0030".
     * @return The patient's birth date.
     */
    QString patientsBirthDate();

    /**
     * Set the value of Patient's Birth Date, "0010|0030".
     * @param patientsBirthDate The patient's birth date in the format "YYYYMMDD".
     */
    void setPatientsBirthDate(const QString &patientsBirthDate);

    /**
     * Get the value of Patient's Sex, "0010|0040".
     * @return The patient's sex as a string.
     */
    QString patientsSex();

    /**
     * Set the value of Patient's Sex, "0010|0040".
     * @param patientsSex The patient's sex, maximum 16 characters.
     */
    void setPatientsSex(const QString &patientsSex);

    /**
     * Get the value of Study Description, "0008|1030".
     * @return The study description.
     */
    QString studyDescription();

    /**
     * Set the value of Study Description, "0008|1030".
     * @param studyDescription The study description, maximum 64 characters enforced by truncation.
     */
    void setStudyDescription(const QString &studyDescription);

    /**
     * Get the value of Study ID, "0020|0010".
     * @return The study ID.
     */
    QString studyID();

    /**
     * Set the value of Study ID, "0020|0010".
     * @param studyID The study ID, maximum 16 characters enforced by truncation.
     */
    void setStudyID(const QString &studyID);

    /**
     * Get the value of Modality, "0008|0060".
     * @return The modality.
     */
    QString modality();

    /**
     * Set the value of Modality, "0008|0060".
     * @param modality The modality, maximum 16 characters enforced by truncation. Typically "MR", "CT" etc.
     */
    void setModality(const QString &modality);

    /**
     * Get the value of Study Date, "0008|0020".
     * @return The study date.
     */
    QString studyDate();

    /**
     * Set the value of Study Date, "0008|0020".
     * @param studyDate The study date in the format "YYYYMMDD".
     */
    void setStudyDate(const QString &studyDate);

    /**
     * Get the value of Study Time, "0008|0030".
     * @return The study time.
     */
    QString studyTime();

    /**
     * Set the value of Study Time, "0008|0030".
     * @param studyTime The study time in the format "HHMMSS.FFFFFF".
     */
    void setStudyTime(const QString &studyTime);

    /**
     * Get the value of Study Instance UID, "0020|000D".
     * @return The study instance UID.
     */
    QString studyInstanceUID();

    /**
     * Set the value of Study Instance UID, "0020|000D".
     * @param studyInstanceUID The study instance UID containing only '0'-'9' and '.'.
     * Maximum 16 characters enforced by truncation.
     */
    void setStudyInstanceUID(const QString &studyInstanceUID);

    /**
     * Get the value of SeriesNumber, "0020|0011".
     * @return The series number.
     */
    QString seriesNumber();

    /**
     * Set the value of Series Number, "0020|0011".
     * @param seriesNumber The series number - a 32 bit integer expressed as astring containing only '0'-'9',
     * '+' and '-'.
     * Maximum 16 characters enforced by truncation.
     */
    void setSeriesNumber(const QString &seriesNumber);

    /**
     * Get the value of Series Description, "0008|103E".
     * @return The series description.
     */
    QString seriesDescription();

    /**
     * Set the value of Series Description, "0008|103E".
     * @param seriesDescription The study description, maximum 64 characters enforced by truncation.
     */
    void setSeriesDescription(const QString &seriesDescription);












    /**
     * Get the value of Image Position (Patient), "0020|0032".
     * @return The x, y, and z coordinates of the upper left hand corner
     * of the image, in mm, as a string. e.g. "0.0\\0.0\\0.0"
     */
    QString imagePositionPatient();

    /**
     * Set the value of Image Position (Patient), "0020|0032".
     * @param imagePositionPatient The x, y, and z coordinates of the upper left hand corner
     * of the image, in mm. e.g. "0.0\\0.0\\0.0"
     */
    void setImagePositionPatient(const QString &imagePositionPatient);

private:
    DictionaryArrayType dictArray;
};

#endif // DICOMDICTIONARYINTERFACE_H
