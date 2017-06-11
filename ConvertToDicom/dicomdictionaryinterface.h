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
 * itk::MetaDataDictionaryArray. The method names are taken from the DICOM standard.
 * http://dicom.nema.org/medical/dicom/current/output/html/part06.html#table_6-1
 */
class DicomDictionaryInterface
{
public:
    typedef std::vector<itk::MetaDataDictionary*> DictionaryArrayType;

    /**
     * This typedef is created merely to prevent compiler warnings.
     * As of writing it describes an unsigned long int.
     */
    typedef DictionaryArrayType::size_type SizeType;

    /**
     * Constructor with dictionary array. Subsequent operations are performed on the
     * dictionaries pointed to by the array of pointers.
     * @param dictionaryArray The array of pointers to the slice dictionaries.
     */
    DicomDictionaryInterface(DictionaryArrayType dictionaryArray);

    /**
     * Get the value of Patient's Name, "0010|0010".
     * @return The patient's name
     */
    QString patientsName();

    /**
     * Set the value of Patient's Name, "0010|0010".
     * @param patientsName The patient's name. The length limit is 64 characters enforced by truncation.
     * @return true if successful, false otherwide.
     * @return true if successful, false otherwide.
     */
    bool setPatientsName(QString patientsName);

    /**
     * Get the value of Patient ID, "0010|0020".
     * @return The patient's ID.
     */
    QString patientID();

    /**
     * Set the value of Patient ID, "0010|0020".
     * @param patientID The patient's ID. The length limit is 64 characters enforced by truncation.
     * @return true if successful, false otherwide.
     */
    bool setPatientID(QString patientID);

    /**
     * Get the value of Patient's Birth Date, "0010|0030".
     * @return The patient's birth date.
     */
    QString patientsBirthDate();

    /**
     * Set the value of Patient's Birth Date, "0010|0030".
     * @param patientsBirthDate The patient's birth date in the format "YYYYMMDD".
     * @return true if successful, false otherwide.
     */
    bool setPatientsBirthDate(QString patientsBirthDate);

    /**
     * Get the value of Patient's Sex, "0010|0040".
     * @return The patient's sex as a string.
     */
    QString patientsSex();

    /**
     * Set the value of Patient's Sex, "0010|0040".
     * @param patientsSex The patient's sex, maximum 16 characters.
     * @return true if successful, false otherwide.
     */
    bool setPatientsSex(QString patientsSex);

    /**
     * Get the value of Study Description, "0008|1030".
     * @return The study description.
     */
    QString studyDescription();

    /**
     * Set the value of Study Description, "0008|1030".
     * @param studyDescription The study description, maximum 64 characters enforced by truncation.
     * @return true if successful, false otherwide.
     */
    bool setStudyDescription(QString studyDescription);

    /**
     * Get the value of Study ID, "0020|0010".
     * @return The study ID.
     */
    QString studyID();

    /**
     * Set the value of Study ID, "0020|0010".
     * @param studyID The study ID, maximum 16 characters enforced by truncation.
     * @return true if successful, false otherwide.
     */
    bool setStudyID(QString studyID);

    /**
     * Get the value of Modality, "0008|0060".
     * @return The modality.
     */
    QString modality();

    /**
     * Set the value of Modality, "0008|0060".
     * @param modality The modality, maximum 16 characters enforced by truncation. Typically "MR", "CT" etc.
     * @return true if successful, false otherwide.
     */
    bool setModality(QString modality);

    /**
     * Get the value of Study Date, "0008|0020".
     * @return The study date.
     */
    QString studyDate();

    /**
     * Set the value of Study Date, "0008|0020".
     * @param studyDate The study date in the format "YYYYMMDD".
     * @return true if successful, false otherwide.
     */
    bool setStudyDate(QString studyDate);

    /**
     * Get the value of Study Time, "0008|0030".
     * @return The study time.
     */
    QString studyTime();

    /**
     * Set the value of Study Time, "0008|0030".
     * @param studyTime The study time in the format "HHMMSS.FFFFFF".
     * @return true if successful, false otherwide.
     */
    bool setStudyTime(QString studyTime);

    /**
     * Get the value of Study Instance UID, "0020|000D".
     * @return The study instance UID.
     */
    QString studyInstanceUID();

    /**
     * Set the value of Study Instance UID, "0020|000D".
     * @param studyInstanceUID The study instance UID containing only '0'-'9' and '.'.
     * Maximum 16 characters enforced by truncation.
     * @return true if successful, false otherwide.
     */
    bool setStudyInstanceUID(QString studyInstanceUID);

    /**
     * Get the value of SeriesNumber, "0020|0011".
     * @return The series number.
     */
    QString seriesNumber();

    /**
     * Set the value of Series Number, "0020|0011".
     * @param seriesNumber The series number - a 32 bit integer expressed as astring containing only '0'-'9',
     * '+' and '-'. Maximum 16 characters enforced by truncation.
     * @return true if successful, false otherwide.
     */
    bool setSeriesNumber(QString seriesNumber);

