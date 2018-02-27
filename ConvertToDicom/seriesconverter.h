//
//  seriesconverter.h
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
#ifndef SERIESCONVERTER_H
#define SERIESCONVERTER_H

#include "errorcodes.h"
#include "logger.h"
#include "itktypedefs.h"

#include <QDir>
#include <QVector>

class SeriesInfo;
class ImageInfo;

/**
 * @brief The SeriesConverter class
 *
 * Class to do the conversion of one series.
 * It reads the image files, converts them to DICOM
 * and writes them out as DICOM files.
 */
class SeriesConverter
{
public:
    /**
     * @brief SeriesConverter
     * Constructor.
     */
    SeriesConverter();

    /**
     * Read the input files and write the DICOM files to the output directory. A directory tree is
     * formed like this: patientsName/studyDescription - studyID/seriesDescription - seriesNumber.
     * @return Suitable code in ErrorCode enum.
     */
    ErrorCode convertFiles();

    /**
     * Make the full output directory path. This is the directory into which the DICOM series will be placed.
     * @param dirName The output directory name that will be expanded by makeOutputPathName().
     * @return ErrorCode SUCCESS if successful,
     * ERROR_CREATING_DIRECTORY or ERROR_DIRECTORY_NOT_EMPTY if not.
     */
    ErrorCode makeFullOutputPathDir(const QString& dirName);

    /**
     * @brief setInputDir
     * @param dir The directory containing the files to be read.
     * Tells us where the files are.
     */
    void setInputDir(const QDir& dir)
    {
        inputDir = dir;
    }

    /**
     * Tries to get as many metadata from the input image files as possible. If the image is a DICOM
     * series the metadata dictionary will be queried. Otherwise the data will likely be limited to
     * dimensions and slice spacing. This must be called after readFiles().
     * @return Suitable code in ErrorCode enum.
     */
    ErrorCode extractImageParameters();

    /**
     * Extract the information in an image or series. This is a read only operation intended to
     * support the preview widget in the GUI.
     * @return A smart pointer to an `ImageInfo` instance
     */
    const std::auto_ptr<ImageInfo> imageInfo();

    /**
     * Determines whether a directory is a valid souurce directory.
     * @param dirPath The path of the directory.
     * @return true if we can use dirPath, false otherwise.
     */
    bool isValidSourceDir(const QString& dirPath);

private:
    /**
      * @brief loadFileNames
      * Load all of the names within the input directory. Assumes that these are all suitable
      * image files.
      * @return Suitable code in ErrorCode enum.
      */
    ErrorCode loadFileNames();

    /**
     * Create and store the acquisition times of the output files.
     */
    void createTimesArray();

    /**
     * Checks the consistency of the dimensionality of each image and number of slices.
     * @return SUCCESS if all is well.
     */
    ErrorCode inputImagesConsistent();

    /**
     * Make the full path directory name.
     * The files exist at the bottom of a tree that looks like this:
     * dirName/PatientName/StudyDescription - StudyID/SeriesDescription - SeriesNumber/.
     * @returns The path of the directory which will receive the DICOM series.
     */
    QString makeOutputPathName(const QString& dirName);

    /**
     * Read in all of the image files in the input directory. Must be called after loadFileNames().
     * @return Suitable code in ErrorCode enum.
     */
    ErrorCode readFiles();

    /**
     * Write the DICOM files to the output directory. A directory tree is formed like this:
     * patientsName/studyDescription - studyID/seriesDescription - seriesNumber.
     * return Suitable code in ErrorCode enum.
     */
    ErrorCode writeFiles();

    QStringList fileNames;     ///< The list of input file names.

    QDir inputDir;            ///< Where the input files are found.
    QDir outputDir;           ///< Where to put the output file tree.
    SeriesInfo* seriesInfo;   ///< Information about the series.

    QVector<Image2DType::Pointer> imageStack;

    Logger logger;           ///< Logger for this class.
};

#endif // SERIESCONVERTER_H
