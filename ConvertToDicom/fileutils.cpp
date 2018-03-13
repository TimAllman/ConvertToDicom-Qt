//
//  fileutils.cpp
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
#include "fileutils.h"
#include "imageinfo.h"

#include "itkheaders.pch.h"

#include <QDir>

FileUtils::FileUtils()
    : logger(log4cplus::Logger::getInstance(std::string(LOGGER_NAME) + ".FileUtils"))
{

}

ErrorCode FileUtils::getImageFileNames(const QString& dirPath, QStringList& fileNames)
{
    LOG4CPLUS_TRACE(logger, "Enter");

    // Assume the array is not empty and empty it
    fileNames.clear();

    QDir inputDir(dirPath);

    QStringList fNames = inputDir.entryList(QDir::Files | QDir::Readable, QDir::Name);

    // we have to prepend the directory path to the file names
    int len = fNames.length();
    for (int idx = 0; idx < len; ++idx)
    {
        QString path = inputDir.absolutePath() + "/" + fNames[idx];
        LOG4CPLUS_DEBUG(logger, fNames[idx].toStdString());
        fileNames.append(path);
    }

    LOG4CPLUS_INFO(logger, "Reading " << fileNames.length() << " file names from directory: "
                   << inputDir.absolutePath().toStdString());

    if (fileNames.isEmpty())
        return ErrorCode::ERROR_FILE_NOT_FOUND;
    else
        return ErrorCode::SUCCESS;
}

ErrorCode FileUtils::getImageInfo(const QString& inputDirPath, ImageInfo& info)
{
    LOG4CPLUS_TRACE(logger, "Enter");

    info.init();
    QDir inputDir(inputDirPath);

    //std::string inDir = inputDir.path().toStdString();
    QStringList fileNames;

    // Take the information we need from the first image
    ErrorCode errCode = getImageFileNames(inputDirPath, fileNames);
    if (errCode != ErrorCode::SUCCESS)
    {
        LOG4CPLUS_ERROR(logger, "Could not find files in " << inputDirPath.toStdString());
        return errCode;
    }

    std::string firstFileName(fileNames[0].toStdString());
    itk::ImageIOBase::Pointer imageIO =
        itk::ImageIOFactory::CreateImageIO(firstFileName.c_str(), itk::ImageIOFactory::ReadMode);

    // If there is a problem, catch it
    if (imageIO.IsNull())
    {
        LOG4CPLUS_ERROR(logger, "Could not get metadata from file: " << firstFileName);
        return ErrorCode::ERROR;
    };

    imageIO->SetFileName(firstFileName);
    imageIO->ReadImageInformation();

    std::string nameOfClass = imageIO->GetNameOfClass();
    info.setImageTypeName(nameOfClass);
    LOG4CPLUS_DEBUG(logger, "ImageIO class name = " << imageIO->GetNameOfClass());

    //    if (std::string(imageIO->GetNameOfClass()) == std::string("GDCMImageIO"))
    //    {

    //        itk::GDCMImageIO::Pointer& p = reinterpret_cast<itk::GDCMImageIO::Pointer&>(imageIO);
    //        itk::MetaDataDictionary seriesDict = p->GetMetaDataDictionary();

    //    }

    // Get the number of dimensions.
    unsigned numDims = imageIO->GetNumberOfDimensions();
    info.setNumDims(numDims);
    LOG4CPLUS_DEBUG(logger, "dimensions = " << numDims);

    int numFiles = fileNames.length();

    for (unsigned int idx = 0; idx < numDims; ++idx)
    {
        info.setSpacing(idx, imageIO->GetSpacing(idx));
    }

    if (numDims == 3)
        info.setSlicesPerImage(int(imageIO->GetDimensions(2)));
    else
        info.setSlicesPerImage(1);

    info.setNumberOfSlices(numFiles * info.slicesPerImage());
    info.setNumberOfImages(numFiles / info.slicesPerImage());

    LOG4CPLUS_DEBUG(logger, "slicesPerImage = " << info.slicesPerImage());
    LOG4CPLUS_DEBUG(logger, "imageSliceSpacing = " << info.spacingStr());
    LOG4CPLUS_DEBUG(logger, "numberOfImages = " << info.numberOfImages());

    // use for creating strings below.
    std::ostringstream value;

    // Set the Image Orientation Patient attribute from the image direction info.
    std::vector<double> dir = imageIO->GetDirection(0);
    value << dir[0] << "\\" << dir[1] << "\\" << dir[2] << "\\";
    dir = imageIO->GetDirection(1);
    value << dir[0] << "\\" << dir[1] << "\\" << dir[2];
    std::string imageOrientationPatient = value.str();
    info.setImageOrientationPatient(imageOrientationPatient);

    LOG4CPLUS_DEBUG(logger, "imagePatientOrientation = " << info.imageOrientationPatient());

    return ErrorCode::SUCCESS;

}

bool FileUtils::isValidSourceDir(const QString& dirPath)
{
    LOG4CPLUS_DEBUG(logger, "Checking source dir validity: " << dirPath.toStdString());

    QDir dir(dirPath);
    bool exists = dir.exists();
    if (!exists)
    {
        LOG4CPLUS_DEBUG(logger, "    Directory does not exist.");
        return false;
    }

    bool empty = dir.isEmpty();
    if (empty)
    {
        LOG4CPLUS_DEBUG(logger, "    Directory is empty.");
        return false;
    }

    ImageInfo info;
    ErrorCode errCode = getImageInfo(dir.path(), info);
    if (errCode != ErrorCode::SUCCESS)
    {
        LOG4CPLUS_DEBUG(logger, "    Failed to extract image metadata.");
        return false;
    }

    LOG4CPLUS_DEBUG(logger, "    Directory valid.");
    return true;
}

