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

DicomDictionaryInterface::DicomDictionaryInterface(DicomDictionaryInterface::DictionaryArrayType dictionaryArray)
    : dictArray(dictionaryArray)
{
}

bool DicomDictionaryInterface::setAttribute(const QString& tag, const QVariant& value, int sliceIndex)
{

}

QVariant DicomDictionaryInterface::attribute(const QString& tag, int sliceIndex)
{

}

QString DicomDictionaryInterface::patientsName()
{

}

void DicomDictionaryInterface::setPatientsName(const QString& patientsName)
{

}

QString DicomDictionaryInterface::patientID()
{

}

void DicomDictionaryInterface::setPatientID(const QString& patientID)
{

}

QString DicomDictionaryInterface::patientsBirthDate()
{

}

void DicomDictionaryInterface::setPatientsBirthDate(const QString& patientsBirthDate)
{

}

QString DicomDictionaryInterface::patientsSex()
{

}

void DicomDictionaryInterface::setPatientsSex(const QString& patientsSex)
{

}

QString DicomDictionaryInterface::studyDescription()
{

}

void DicomDictionaryInterface::setStudyDescription(const QString& studyDescription)
{

}

QString DicomDictionaryInterface::studyID()
{

}

void DicomDictionaryInterface::setStudyID(const QString& studyID)
{

}

QString DicomDictionaryInterface::modality()
{

}

void DicomDictionaryInterface::setModality(const QString& modality)
{

}

QString DicomDictionaryInterface::studyDate()
{

}

void DicomDictionaryInterface::setStudyDate(const QString& studyDate)
{

}

QString DicomDictionaryInterface::studyTime()
{

}

void DicomDictionaryInterface::setStudyTime(const QString& studyTime)
{

}

QString DicomDictionaryInterface::studyInstanceUID()
{

}

void DicomDictionaryInterface::setStudyInstanceUID(const QString& studyInstanceUID)
{

}

QString DicomDictionaryInterface::seriesNumber()
{

}

void DicomDictionaryInterface::setSeriesNumber(const QString& seriesNumber)
{

}

QString DicomDictionaryInterface::seriesDescription()
{

}

void DicomDictionaryInterface::setSeriesDescription(const QString& seriesDescription)
{

}
