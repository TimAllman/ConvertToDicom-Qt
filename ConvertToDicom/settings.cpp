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
#include "loggername.h"
#include "seriesinfo.h"

#include <log4cplus/loggingmacros.h>

#include <QDir>
#include <QDateTime>

QString Settings::LoggingLevelKey = "LoggingLevel";
QString Settings::OverwriteFilesKey = "OverwriteFiles";
QString Settings::InputDirKey = "InputDir";
QString Settings::OutputDirKey = "OutputDir";
QString Settings::TimeIncrementKey = "TimeIncrement";
QString Settings::PatientsNameKey = "PatientsName";
QString Settings::PatientsIDKey = "PatientsID";
QString Settings::PatientsDOBKey = "PatientsDOB";
QString Settings::PatientsSexKey = "PatientsSex";
QString Settings::StudyDescriptionKey = "StudyDescription";
QString Settings::StudyIDKey = "StudyID";
QString Settings::StudyModalityKey = "StudyModality";
QString Settings::StudyDateTimeKey = "StudyDateTime";
QString Settings::StudyStudyUIDKey = "StudyStudyUID";
QString Settings::SeriesDescriptionKey = "SeriesDescription";
QString Settings::SeriesNumberKey = "SeriesNumber";
QString Settings::SeriesPatientPositionKey = "SeriesPatientPosition";

Settings::Settings()
    : logger(log4cplus::Logger::getInstance(std::string(LOGGER_NAME) + ".Settings"))
{
    LOG4CPLUS_TRACE(logger, "Enter");


    // set the defaults for the settings
    setValue(LoggingLevelKey, log4cplus::INFO_LOG_LEVEL);

    LOG4CPLUS_DEBUG(logger, "Registered default settings.");
}

void Settings::loadSettings(SeriesInfo& info)
{
    This should go into SeriesInfo

    LOG4CPLUS_TRACE(logger, "Enter");


    LOG4CPLUS_DEBUG(logger, "Loaded current settings and set default settings.");
}

void Settings::saveSettings(SeriesInfo& info)
{
    LOG4CPLUS_TRACE(logger, "Enter");

    // save the current settings
    setValue(LoggingLevelKey, logger.getLogLevel());

    setValue(OverwriteFilesKey, info.overwriteFiles());
    setValue(InputDirKey, info.inputDir());
    setValue(OutputDirKey, info.outputDir());
    setValue(TimeIncrementKey, info.timeIncrement());
    setValue(PatientsNameKey, info.patientsName());
    setValue(PatientsIDKey, info.patientsID());
    setValue(PatientsDOBKey, info.patientsDOB());
    setValue(PatientsSexKey, info.patientsSex());
    setValue(SeriesDescriptionKey, info.seriesDescription());
    setValue(SeriesNumberKey, info.seriesNumber());
    setValue(SeriesPatientPositionKey, info.seriesPositionPatient());
    setValue(StudyDescriptionKey, info.studyDescription());
    setValue(StudyIDKey, info.studyID());
    setValue(StudyModalityKey, info.studyModality());
    setValue(StudyDateTimeKey, info.studyDateTime());
    setValue(StudyStudyUIDKey, info.studyStudyUID());

    // force a write to disk
    sync();

    LOG4CPLUS_DEBUG(logger, "Saved settings.");
}