    /**
     * Get the value of Series Description, "0008|103E".
     * @return The series description.
     */
    QString seriesDescription();

    /**
     * Set the value of Series Description, "0008|103E".
     * @param seriesDescription The study description, maximum 64 characters enforced by truncation.
     * @return true if successful, false otherwide.
     */
    bool setSeriesDescription(QString seriesDescription);

    /**
     * Get the value of Patient Position, "0018|5100".
     * @return The patient position as a short string such as "HFS" (head first supine).
     */
    QString patientPosition();

    /**
     * Set the value of Patient Position, "0018|5100".
     * @param patientPosition The patient position as a short string such as "HFS" (head first supine).
     * Only 'A'-'Z', '0'-'9', ' ' and '_' allowed. Maximum 16 characters enforced by truncation.
     * @return true if successful, false otherwide.
     */
    bool setPatientPosition(QString patientPosition);

    /**
     * Get the value of Slice Thickness, "0018|0050".
     * @return The slice thickness in mm.
     */
    QString sliceThickness();

    /**
     * Set the value of Slice Thickness, "0018|0050".
     * @param sliceThickness The slice thickness in mm as a string.
     * Maximum 16 characters enforced by truncation.
     * @return true if successful, false otherwide.
     */
    bool setSliceThickness(QString sliceThickness);

    /**
     * Get the value of Spacing Between Slices, "0018|0088".
     * @return The slice spacing in mm.
     */
    QString spacingBetweenSlices();

    /**
     * Set the value of Spacing Between Slices, "0018|0088".
     * @param spacingBetweenSlices The slice spacing in mm as a string.
     * Maximum 16 characters enforced by truncation.
     * @return true if successful, false otherwide.
     */
    bool setSpacingBetweenSlices(QString spacingBetweenSlices);

    /**
     * Get the value of Image Position (Patient), "0020|0032".
     * @param sliceIndex The index of the slice whose position we want.
     * @return The x, y, and z coordinates of the upper left hand corner
     * of the image, in mm, as a string. e.g. "0.0\\0.0\\0.0"
     */
    QString imagePositionPatient(DicomDictionaryInterface::SizeType sliceIndex);

    /**
     * Set the value of Image Position (Patient), "0020|0032".
     * @param imagePositionPatient The x, y, and z coordinates of the upper left hand corner
     * of the image, in mm. e.g. "0.0\\0.0\\0.0".
     * Maximum length for 3 numbers and 4 '\' is 16 * 3 + 4 = 23 bytes.
     * @param sliceIndex The index of the slice whose position we want to set.
     * @return true if successful, false otherwide.
     */
    bool setImagePositionPatient(QString imagePositionPatient, DicomDictionaryInterface::SizeType sliceIndex);

    /**
     * Get the value of Image Orientation (Patient), "0020|0037".
     * @return The direction cosines of the first row and the first column with respect to the patient.
     */
    QString imageOrientationPatient();

    /**
     * Set the value of Image Orientation (Patient), "0020|0037".
     * @param imageOrientationPatient The direction cosines of the first row and the first column with
     * respect to the patient. There are six values separated by back slashes,
     * e.g. "1.0\\0.0\\0.0\\1.0\\1.0\\0.0". Maximum 106 characters enforced by truncation.
     * @return true if successful, false otherwide.
     */
    bool setImageOrientationPatient(QString imageOrientationPatient);

private:
    /**
     * Set the value corresponding the tag in the slice at index sliceIndex.
     * This method supports the public setters for specific attributes.
     * @param tag A DICOM tag in the format "0010|0010".
     * @param value The value to be stored. May be string or numeric.
     * @param sliceIndex The index of the slice within the series to receive the new value.
     * @return true if successful, false if not. This fails only if the tag is invalid or
     * is one (such as image location) that is valid only for one slice.
     */
    bool setAttribute(const QString &tag, const QVariant &value, DicomDictionaryInterface::SizeType sliceIndex);

    /**
     * Set the value corresponding the tag in all of the slices.
     * This method supports the public setters for specific attributes.
     * @param tag A DICOM tag in the format "0010|0010".
     * @param value The value to be stored. May be string or numeric.
     * @return true if successful, false if not. This fails only if the tag is invalid or
     * is one (such as image location) that is valid only for one slice.
     */
    bool setAttributeAllSlices(const QString &tag, const QVariant &value);

    /**
     * @brief attribute
     * Get the value of the attribute corresponding to the tag. Although this method is public,
     * the getters for specific attribute values should be used.
     * @param tag The tag of the attribute desired in the format "0010|0010"
     * @param sliceIndex The index of the slice within the series to query.
     * @return The value if successful or an invalid QVariant if not.
     */
    QVariant attribute(const QString &tag, DicomDictionaryInterface::SizeType sliceIndex);

    DictionaryArrayType dictArray;
};

#endif // DICOMDICTIONARYINTERFACE_H
