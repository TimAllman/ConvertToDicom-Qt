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

#include <QDialog>

namespace Ui {
class DicomAttributesDialog;
}

class DicomAttributesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DicomAttributesDialog(QWidget *parent = 0);
    ~DicomAttributesDialog();

    /**
     * @brief getInstance
     * This returns the last created instance but there should be no more than one instance of a dialog.
     * This was done to allow the instance address to be available for signal and slot connections.
     * @return The last created instance.
     */
    static DicomAttributesDialog* getInstance()
    {
        return instance;
    }

private:
    Ui::DicomAttributesDialog *ui;

    static DicomAttributesDialog* instance;

};

#endif // DICOMATTRIBUTESDIALOG_H
