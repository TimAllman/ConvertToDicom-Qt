//
//  dicomdictionaryinterface.cpp
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

#include "dicomdictionaryinterface.h"

#include "itkheaders.pch.h"

static QString PATIENTS_NAME_TAG = "0010|0010";
static QString PATIENTS_ID_TAG = "0010|0020";
static QString PATIENTS_BIRTH_DATE_TAG = "0010|0030";
static QString PATIENTS_SEX_TAG = "0010|0040";
static QString STUDY_DESCRIPTION_TAG = "0008|1030";
static QString STUDY_ID_TAG = "0020|0010";
static QString MODALITY_TAG = "0008|0060";
static QString PATIENT_POSITION_TAG = "0018|5100";
static QString STUDY_DATE_TAG = "0008|0020";
static QString STUDY_TIME_TAG = "0008|0030";
static QString STUDY_INSTANCE_UID_TAG = "0020|000D";
static QString SERIES_NUMBER_TAG = "0020|0011";
static QString SERIES_DESCRIPTION_TAG = "0008|103E";
static QString SPACING_BETWEEN_SLICES_TAG = "0018|0088";
static QString SLICE_THICKNESS_TAG = "0018|0050";
static QString IMAGE_POSITION_PATIENT_TAG = "0020|0032";
static QString IMAGE_ORIENTATION_PATIENT_TAG = "0020|0037";

DicomDictionaryInterface::DicomDictionaryInterface(DicomDictionaryInterface::DictionaryArrayType dictionaryArray)
    : dictArray(dictionaryArray)
{
}

bool DicomDictionaryInterface::setAttribute(const QString& tag, const QVariant& value, SizeType sliceIndex)
{
    itk::MetaDataDictionary* dict = dictArray[sliceIndex];
    QMetaType::Type valueType = QMetaType::Type(value.type());

    switch (valueType)
    {
        case QMetaType::QString:
            itk::EncapsulateMetaData<std::string>(*dict, tag.toStdString(), value.toString().toStdString());
            break;
        case QMetaType::Long:
            itk::EncapsulateMetaData<long>(*dict, tag.toStdString(), long(value.toInt()));
            break;
        case QMetaType::ULong:
            itk::EncapsulateMetaData<unsigned long>(*dict, tag.toStdString(), unsigned(value.toUInt()));
            break;
        default:
            return false;
    }

    return true;
}

bool DicomDictionaryInterface::setAttributeAllSlices(const QString& tag, const QVariant& value)
{
    bool result = true;
    SizeType length = dictArray.size();

    for (SizeType idx = 0; idx < length; ++idx)
    {
        result = setAttribute(tag, value, idx);
        if (!result)
            return result;
    }

    return result;
}

QVariant DicomDictionaryInterface::attribute(const QString& tag, SizeType sliceIndex)
{
    itk::MetaDataDictionary& dict = *dictArray[sliceIndex];

    const itk::MetaDataObjectBase *object = dict[tag.toStdString()];

    if (object->GetMetaDataObjectTypeInfo() == typeid (std::string))
    {
        std::string value;
        bool result = itk::ExposeMetaData<std::string>(dict, tag.toStdString(), value);
        if (result)
            return QVariant(QString(value.c_str()));
    }
    else if (object->GetMetaDataObjectTypeInfo() == typeid (int))
    {
        int value;
        bool result = itk::ExposeMetaData<int>(dict, tag.toStdString(), value);
        if (result)
            return QVariant(value);
    }
    else if (object->GetMetaDataObjectTypeInfo() == typeid (unsigned))
    {
        unsigned value;
        bool result = itk::ExposeMetaData<unsigned>(dict, tag.toStdString(), value);
        if (result)
            return QVariant(value);
    }

    return QVariant(); // return an invalid object.
}

QString DicomDictionaryInterface::patientsName()
{
    // All slices should have the same value so take the value from the first slice.
    return attribute(PATIENTS_NAME_TAG, 0).toString();
}

bool DicomDictionaryInterface::setPatientsName(QString patientsName)
{
    patientsName.truncate(64);
    bool result = setAttributeAllSlices(PATIENTS_NAME_TAG, patientsName);
    return result;
}

QString DicomDictionaryInterface::patientID()
{
    return attribute(PATIENTS_ID_TAG, 0).toString();
}

bool DicomDictionaryInterface::setPatientID(QString patientID)
{
    patientID.truncate(64);
    bool result = setAttributeAllSlices(PATIENTS_ID_TAG, patientID);
    return result;
}

QString DicomDictionaryInterface::patientsBirthDate()
{
    return attribute(PATIENTS_BIRTH_DATE_TAG, 0).toString();
}

bool DicomDictionaryInterface::setPatientsBirthDate(QString patientsBirthDate)
{
    patientsBirthDate.truncate(8);
    bool result = setAttributeAllSlices(PATIENTS_BIRTH_DATE_TAG, patientsBirthDate);
    return result;
}

QString DicomDictionaryInterface::patientsSex()
{
    return attribute(PATIENTS_SEX_TAG, 0).toString();
}

