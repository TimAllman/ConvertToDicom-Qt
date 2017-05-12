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

#include <log4cplus/logger.h>

#include <QString>
#include <QSettings>

class Settings : public QSettings
{
    log4cplus::Logger logger;

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

    static QString ImageSliceSpacingKey;
    static QString ImagePatientPositionXKey;
    static QString ImagePatientPositionYKey;
    static QString ImagePatientPositionZKey;
    static QString ImagePatientOrientationKey;

    /**
     * @brief Settings
     * Default constructor to create and initialise application settings.
     */
    explicit Settings();

private:
    QMap<QString, QVariant> defaults; // this contains the default settings.

    /**
     * @brief registerDefaults
     * Set up the default settings.
     */
    void registerDefaults();


};

#endif // SETTINGS_H
