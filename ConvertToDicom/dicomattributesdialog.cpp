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

#include <limits>

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

    // We load up the read only comboboxes.
    ui->patientSexComboBox->addItems(sexes);
    ui->studyModalityComboBox->addItems(modalities);
    ui->seriesPatientPositionComboBox->addItems(positions);

    // Set validators and masks to enforce input restrictions.
    QIntValidator intValidator(std::numeric_limits<int>::max(), std::numeric_limits<int>::min(), this);
    ui->seriesNumberLineEdit->setValidator(&intValidator);
    ui->seriesNumberLineEdit->setInputMask("#900000000");

    QRegExpValidator floatValidator(QRegExp("^[-+]?[0-9]+[.]?[0-9]*([eE][-+]?[0-9]+)?$"));
    ui->seriesTimeIncrementLineEdit->setValidator(&floatValidator);
    ui->imagePatientPositionXLineEdit->setValidator(&floatValidator);
    ui->imagePatientPositionYLineEdit->setValidator(&floatValidator);
    ui->imagePatientPositionZLineEdit->setValidator(&floatValidator);

    // Connections to local handlers.
    connect(ui->patientNameLineEdit, SIGNAL(clicked()), this, SLOT(handlePatientNameLineEditEditingFinished()));
    connect(ui->patientIDLineEdit, SIGNAL(clicked()), this, SLOT(handlePatientIDLineEditEditingFinished()));
    connect(ui->patientDOBDateEdit, SIGNAL(dateChanged(const QDate&)), this, SLOT(handlePatientDOBDateEditChanged(const QDate &)));
    connect(ui->patientSexComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handlePatientSexComboBoxIndexChanged(int)));

    connect(ui->studyDescriptionLineEdit, SIGNAL(editingFinished()), this, SLOT(handleStudyDescriptionLineEditEditingFinished()));
    connect(ui->studyIDLineEdit, SIGNAL(editingFinished()), this, SLOT(handleStudyIDLineEditEditingFinished()));
    connect(ui->studyModalityComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleStudyModalityComboBoxIndexChanged(int)));
    connect(ui->studyDateTimeDateTimeEdit, SIGNAL(dateChanged(const QDate&)), this, SLOT(void handleStudyDateTimeDateTimeEditChanged(const QDateTime &)));
    connect(ui->studyInstanceUIDLineEdit, SIGNAL(editingFinished()), this, SLOT(handleStudyInstanceUIDLineEditEditingFinished()));
    connect(ui->studyDateTimeNowPushButton, SIGNAL(clicked()), this, SLOT(handleStudyDateNowButtonClicked()));
    connect(ui->studyInstanceUIDGeneratePushButton, SIGNAL(clicked()), this, SLOT(handleStudyUIDGenerateButtonClicked()));

    connect(ui->seriesDescriptionLineEdit, SIGNAL(editingFinished()), this, SLOT(handleSeriesDescriptionLineEditEditingFinished()));
    connect(ui->seriesPatientPositionComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleStudyPatientPositionComboBoxIndexChanged(int)));
    connect(ui->seriesNumberLineEdit, SIGNAL(editingFinished()), this, SLOT(handleSeriesNumberLineEditEditingFinished()));
    connect(ui->seriesTimeIncrementLineEdit, SIGNAL(editingFinished()), this, SLOT(handleSeriesTimeIncrementLineEditEditingFinished()));

    connect(ui->imageSlicesPerImageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleImageSlicesPerImageComboBoxIndexChanged(int)));
    connect(ui->imageSliceSpacingLineEdit, SIGNAL(editingFinished()), this, SLOT(handleImageSliceSpacingLineEditEditingFinished()));
    connect(ui->imagePatientPositionXLineEdit, SIGNAL(editingFinished()), this, SLOT(handleImagePatientPositionXLineEditEditingFinished()));
    connect(ui->imagePatientPositionYLineEdit, SIGNAL(editingFinished()), this, SLOT(handleImagePatientPositionYLineEditEditingFinished()));
    connect(ui->imagePatientPositionZLineEdit, SIGNAL(editingFinished()), this, SLOT(handleImagePatientPositionZLineEditEditingFinished()));
    connect(ui->imagePatientOrientationLineEdit, SIGNAL(editingFinished()), this, SLOT(handleImagePatientOrientationLineEditEditingFinished()));
    connect(ui->imageAxialPushButton, SIGNAL(clicked()), this, SLOT(handleImageAxialPushButtonClicked()));
    connect(ui->imageSaggitalPushButton, SIGNAL(clicked()), this, SLOT(handleImageSaggitalPushButtonClicked()));
    connect(ui->imageCoronalPushButton, SIGNAL(clicked()), this, SLOT(handleImageCoronalPushButtonClicked()));
}

