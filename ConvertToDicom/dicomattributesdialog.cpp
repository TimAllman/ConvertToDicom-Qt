//
//  dicomattributesdialog.cpp
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
#include "dicomattributesdialog.h"
#include "ui_dicomattributesdialog.h"

#include "seriesinfo.h"
#include "logger.h"

#include <gdcmUIDGenerator.h>

#include <QStringList>

static QStringList sexes = {"Male", "Female", "Unspecified"};
static QStringList modalities = { "CR", "CT", "DX", "ES", "MG", "MR", "NM",
                                  "OT", "PT", "RF", "SC", "US", "XA"};
static QStringList positions = {"HFP", "HFS", "HFDR", "HFDL", "FFDR",
                                "FFDL", "FFP", "FFS"};

DicomAttributesDialog::DicomAttributesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DicomAttributesDialog),
    seriesInfo(SeriesInfo::getInstance()),
    logger(Logger::getInstance(std::string(LOGGER_NAME) + ".SeriesInfo"))
{
    ui->setupUi(this);

    ui->patientsSexComboBox->addItems(sexes);
    ui->studyModalityComboBox->addItems(modalities);
    ui->seriesPatientPositionComboBox->addItems(positions);  // HFP

    connect(ui->studyDateTimeNowPushButton, SIGNAL(clicked()), this, SLOT(handleStudyDateNowButtonClicked()));
    connect(ui->studyInstanceUIDGeneratePushButton, SIGNAL(clicked()), this, SLOT(handleStudyUIDGenerateButtonClicked()));
}

DicomAttributesDialog::~DicomAttributesDialog()
{
    delete ui;
}

//////////////////////////////////////////////////////////////////////

void DicomAttributesDialog::loadData()
{
    // Patient tab
    ui->patientsNameLineEdit->setText(seriesInfo->patientsName());
    ui->patientsIDLineEdit->setText(seriesInfo->patientsID());
    ui->patientsDOBDateEdit->setDate(seriesInfo->patientsDOB());

    int idx = sexes.indexOf(seriesInfo->patientsSex());
    ui->patientsSexComboBox->setCurrentIndex(idx);
    LOG4CPLUS_DEBUG(logger, "Patient's sex set to " << ui->patientsSexComboBox->currentText().toStdString());

    //Study tab
    idx = modalities.indexOf(seriesInfo->studyModality());
    ui->studyModalityComboBox->setCurrentIndex(idx);
    LOG4CPLUS_DEBUG(logger, "Modality set to " << ui->studyModalityComboBox->currentText().toStdString());

    ui->studyDescriptionLineEdit->setText(seriesInfo->studyDescription());
    ui->studyIDLineEdit->setText(seriesInfo->studyID());
    ui->studyDateTimeDateTimeEdit->setDateTime(seriesInfo->studyDateTime());
    ui->studyInstanceUIDLineEdit->setText(seriesInfo->studyStudyUID());

    // Series tab
    idx = positions.indexOf(seriesInfo->seriesPositionPatient());
    ui->seriesPatientPositionComboBox->setCurrentIndex(idx);
    LOG4CPLUS_DEBUG(logger, "Position set to " << ui->seriesPatientPositionComboBox->currentText().toStdString());

    ui->seriesDescriptionLineEdit->setText(seriesInfo->seriesDescription());
    ui->seriesNumberLineEdit->setText(seriesInfo->seriesNumber());
    ui->seriesTimeIncrementLineEdit->setText(QString::number(seriesInfo->seriesTimeIncrement()));

    // Image tab
    ui->numberOfImagesLineEdit->setText(QString::number(seriesInfo->imageNumberOfImages()));

    /* We need to set up the slices per image combobox.
     * It is possible that a series of slices may be either single 2D images
     * or slices of fewer 3D images. This code finds the list of exact divisors
     * for the number of slices so that the DICOM images cam be written
     * out properly.
     */
    int sliceCount = seriesInfo->imageNumberOfSlices();
    QStringList countList;
    for (int idx = 1; idx <= sliceCount; ++idx)
        if ((sliceCount % idx) == 0)
            countList.append(QString::number(idx));
    int index = countList.indexOf(QString::number(seriesInfo->imageSlicesPerImage()));
    if (index == -1)
        index = 0;
    ui->imageSlicesPerImageComboBox->clear();
    ui->imageSlicesPerImageComboBox->addItems(countList);
    ui->imageSlicesPerImageComboBox->setCurrentIndex(index);

    ui->imageSliceSpacingLineEdit->setText(QString::number(seriesInfo->imageSliceSpacing()));
    ui->imagePatientsPositionXLineEdit->setText(QString::number(seriesInfo->imagePositionPatientX()));
    ui->imagePatientsPositionYLineEdit->setText(QString::number(seriesInfo->imagePositionPatientY()));
    ui->imagePatientsPositionZLineEdit->setText(QString::number(seriesInfo->imagePositionPatientZ()));
    ui->imagePatientOrientationLineEdit->setText(seriesInfo->imagePatientOrientation());

}

