//
//  settings
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
#ifndef SETTINGS_H
#define SETTINGS_H

class SeriesInfo;

#include "logger.h"

#include <QString>
#include <QSettings>

/**
 * @brief The Settings class
 * Class which saves and restores settings between executions. The static xxxKey members
 * are keys used to look up the appropriate values.
 */
class Settings : public QSettings
{
public:
    // Keys for preferences.
    static QString LoggingLevelKey;
    static QString OverwriteFilesKey;
    static QString InputDirKey;
    static QString OutputDirKey;
    static QString TimeIncrementKey;

    static QString PatientsNameKey;
    static QString PatientsIDKey;
    static QString PatientsDOBKey;
    static QString PatientsSexKey;

    static QString StudyDescriptionKey;
    static QString StudyIDKey;
    static QString StudyModalityKey;
    static QString StudyDateTimeKey;
    static QString StudyStudyUIDKey;

    static QString SeriesDescriptionKey;
    static QString SeriesNumberKey;
    static QString SeriesPatientPositionKey;

    //    static QString ImageSliceSpacingKey;
    //    static QString ImagePatientPositionXKey;
    //    static QString ImagePatientPositionYKey;
    //    static QString ImagePatientPositionZKey;
    //    static QString ImagePatientOrientationKey;

    /**
     * @brief Settings
     * Default constructor to create and initialise application settings.
     */
    explicit Settings();

private:
    Logger logger;
};

#endif // SETTINGS_H