DicomAttributesDialog::~DicomAttributesDialog()
{
    delete ui;
}

//////////////////////////////////////////////////////////////////////

void DicomAttributesDialog::loadData()
{
    // Patient tab
    ui->patientNameLineEdit->setText(seriesInfo->patientName());
    ui->patientIDLineEdit->setText(seriesInfo->patientID());
    ui->patientDOBDateEdit->setDate(seriesInfo->patientDOB());

    int idx = sexes.indexOf(seriesInfo->patientSex());
    ui->patientSexComboBox->setCurrentIndex(idx);
    LOG4CPLUS_DEBUG(logger, "Patient's sex set to " << ui->patientSexComboBox->currentText().toStdString());

    //Study tab
    idx = modalities.indexOf(seriesInfo->studyModality());
    ui->studyModalityComboBox->setCurrentIndex(idx);
    LOG4CPLUS_DEBUG(logger, "Modality set to " << ui->studyModalityComboBox->currentText().toStdString());

    ui->studyDescriptionLineEdit->setText(seriesInfo->studyDescription());
    ui->studyIDLineEdit->setText(seriesInfo->studyID());
    ui->studyDateTimeDateTimeEdit->setDateTime(seriesInfo->studyDateTime());
    ui->studyInstanceUIDLineEdit->setText(seriesInfo->studyInstanceUID());

    // Series tab
    idx = positions.indexOf(seriesInfo->seriesPositionPatient());
    ui->seriesPatientPositionComboBox->setCurrentIndex(idx);
    LOG4CPLUS_DEBUG(logger, "Position set to " << ui->seriesPatientPositionComboBox->currentText().toStdString());

    ui->seriesDescriptionLineEdit->setText(seriesInfo->seriesDescription());
    ui->seriesNumberLineEdit->setText(seriesInfo->seriesNumberStr());
    ui->seriesTimeIncrementLineEdit->setText(seriesInfo->seriesTimeIncrementStr());

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
    ui->imagePatientPositionXLineEdit->setText(QString::number(seriesInfo->imagePositionPatientX()));
    ui->imagePatientPositionYLineEdit->setText(QString::number(seriesInfo->imagePositionPatientY()));
    ui->imagePatientPositionZLineEdit->setText(QString::number(seriesInfo->imagePositionPatientZ()));
    ui->imagePatientOrientationLineEdit->setText(seriesInfo->imagePatientOrientation());

}

void DicomAttributesDialog::storeData()
{
    // Patient tab
    seriesInfo->setPatientName(ui->patientNameLineEdit->text());
    seriesInfo->setPatientID(ui->patientIDLineEdit->text());
    seriesInfo->setPatientDOB(ui->patientDOBDateEdit->date());
    seriesInfo->setPatientSex(ui->patientSexComboBox->currentText());

    //Study tab
    seriesInfo->setStudyDescription(ui->studyDescriptionLineEdit->text());
    seriesInfo->setStudyModality(ui->studyModalityComboBox->currentText());
    seriesInfo->setStudyID(ui->studyIDLineEdit->text());
    seriesInfo->setStudyDateTime(ui->studyDateTimeDateTimeEdit->dateTime());
    seriesInfo->setStudyInstanceUID(ui->studyInstanceUIDLineEdit->text());

    // Series tab
    seriesInfo->setSeriesDescription(ui->seriesDescriptionLineEdit->text());
    seriesInfo->setSeriesPositionPatient(ui->seriesPatientPositionComboBox->currentText());
    seriesInfo->setSeriesNumber(ui->seriesNumberLineEdit->text());
    seriesInfo->setSeriesTimeIncrement(ui->seriesTimeIncrementLineEdit->text().toDouble());

    // Image tab
    seriesInfo->setImageNumberOfImages(ui->numberOfImagesLineEdit->text().toInt());
    seriesInfo->setSeriesSlicesPerImage(ui->imageSlicesPerImageComboBox->currentText().toInt());
    seriesInfo->setImageSliceSpacing(ui->imageSliceSpacingLineEdit->text().toInt());
    seriesInfo->setImagePositionPatientX(ui->imagePatientPositionXLineEdit->text().toDouble());
    seriesInfo->setImagePositionPatientY(ui->imagePatientPositionYLineEdit->text().toDouble());
    seriesInfo->setImagePositionPatientZ(ui->imagePatientPositionZLineEdit->text().toDouble());
    seriesInfo->setImagePatientOrientation(ui->imagePatientOrientationLineEdit->text());
}

void DicomAttributesDialog::handlePatientNameLineEditEditingFinished()
{
    seriesInfo->setPatientName(ui->patientNameLineEdit->text());
}

void DicomAttributesDialog::handlePatientIDLineEditEditingFinished()
{
    seriesInfo->setPatientID(ui->patientIDLineEdit->text());
}