void DicomAttributesDialog::storeData()
{
    // Patient tab
    seriesInfo->setPatientsName(ui->patientsNameLineEdit->text());
    seriesInfo->setPatientsID(ui->patientsIDLineEdit->text());
    seriesInfo->setPatientsDOB(ui->patientsDOBDateEdit->date());
    seriesInfo->setPatientsSex(ui->patientsSexComboBox->currentText());

    //Study tab
    seriesInfo->setStudyDescription(ui->studyDescriptionLineEdit->text());
    seriesInfo->setStudyModality(ui->studyModalityComboBox->currentText());
    seriesInfo->setStudyID(ui->studyIDLineEdit->text());
    seriesInfo->setStudyDateTime(ui->studyDateTimeDateTimeEdit->dateTime());
    seriesInfo->setStudyStudyUID(ui->studyInstanceUIDLineEdit->text());

    // Series tab
    seriesInfo->setSeriesDescription(ui->seriesDescriptionLineEdit->text());
    seriesInfo->setSeriesPositionPatient(ui->seriesPatientPositionComboBox->currentText());
    seriesInfo->setSeriesNumber(ui->seriesNumberLineEdit->text());
    seriesInfo->setSeriesTimeIncrement(ui->seriesTimeIncrementLineEdit->text().toInt());

    // Image tab
    seriesInfo->setNumberOfImages(ui->numberOfImagesLineEdit->text().toInt());
    seriesInfo->setSeriesSlicesPerImage(ui->imageSlicesPerImageComboBox->currentText().toInt());
    seriesInfo->setImageSliceSpacing(ui->imageSliceSpacingLineEdit->text().toInt());
    seriesInfo->setImagePositionPatientX(ui->imagePatientsPositionXLineEdit->text().toDouble());
    seriesInfo->setImagePositionPatientY(ui->imagePatientsPositionYLineEdit->text().toDouble());
    seriesInfo->setImagePositionPatientZ(ui->imagePatientsPositionZLineEdit->text().toDouble());
    seriesInfo->setImagePatientOrientation(ui->imagePatientOrientationLineEdit->text());
}

void DicomAttributesDialog::handleImageAxialPushButtonClicked()
{
    seriesInfo->setImagePatientOrientation("1\\0\\0\\0\\1\\0");
    ui->imagePatientOrientationLineEdit->setText("1\\0\\0\\0\\1\\0");
}

void DicomAttributesDialog::handleImageSaggitalPushButtonClicked()
{
    seriesInfo->setImagePatientOrientation("0\\1\\0\\0\\0\\1");
    ui->imagePatientOrientationLineEdit->setText("0\\1\\0\\0\\0\\1");
}

void DicomAttributesDialog::handleImageCoronalPushButtonClicked()
{
    seriesInfo->setImagePatientOrientation("1\\0\\0\\0\\0\\1");
    ui->imagePatientOrientationLineEdit->setText("1\\0\\0\\0\\0\\1");
}

void DicomAttributesDialog::handleStudyDateNowButtonClicked()
{
    seriesInfo->setStudyDateTime(QDateTime::currentDateTime());
    ui->studyDateTimeDateTimeEdit->setDateTime(seriesInfo->studyDateTime());

    LOG4CPLUS_DEBUG(logger, "handleStudyDateNowButtonClicked: "
                    << seriesInfo->studyDateTimeStr().toStdString());
}

void DicomAttributesDialog::handleStudyUIDGenerateButtonClicked()
{
    gdcm::UIDGenerator suid;
    QString studyUID = suid.Generate();
    seriesInfo->setStudyStudyUID(studyUID);
    ui->studyInstanceUIDLineEdit->setText(studyUID);

    LOG4CPLUS_DEBUG(logger, "handleStudyUIDGenerateButtonClicked: "
                    << seriesInfo->studyStudyUID().toStdString());
}

void DicomAttributesDialog::handlePatientsDOBDateEditChanged(const QDate &datetime)
{
    seriesInfo->setPatientsDOB(datetime);

    LOG4CPLUS_DEBUG(logger, "handlePatientsDOBDateEditChanged: "
                    << seriesInfo->patientsDOBStr().toStdString());
}

void DicomAttributesDialog::handleStudyDateTimeDateTimeEditChanged(const QDateTime& dateTime)
{
    seriesInfo->setStudyDateTime(dateTime);

    LOG4CPLUS_DEBUG(logger, "handlestudyDateTimeDateTimeEditChanged: "
                    << seriesInfo->studyDateTimeStr().toStdString());
}

void DicomAttributesDialog::handlePatientsSexComboBoxIndexChanged(int idx)
{
    seriesInfo->setPatientsSex(sexes[idx]);

    LOG4CPLUS_DEBUG(logger, "handlePatientsSexComboBoxIndexChanged: "
                    << seriesInfo->patientsSex().toStdString());
}

void DicomAttributesDialog::handleStudyModalityComboBoxIndexChanged(int idx)
{
    seriesInfo->setStudyModality(modalities[idx]);

    LOG4CPLUS_DEBUG(logger, "handleStudyModalityComboBoxIndexChanged: "
                    << seriesInfo->studyModality().toStdString());
}

void DicomAttributesDialog::handleSeriesPatientPositionComboBoxActivated(int idx)
{
    seriesInfo->setSeriesPositionPatient(positions[idx]);

    LOG4CPLUS_DEBUG(logger, "handleStudyModalityComboBoxIndexChanged: "
                    << seriesInfo->seriesPositionPatient().toStdString());
}

void DicomAttributesDialog::handleImageSlicesPerImageComboBoxActivated(int idx)
{
    bool ok;
    seriesInfo->setSeriesSlicesPerImage(ui->imageSlicesPerImageComboBox->itemText(idx).toInt(&ok));

    LOG4CPLUS_DEBUG(logger, "handleStudyModalityComboBoxIndexChanged: "
                    << seriesInfo->seriesPositionPatient().toStdString());
}














