//
//  fileutils.h
//  ConvertToDicom
//

/* ConvertToDicom converts a series of images to DICOM format from any format recognized
 * by ITK (http://www.itk.org).
 * Copyright (C) 2018 Tim Allman
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
#ifndef FILEUTILS_H
#define FILEUTILS_H

#include "errorcodes.h"
#include "logger.h"

#include <QString>
#include <QStringList>

class ImageInfo;

class FileUtils
{
public:
    FileUtils();

    /**
     * Load all of the names within the input directory into <code>filenames</code>.
     * Assumes that these are all suitable image files.
     * @todo Be more selective so that returned file names are known to be image file names.
     * @param dirPath The full path of the directory containing the files.
     * @param filenames The file names found.
     * @return Suitable code in ErrorCode enum.
     */
    ErrorCode getImageFileNames(const QString& dirPath, QStringList& filenames);

    /**
     * Extract the information in an image or series. This is intended to be a read only operation
     * intended to support the preview widget in the GUI.
     * @param inputDirPath Path to the directory containing the image series.
     * @param Reference to an ImageInfo instance to fill with data.
     * @return A const reference to an `ImageInfo` instance
     */
    ErrorCode getImageInfo(const QString& inputDirPath, ImageInfo& info);

    /**
     * Determines whether a directory is a valid souurce directory.
     * @param dirPath The path of the directory.
     * @return true if we can use dirPath, false otherwise.
     */
    bool isValidSourceDir(const QString& dirPath);


private:
    QStringList filenames;
    Logger logger;           ///< Logger for this class.

};

#endif // FILEUTILS_H
