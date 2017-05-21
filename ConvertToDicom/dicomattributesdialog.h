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
    void handleImageAxialPushButtonClicked();
    void handleImageSaggitalPushButtonClicked();
    void handleImageCoronalPushButtonClicked();
    void handleStudyDateNowButtonClicked();
    void handleStudyUIDGenerateButtonClicked();
    void handlePatientsDOBDateEditChanged(const QDate &date);
    void handleStudyDateTimeDateTimeEditChanged(const QDateTime &datetime);
    void handlePatientsSexComboBoxIndexChanged(int idx);
    void handleStudyModalityComboBoxIndexChanged(int idx);
    void handleSeriesPatientPositionComboBoxActivated(int idx);
    void handleImageSlicesPerImageComboBoxActivated(int idx);

private:
    Ui::DicomAttributesDialog *ui;

    SeriesInfo* seriesInfo;
    Logger logger;

};

#endif // DICOMATTRIBUTESDIALOG_H
