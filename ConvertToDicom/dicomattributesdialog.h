//
//  dicomattributesdialog.h
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
#ifndef DICOMATTRIBUTESDIALOG_H
#define DICOMATTRIBUTESDIALOG_H

#include "logger.h"
#include "seriesinfo.h"

#include <QDialog>

class SeriesInfo;

namespace Ui {
class DicomAttributesDialog;
}

class DicomAttributesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DicomAttributesDialog(QWidget *parent = 0);
    ~DicomAttributesDialog();

    void loadData();

    void storeData();

private slots:
    void handlePatientNameLineEditEditingFinished();
    void handlePatientIDLineEditEditingFinished();
    void handlePatientDOBDateEditChanged(const QDate &date);
    void handlePatientSexComboBoxIndexChanged(int idx);

    void handleStudyDescriptionLineEditEditingFinished();
    void handleStudyIDLineEditEditingFinished();
    void handleStudyInstanceUIDLineEditEditingFinished();
    void handleStudyDateNowButtonClicked();
    void handleStudyUIDGenerateButtonClicked();
    void handleStudyDateTimeDateTimeEditChanged(const QDateTime &datetime);
    void handleStudyModalityComboBoxIndexChanged(int idx);

    void handleSeriesDescriptionLineEditEditingFinished();
    void handleSeriesPatientPositionComboBoxActivated(int idx);
    void handleSeriesPatientPositionComboBoxIndexChanged(int idx);
    void handleSeriesNumberLineEditEditingFinished();
    void handleSeriesTimeIncrementLineEditEditingFinished();

    void handleImageSlicesPerImageComboBoxIndexChanged(int idx);
    void handleImageSliceSpacingLineEditEditingFinished();
    void handleImagePatientPositionXLineEditEditingFinished();
    void handleImagePatientPositionYLineEditEditingFinished();
    void handleImagePatientPositionZLineEditEditingFinished();
    void handleImagePatientOrientationLineEditEditingFinished();
    void handleImageAxialPushButtonClicked();
    void handleImageSaggitalPushButtonClicked();
    void handleImageCoronalPushButtonClicked();

private:
    Ui::DicomAttributesDialog *ui;

    SeriesInfo* seriesInfo;
    Logger logger;

};

#endif // DICOMATTRIBUTESDIALOG_H