void DicomAttributesDialog::handlePatientDOBDateEditChanged(const QDate &datetime)
{
    seriesInfo->setPatientDOB(datetime);

    LOG4CPLUS_DEBUG(logger, "handlePatientDOBDateEditChanged: "
                    << seriesInfo->patientDOBStr().toStdString());
}

void DicomAttributesDialog::handlePatientSexComboBoxIndexChanged(int idx)
{
    seriesInfo->setPatientSex(sexes[idx]);

    LOG4CPLUS_DEBUG(logger, "handlePatientSexComboBoxIndexChanged: "
                    << seriesInfo->patientSex().toStdString());
}

void DicomAttributesDialog::handleStudyDescriptionLineEditEditingFinished()
{
    seriesInfo->setStudyDescription(ui->studyDescriptionLineEdit->text());
}

void DicomAttributesDialog::handleStudyIDLineEditEditingFinished()
{
    seriesInfo->setStudyID(ui->studyIDLineEdit->text());
}

void DicomAttributesDialog::handleStudyModalityComboBoxIndexChanged(int idx)
{
    seriesInfo->setStudyModality(modalities[idx]);

    LOG4CPLUS_DEBUG(logger, "handleStudyModalityComboBoxIndexChanged: "
                    << seriesInfo->studyModality().toStdString());
}

void DicomAttributesDialog::handleStudyInstanceUIDLineEditEditingFinished()
{
    seriesInfo->setStudyInstanceUID(ui->studyInstanceUIDGeneratePushButton->text());
}

void DicomAttributesDialog::handleStudyDateTimeDateTimeEditChanged(const QDateTime& dateTime)
{
    seriesInfo->setStudyDateTime(dateTime);

    LOG4CPLUS_DEBUG(logger, "handlestudyDateTimeDateTimeEditChanged: "
                    << seriesInfo->studyDateTimeStr().toStdString());
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
    seriesInfo->setStudyInstanceUID(studyUID);
    ui->studyInstanceUIDLineEdit->setText(studyUID);

    LOG4CPLUS_DEBUG(logger, "handleStudyUIDGenerateButtonClicked: "
                    << seriesInfo->studyInstanceUID().toStdString());
}

void DicomAttributesDialog::handleSeriesDescriptionLineEditEditingFinished()
{
    seriesInfo->setSeriesDescription(ui->seriesDescriptionLineEdit->text());
}

void DicomAttributesDialog::handleSeriesPatientPositionComboBoxActivated(int idx)
{
    seriesInfo->setSeriesPositionPatient(positions[idx]);

    LOG4CPLUS_DEBUG(logger, "handleStudyModalityComboBoxIndexChanged: "
                    << seriesInfo->seriesPositionPatient().toStdString());
}

void DicomAttributesDialog::handleSeriesNumberLineEditEditingFinished()
{
    seriesInfo->setSeriesNumber(ui->seriesNumberLineEdit->text());
}

void DicomAttributesDialog::handleSeriesTimeIncrementLineEditEditingFinished()
{
    seriesInfo->setSeriesTimeIncrement(ui->seriesTimeIncrementLineEdit->text().toDouble());
}

void DicomAttributesDialog::handleImageSlicesPerImageComboBoxIndexChanged(int idx)
{
    bool ok;
    seriesInfo->setSeriesSlicesPerImage(ui->imageSlicesPerImageComboBox->itemText(idx).toInt(&ok));
    seriesInfo->setImageNumberOfImages(seriesInfo->imageNumberOfSlices() / seriesInfo->imageSlicesPerImage());

    ui->numberOfImagesLineEdit->setText(QString::number(seriesInfo->imageNumberOfImages()));

    LOG4CPLUS_DEBUG(logger, "handleStudyModalityComboBoxIndexChanged: "
                    << seriesInfo->seriesPositionPatient().toStdString());
}

void DicomAttributesDialog::handleImageSliceSpacingLineEditEditingFinished()
{
    seriesInfo->setImageSliceSpacing(ui->imageSliceSpacingLineEdit->text().toDouble());
}

void DicomAttributesDialog::handleImagePatientPositionXLineEditEditingFinished()
{
    seriesInfo->setImagePositionPatientX(ui->imagePatientPositionXLineEdit->text().toDouble());
}

void DicomAttributesDialog::handleImagePatientPositionYLineEditEditingFinished()
{
    seriesInfo->setImagePositionPatientY(ui->imagePatientPositionYLineEdit->text().toDouble());
}

void DicomAttributesDialog::handleImagePatientPositionZLineEditEditingFinished()
{
    seriesInfo->setImagePositionPatientZ(ui->imagePatientPositionZLineEdit->text().toDouble());
}

void DicomAttributesDialog::handleImagePatientOrientationLineEditEditingFinished()
{
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