bool DicomDictionaryInterface::setPatientsSex(QString patientsSex)
{
    patientsSex.truncate(16);
    bool result = setAttributeAllSlices(PATIENTS_SEX_TAG, patientsSex);
    return result;
}

QString DicomDictionaryInterface::studyDescription()
{
    return attribute(STUDY_DESCRIPTION_TAG, 0).toString();
}

bool DicomDictionaryInterface::setStudyDescription(QString studyDescription)
{
    studyDescription.truncate(64);
    bool result = setAttributeAllSlices(PATIENTS_SEX_TAG, studyDescription);
    return result;
}

QString DicomDictionaryInterface::studyID()
{
    return attribute(STUDY_ID_TAG, 0).toString();
}

bool DicomDictionaryInterface::setStudyID(QString studyID)
{
    studyID.truncate(16);
    bool result = setAttributeAllSlices(PATIENTS_SEX_TAG, studyID);
    return result;
}

QString DicomDictionaryInterface::modality()
{
    return attribute(MODALITY_TAG, 0).toString();
}

bool DicomDictionaryInterface::setModality(QString modality)
{
    modality.truncate(16);
    bool result = setAttributeAllSlices(MODALITY_TAG, modality);
    return result;
}

QString DicomDictionaryInterface::studyDate()
{
    return attribute(STUDY_DATE_TAG, 0).toString();
}

bool DicomDictionaryInterface::setStudyDate(QString studyDate)
{
    studyDate.truncate(8);
    bool result = setAttributeAllSlices(STUDY_DATE_TAG, studyDate);
    return result;
}

QString DicomDictionaryInterface::studyTime()
{
    return attribute(STUDY_TIME_TAG, 0).toString();
}

bool DicomDictionaryInterface::setStudyTime(QString studyTime)
{
    studyTime.truncate(8);
    bool result = setAttributeAllSlices(STUDY_DATE_TAG, studyTime);
    return result;
}

QString DicomDictionaryInterface::studyInstanceUID()
{
    return attribute(STUDY_INSTANCE_UID_TAG, 0).toString();
}

bool DicomDictionaryInterface::setStudyInstanceUID(QString studyInstanceUID)
{
    studyInstanceUID.truncate(16);
    bool result = setAttributeAllSlices(STUDY_DATE_TAG, studyInstanceUID);
    return result;
}

QString DicomDictionaryInterface::seriesNumber()
{
    return attribute(SERIES_NUMBER_TAG, 0).toString();
}

bool DicomDictionaryInterface::setSeriesNumber(QString seriesNumber)
{
    seriesNumber.truncate(16);
    bool result = setAttributeAllSlices(STUDY_DATE_TAG, seriesNumber);
    return result;
}

QString DicomDictionaryInterface::seriesDescription()
{
    return attribute(SERIES_DESCRIPTION_TAG, 0).toString();
}

bool DicomDictionaryInterface::setSeriesDescription(QString seriesDescription)
{
    seriesDescription.truncate(64);
    bool result = setAttributeAllSlices(STUDY_DATE_TAG, seriesDescription);
    return result;
}

QString DicomDictionaryInterface::patientPosition()
{
    return attribute(PATIENT_POSITION_TAG, 0).toString();
}

bool DicomDictionaryInterface::setPatientPosition(QString patientPosition)
{
    patientPosition.truncate(16);
    bool result = setAttributeAllSlices(STUDY_DATE_TAG, patientPosition);
    return result;
}

QString DicomDictionaryInterface::sliceThickness()
{
    return attribute(SLICE_THICKNESS_TAG, 0).toString();
}

bool DicomDictionaryInterface::setSliceThickness(QString sliceThickness)
{
    sliceThickness.truncate(16);
    bool result = setAttributeAllSlices(STUDY_DATE_TAG, sliceThickness);
    return result;
}

QString DicomDictionaryInterface::spacingBetweenSlices()
{
    return attribute(SPACING_BETWEEN_SLICES_TAG, 0).toString();
}

bool DicomDictionaryInterface::setSpacingBetweenSlices(QString spacingBetweenSlices)
{
    spacingBetweenSlices.truncate(16);
    bool result = setAttributeAllSlices(SPACING_BETWEEN_SLICES_TAG, spacingBetweenSlices);
    return result;
}

QString DicomDictionaryInterface::imagePositionPatient(DicomDictionaryInterface::SizeType sliceIndex)
{
    return attribute(SPACING_BETWEEN_SLICES_TAG, sliceIndex).toString();
}

bool DicomDictionaryInterface::setImagePositionPatient(QString imagePositionPatient, DicomDictionaryInterface::SizeType sliceIndex)
{
    imagePositionPatient.truncate(16);
    bool result = setAttribute(SPACING_BETWEEN_SLICES_TAG, imagePositionPatient, sliceIndex);
    return result;
}

QString DicomDictionaryInterface::imageOrientationPatient()
{
    return attribute(IMAGE_ORIENTATION_PATIENT_TAG, 0).toString();
}

bool DicomDictionaryInterface::setImageOrientationPatient(QString imageOrientationPatient)
{
    imageOrientationPatient.truncate(106);
    bool result = setAttributeAllSlices(IMAGE_ORIENTATION_PATIENT_TAG, imageOrientationPatient);
    return result;
}



