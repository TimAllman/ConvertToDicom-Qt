//
//  settings.cpp
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

#include "settings.h"
#include "logger.h"
#include "seriesinfo.h"

#include <log4cplus/loggingmacros.h>

#include <QDir>
#include <QDateTime>

QString Settings::LoggingLevelKey = "LoggingLevel";
QString Settings::OverwriteFilesKey = "OverwriteFilesYYY";
QString Settings::InputDirKey = "InputDir";
QString Settings::OutputDirKey = "OutputDir";
QString Settings::SeriesTimeIncrementKey = "TimeIncrement";
QString Settings::PatientNameKey = "PatientName";
QString Settings::PatientIDKey = "PatientID";
QString Settings::PatientDOBKey = "PatientDOB";
QString Settings::PatientSexKey = "PatientSex";
QString Settings::StudyDescriptionKey = "StudyDescription";
QString Settings::StudyIDKey = "StudyID";
QString Settings::StudyModalityKey = "StudyModality";
QString Settings::StudyDateTimeKey = "StudyDateTime";
QString Settings::StudyInstanceUIDKey = "StudyStudyUID";
QString Settings::SeriesDescriptionKey = "SeriesDescription";
QString Settings::SeriesNumberKey = "SeriesNumber";
QString Settings::SeriesPatientPositionKey = "SeriesPatientPosition";
//QString Settings::ImageSliceSpacingKey = "ImageSliceSpacing";
//QString Settings::ImagePatientPositionXKey = "ImagePatientPositionX";
//QString Settings::ImagePatientPositionYKey = "ImagePatientPositionY";
//QString Settings::ImagePatientPositionZKey = "ImagePatientPositionZ";
//QString Settings::ImagePatientOrientationKey = "ImagePatientOrientation";

Settings::Settings()
    : logger(log4cplus::Logger::getInstance(std::string(LOGGER_NAME) + ".Settings"))
{
    LOG4CPLUS_TRACE(logger, "Enter");


    // set the defaults for the settings
    //setValue(LoggingLevelKey, log4cplus::INFO_LOG_LEVEL);

    LOG4CPLUS_DEBUG(logger, "Registered default settings.");
}
