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
    //ui->patientsSexComboBox->setCurrentIndex(2);             // Unspecified
    ui->studyModalityComboBox->addItems(modalities);
    //ui->seriesPatientPositionComboBox->addItems(positions);  // HFP
    ui->seriesPatientPositionComboBox->setCurrentIndex(1);

}

DicomAttributesDialog::~DicomAttributesDialog()
{
    delete ui;
}

//////////////////////////////////////////////////////////////////////

void DicomAttributesDialog::loadData(const SeriesInfo& info)
{
    // Patient tab
    ui->patientsNameLineEdit->setText(info.patientsName());
    ui->patientsIDLineEdit->setText(info.patientsID());
    ui->patientsDOBDateEdit->setDate(info.patientsDOB());

    int idx = sexes.indexOf(info.patientsSex());
    ui->patientsSexComboBox->setCurrentIndex(idx);
    LOG4CPLUS_DEBUG(logger, "Patient's sex set to " << ui->patientsSexComboBox->currentText().toStdString());

    //Study tab
    idx = modalities.indexOf(info.studyModality());
    ui->studyModalityComboBox->setCurrentIndex(idx);
    LOG4CPLUS_DEBUG(logger, "Modality set to " << ui->studyModalityComboBox->currentText().toStdString());

    ui->studyDescriptionTextEdit->setPlainText(info.studyDescription());
    ui->studyIDLineEdit->setText(info.studyID());
    ui->studyDateTimeDDateTimeEdit->setDateTime(info.studyDateTime());
    ui->studyInstanceUIDLineEdit->setText(info.studyStudyUID());

    // Series tab
    idx = positions.indexOf(info.seriesPositionPatient());
    ui->seriesPatientPositionComboBox->setCurrentIndex(idx);
    LOG4CPLUS_DEBUG(logger, "Position set to " << ui->seriesPatientPositionComboBox->currentText().toStdString());

    ui->seriesDescriptionTextEdit->setPlainText(info.seriesDescription());
    ui->seriesNumberLineEdit->setText(info.seriesNumber());
    ui->seriesTimeIncrementLineEdit->setText(QString::number(info.seriesTimeIncrement()));

    // Image tab
    ui->numberOfImagesLineEdit->setText(QString::number(info.imageNumberOfImages()));

    int sliceCount = info.imageNumberOfSlices();
    QStringList countList;
    for (int idx = 1; idx <= sliceCount; ++idx)
        countList.append(QString::number(idx));
    ui->imageSlicesPerImageComboBox->addItems(countList);

    ui->imageSliceSpacingLineEdit->setText(QString::number(info.imageSliceSpacing()));
    ui->imagePatientsPositionXLineEdit->setText(QString::number(info.imagePositionPatientX()));
    ui->imagePatientsPositionYLineEdit->setText(QString::number(info.imagePositionPatientY()));
    ui->imagePatientsPositionZLineEdit->setText(QString::number(info.imagePositionPatientZ()));
    ui->imagePatientOrientationLineEdit->setText(info.imagePatientOrientation());

}

void DicomAttributesDialog::storeData(SeriesInfo& info)
{
    // Patient tab
    info.setPatientsName(ui->patientsNameLineEdit->text());
    info.setPatientsID(ui->patientsIDLineEdit->text());
    info.setPatientsDOB(ui->patientsDOBDateEdit->date());
    info.setPatientsSex(ui->patientsSexComboBox->currentText());

    //Study tab
    info.setStudyModality(ui->studyModalityComboBox->currentText());

    info.setSeriesTimeIncrement(ui->studyDescriptionTextEdit->toPlainText().toInt());
    info.setStudyID(ui->studyIDLineEdit->text());
    info.setStudyDateTime(ui->studyDateTimeDDateTimeEdit->dateTime());
    info.setStudyStudyUID(ui->studyInstanceUIDLineEdit->text());

    // Series tab
    info.setSeriesPositionPatient(ui->seriesPatientPositionComboBox->currentText());
    info.setSeriesDescription(ui->seriesDescriptionTextEdit->toPlainText());
    info.setSeriesNumber(ui->seriesNumberLineEdit->text());
    info.setSeriesTimeIncrement(ui->seriesTimeIncrementLineEdit->text().toInt());

    // Image tab
    info.setNumberOfImages(ui->numberOfImagesLineEdit->text().toInt());
    info.setSeriesSlicesPerImage(ui->imageSlicesPerImageComboBox->currentText().toInt());
    info.setImageSliceSpacing(ui->imageSliceSpacingLineEdit->text().toInt());
    info.setImagePositionPatientX(ui->imagePatientsPositionXLineEdit->text().toDouble());
    info.setImagePositionPatientY(ui->imagePatientsPositionYLineEdit->text().toDouble());
    info.setImagePositionPatientZ(ui->imagePatientsPositionZLineEdit->text().toDouble());
    info.setImagePatientOrientation(ui->imagePatientOrientationLineEdit->text());
}

void DicomAttributesDialog::handleImageAxialPushButtonClicked()
{
    seriesInfo.setImagePatientOrientation("1\\0\\0\\0\\1\\0");
    ui->imagePatientOrientationLineEdit->setText("1\\0\\0\\0\\1\\0");
}

void DicomAttributesDialog::handleImageSaggitalPushButtonClicked()
{
    seriesInfo.setImagePatientOrientation("0\\1\\0\\0\\0\\1");
    ui->imagePatientOrientationLineEdit->setText("0\\1\\0\\0\\0\\1");
}

void DicomAttributesDialog::handleImageCoronalPushButtonClicked()
{
    seriesInfo.setImagePatientOrientation("1\\0\\0\\0\\0\\1");
    ui->imagePatientOrientationLineEdit->setText("1\\0\\0\\0\\0\\1");
}

void DicomAttributesDialog::handleStudyDateNowButtonClicked()
{
    seriesInfo.setStudyDateTime(QDateTime::currentDateTime());
    ui->studyDateTimeDDateTimeEdit->setDateTime(seriesInfo.studyDateTime());

    LOG4CPLUS_DEBUG(logger, "handleStudyDateNowButtonClicked: "
                    << seriesInfo.studyDateTimeStr().toStdString());
}

void DicomAttributesDialog::handleStudyUIDGenerateButtonClicked()
{
    gdcm::UIDGenerator suid;
    QString studyUID = suid.Generate();
    seriesInfo.setStudyStudyUID(studyUID);
    ui->studyInstanceUIDLineEdit->setText(studyUID);

    LOG4CPLUS_DEBUG(logger, "handleStudyUIDGenerateButtonClicked: "
                    << seriesInfo.studyStudyUID().toStdString());
}


















