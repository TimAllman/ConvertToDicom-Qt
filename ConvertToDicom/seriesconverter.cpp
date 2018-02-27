//
//  seriesconverter.cpp
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
#include "seriesconverter.h"
#include "logger.h"
#include "imagereader.h"
#include "seriesinfo.h"
#include "dicomserieswriter.h"
#include "imageinfo.h"
#include "itkheaders.pch.h"

#include <vector>
#include <sstream>

#include <QDir>
#include <QStringList>

SeriesConverter::SeriesConverter()
    : seriesInfo(SeriesInfo::getInstance()),
      logger(log4cplus::Logger::getInstance(std::string(LOGGER_NAME) + ".SeriesConverter"))
{

}

ErrorCode SeriesConverter::convertFiles()
{
    inputDir = seriesInfo->inputDir();
    outputDir = seriesInfo->outputDir();

    /*
     * There are three steps here.
     *
     * 1) Get the names of the files in this directory.
     * 2) Read in the files and store them in memory as a series of slices
     * 3) Write out the images as a series of DICOM images.
     *
     * We fail if any step is not successful.
     */
    ErrorCode errCode = loadFileNames();
    if (errCode != ErrorCode::SUCCESS)
        return errCode;

    errCode = readFiles();
    if (errCode != ErrorCode::SUCCESS)
        return errCode;

    errCode = writeFiles();
    if (errCode != ErrorCode::SUCCESS)
        return errCode;

    return ErrorCode::SUCCESS;
}

ErrorCode SeriesConverter::makeFullOutputPathDir(const QString& dirName)
{
    QString pathName = makeOutputPathName(dirName);
    seriesInfo->setOutputPath(pathName);
    LOG4CPLUS_DEBUG(logger, "Output path: " << seriesInfo->outputPath().toStdString());

    QDir pathDir(pathName);
    bool success = pathDir.mkpath(pathName);

    if (!success)
    {
        return ErrorCode::ERROR_CREATING_DIRECTORY;
    }
    // See if the directory is empty
    else if(pathDir.entryList(QDir::Files).length() != 0)
    {
        return ErrorCode::ERROR_DIRECTORY_NOT_EMPTY;
    }
    else return ErrorCode::SUCCESS;
}

ErrorCode SeriesConverter::extractImageParameters()
{
    LOG4CPLUS_TRACE(logger, "Enter");

    // Take the information we need from the first image
    if (loadFileNames() == ErrorCode::ERROR_FILE_NOT_FOUND)
    {
        LOG4CPLUS_ERROR(logger, "Could not find files in " << seriesInfo->inputDir().path().toStdString());
        return ErrorCode::ERROR_FILE_NOT_FOUND;
    }

    std::string firstFileName(fileNames[0].toStdString());
    itk::ImageIOBase::Pointer imageIO =
        itk::ImageIOFactory::CreateImageIO(firstFileName.c_str(), itk::ImageIOFactory::ReadMode);

    // If there is a problem, catch it
    if (imageIO.IsNull())
    {
        LOG4CPLUS_ERROR(logger, "Could not get metadata from file: " << firstFileName);
        return ErrorCode::ERROR_READING_FILE;
    };

    imageIO->SetFileName(firstFileName);
    imageIO->ReadImageInformation();

    std::string nameOfClass = imageIO->GetNameOfClass();
    LOG4CPLUS_DEBUG(logger, "ImageIO class name = " << imageIO->GetNameOfClass());

    //    if (std::string(imageIO->GetNameOfClass()) == std::string("GDCMImageIO"))
    //    {

    //        itk::GDCMImageIO::Pointer& p = reinterpret_cast<itk::GDCMImageIO::Pointer&>(imageIO);
    //        itk::MetaDataDictionary seriesDict = p->GetMetaDataDictionary();

    //    }

    // Get the number of dimensions.
    unsigned numDims = imageIO->GetNumberOfDimensions();
    LOG4CPLUS_DEBUG(logger, "dimensions = " << numDims);

    int numFiles = fileNames.length();

    if (numDims == 3)
    {
        seriesInfo->setImageSlicesPerImage(int(imageIO->GetDimensions(2)));
        seriesInfo->setImageSliceSpacing(int(imageIO->GetSpacing(2)));
        seriesInfo->setSeriesNumberOfSlices(numFiles * seriesInfo->imageSlicesPerImage());
    }
    else
    {
        seriesInfo->setImageNumberOfImages(1);
        seriesInfo->setImageSlicesPerImage(1);
        // If we have a value use it, otherwise set to 1.0 mm
        if (seriesInfo->imageSliceSpacing() == 0.0)
            seriesInfo->setImageSliceSpacing(1.0);
        seriesInfo->setSeriesNumberOfSlices(numFiles);
    }

    seriesInfo->setImageNumberOfImages(numFiles / seriesInfo->imageSlicesPerImage());

    LOG4CPLUS_DEBUG(logger, "slicesPerImage = " << seriesInfo->imageSlicesPerImage());
    LOG4CPLUS_DEBUG(logger, "imageSliceSpacing = " << seriesInfo->imageSliceSpacing());
    LOG4CPLUS_DEBUG(logger, "numberOfImages = " << seriesInfo->imageNumberOfImages());

    // use for creating strings below.
    std::ostringstream value;

    // Set the Image Orientation Patient attribute from the image direction info.
    std::vector<double> dir = imageIO->GetDirection(0);
    value << dir[0] << "\\" << dir[1] << "\\" << dir[2] << "\\";
    dir = imageIO->GetDirection(1);
    value << dir[0] << "\\" << dir[1] << "\\" << dir[2];
    std::string imageOrientationPatient = value.str();
    seriesInfo->setImagePatientOrientation(imageOrientationPatient.c_str());

    LOG4CPLUS_DEBUG(logger, "imagePatientOrientation = "
                    << seriesInfo->imagePatientOrientation().toStdString());

    // Image Position Patient
    seriesInfo->setImagePositionPatientX(imageIO->GetOrigin(0));
    seriesInfo->setImagePositionPatientY(imageIO->GetOrigin(1));
    if (numDims == 3)
        seriesInfo->setImagePositionPatientZ(imageIO->GetOrigin(2));
    else
        seriesInfo->setImagePositionPatientZ(0.0);

    LOG4CPLUS_DEBUG(logger, "imagePatientPosition(X, Y, Z) = " << seriesInfo->imagePositionPatientX() << ", "
                    << seriesInfo->imagePositionPatientY() << ", " << seriesInfo->imagePositionPatientZ());

    return ErrorCode::SUCCESS;
}

const std::auto_ptr<ImageInfo> SeriesConverter::imageInfo()
{
    std::auto_ptr<ImageInfo> info(new ImageInfo);

    LOG4CPLUS_TRACE(logger, "Enter");

    // Take the information we need from the first image
    if (loadFileNames() == ErrorCode::ERROR_FILE_NOT_FOUND)
    {
        info.release();
        LOG4CPLUS_ERROR(logger, "Could not find files in " << seriesInfo->inputDir().path().toStdString());
        return info;
    }

    std::string firstFileName(fileNames[0].toStdString());
    itk::ImageIOBase::Pointer imageIO =
        itk::ImageIOFactory::CreateImageIO(firstFileName.c_str(), itk::ImageIOFactory::ReadMode);

    // If there is a problem, catch it
    if (imageIO.IsNull())
    {
        info.release();
        LOG4CPLUS_ERROR(logger, "Could not get metadata from file: " << firstFileName);
        return info;
    };

    imageIO->SetFileName(firstFileName);
    imageIO->ReadImageInformation();

    std::string nameOfClass = imageIO->GetNameOfClass();
    info->setImageTypeName(nameOfClass);
    LOG4CPLUS_DEBUG(logger, "ImageIO class name = " << imageIO->GetNameOfClass());

    //    if (std::string(imageIO->GetNameOfClass()) == std::string("GDCMImageIO"))
    //    {

    //        itk::GDCMImageIO::Pointer& p = reinterpret_cast<itk::GDCMImageIO::Pointer&>(imageIO);
    //        itk::MetaDataDictionary seriesDict = p->GetMetaDataDictionary();

    //    }

    // Get the number of dimensions.
    unsigned numDims = imageIO->GetNumberOfDimensions();
    info->setNumDims(numDims);
    LOG4CPLUS_DEBUG(logger, "dimensions = " << numDims);

    int numFiles = fileNames.length();

    for (unsigned int idx = 0; idx < numDims; ++idx)
    {
        info->setSpacing(idx, imageIO->GetSpacing(idx));
    }

    if (numDims == 3)
        info->setSlicesPerImage(int(imageIO->GetDimensions(2)));
    else
        info->setSlicesPerImage(1);

    info->setNumberOfSlices(numFiles * info->slicesPerImage());
    info->setNumberOfImages(numFiles / info->slicesPerImage());

    LOG4CPLUS_DEBUG(logger, "slicesPerImage = " << info->slicesPerImage());
    LOG4CPLUS_DEBUG(logger, "imageSliceSpacing = " << info->spacingStr());
    LOG4CPLUS_DEBUG(logger, "numberOfImages = " << info->numberOfImages());

    // use for creating strings below.
    std::ostringstream value;

    // Set the Image Orientation Patient attribute from the image direction info.
    std::vector<double> dir = imageIO->GetDirection(0);
    value << dir[0] << "\\" << dir[1] << "\\" << dir[2] << "\\";
    dir = imageIO->GetDirection(1);
    value << dir[0] << "\\" << dir[1] << "\\" << dir[2];
    std::string imageOrientationPatient = value.str();
    info->setImageOrientationPatient(imageOrientationPatient);

    LOG4CPLUS_DEBUG(logger, "imagePatientOrientation = " << info->imageOrientationPatient());

    return info;
}

bool SeriesConverter::isValidSourceDir(const QString& dirPath)
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

    inputDir = dirPath;

    //    ErrorCode errCode = loadFileNames();
    //    if (errCode != ErrorCode::SUCCESS)
    //    {
    //        LOG4CPLUS_DEBUG(logger, "    Failed to load file names.");
    //        return false;
    //    }

    ErrorCode errCode = extractImageParameters();
    if (errCode != ErrorCode::SUCCESS)
    {
        LOG4CPLUS_DEBUG(logger, "    Failed to extract image metadata.");
        return false;
    }

    LOG4CPLUS_DEBUG(logger, "    Directory valid.");
    return true;
}

ErrorCode SeriesConverter::loadFileNames()
{
    LOG4CPLUS_TRACE(logger, "Enter");

    // If the array is not empty, empty it
    fileNames.clear();

    QStringList fNames = inputDir.entryList(QDir::Files | QDir::Readable, QDir::Name);

    // we have to prepend the directory path to the file names
    int len = fNames.length();
    for (int idx = 0; idx < len; ++idx)
    {
        QString path = inputDir.absolutePath() + "/" + fNames[idx];
        LOG4CPLUS_DEBUG(logger, fNames[idx].toStdString());
        fileNames.append(path);
    }

    LOG4CPLUS_INFO(logger, "Loading " << fileNames.length() << " files from directory: "
                   << inputDir.absolutePath().toStdString());

    if (fileNames.isEmpty())
        return ErrorCode::ERROR_FILE_NOT_FOUND;
    else
        return ErrorCode::SUCCESS;
}

void SeriesConverter::createTimesArray()
{
    LOG4CPLUS_TRACE(logger, "Enter");

    // Here we create an array of DICOM acquisition times as time strings
    seriesInfo->acqTimes().clear();

    // Get the starting time (NSTimeinterval is a typedef for double)
    //    NSDateFormatter* df = [[NSDateFormatter alloc]init];
    //    [df setDateFormat:"HHmmss.SSS"];

    // We create a list of incremented times. We may need fewer than the number of slices of these
    // times but we will never need more. This saves modifying the list if we change the number
    // of slices per image later.
    QTime acqTime = seriesInfo->studyDateTime().time();
    double timeIncr = seriesInfo->seriesTimeIncrement();
    int numSlices = seriesInfo->imageNumberOfSlices();
    for (int sliceIdx = 0; sliceIdx < numSlices; ++sliceIdx)
    {
        seriesInfo->acqTimes().append(acqTime);
        acqTime = acqTime.addMSecs(int(std::round(timeIncr * 1000.0)));
    }

    std::stringstream stream;
    for (int idx = 0; idx < seriesInfo->acqTimes().length(); ++idx)
        stream << seriesInfo->acqTimes()[idx].toString(Qt::ISODateWithMs).toStdString() << "\n";
    LOG4CPLUS_DEBUG(logger, "acqTimes = " << stream.str());
}

ErrorCode SeriesConverter::inputImagesConsistent()
{
    // Get the image info from the first file
    std::string fileName = fileNames[0].toStdString();
    itk::ImageIOBase::Pointer imageIO =
            itk::ImageIOFactory::CreateImageIO(fileName.c_str(), itk::ImageIOFactory::ReadMode);

    // If there is a problem, catch it
    if (imageIO.IsNull())
    {
        LOG4CPLUS_ERROR(logger, "Could not get metadata from file: " << fileName.c_str());
        return ErrorCode::ERROR_READING_FILE;
    };


    imageIO->SetFileName(fileName);
    imageIO->ReadImageInformation();

    unsigned numDims_1 = imageIO->GetNumberOfDimensions();
    LOG4CPLUS_INFO(logger, "Input file number of dimensions = " << numDims_1);

    unsigned long dim0_1 = imageIO->GetDimensions(0);
    unsigned long dim1_1 = imageIO->GetDimensions(1);
    unsigned long dim2_1 = 0;
    if (numDims_1 == 2)
    {
        LOG4CPLUS_INFO(logger, "Input file dimensions = " << dim0_1 << ", " << dim1_1);
    }
    else // must be 3
    {
        dim2_1 = imageIO->GetDimensions(2);
        LOG4CPLUS_INFO(logger, "Input file dimensions = " << dim0_1 << ", " << dim1_1 << ", " << dim2_1);
    }

    for (int idx = 1; idx < fileNames.length(); ++idx)
    {
        std::string fileName = fileNames[idx].toStdString();

        imageIO->SetFileName(fileName);
        imageIO->ReadImageInformation();

        unsigned numDims = imageIO->GetNumberOfDimensions();
        if (numDims != numDims_1)
        {
            LOG4CPLUS_ERROR(logger, "File " << fileName.c_str()
                            << ": inconsistent number of dimension: " << numDims);
            return ErrorCode::ERROR_IMAGE_INCONSISTENT;
        }

        unsigned long dim0 = imageIO->GetDimensions(0);
        unsigned long dim1 = imageIO->GetDimensions(1);
        if (dim0 != dim0_1)
        {
            LOG4CPLUS_ERROR(logger, "File " <<  fileName.c_str()
                            << ": inconsistent dimension 0: %d" << dim0_1);
            return ErrorCode::ERROR_IMAGE_INCONSISTENT;
        }

        if (dim1 != dim1_1)
        {
            LOG4CPLUS_ERROR(logger, "File " <<  fileName.c_str()
                            << ": inconsistent dimension 1: %d" << dim1_1);
            return ErrorCode::ERROR_IMAGE_INCONSISTENT;
        }

        if (numDims_1 == 3)
        {
            unsigned long dim2 = imageIO->GetDimensions(2);
            if (dim2 != dim2_1)
            {
                LOG4CPLUS_ERROR(logger, "File " <<  fileName.c_str()
                                << ": inconsistent dimension 2: %d" << dim2_1);
                return ErrorCode::ERROR_IMAGE_INCONSISTENT;
            }
        }
    }

    return ErrorCode::SUCCESS;
}

QString SeriesConverter::makeOutputPathName(const QString& dirName)
{

    QString path = QString("%1/%2/%3 - %4/%5 - %6/")
                   .arg(dirName)
                   .arg(seriesInfo->patientName())
                   .arg(seriesInfo->studyDescription())
                   .arg(seriesInfo->studyID())
                   .arg(seriesInfo->seriesDescription())
                   .arg(seriesInfo->seriesNumber());

    return path;
}

ErrorCode SeriesConverter::readFiles()
{
    LOG4CPLUS_TRACE(logger, "Enter");

    std::vector<std::string> paths;

    // Copy the stored QStrings to a std::vector of std::strings to be cmpatible with ITK
    for (auto iter = fileNames.begin(); iter != fileNames.end(); ++iter)
    {
        QString filePath = *iter;
        paths.push_back(filePath.toStdString());
    }

    // Read in all of the slices
    imageStack.clear();
    ImageReader reader;
    int numberOfImages = fileNames.length();
    int slicesPerImage = 0;
    int numberOfSlices = 0;
    for (auto iter = paths.begin(); iter != paths.end(); ++iter)
    {
        slicesPerImage = 0;
        ImageReader::ImageVector imageVec = reader.ReadImage(*iter);
        for (ImageReader::ImageVector::const_iterator iter = imageVec.begin(); iter != imageVec.end(); ++iter)
        {
            Image2DType::Pointer image = *iter;
            imageStack.push_back(*iter);
            ++slicesPerImage;
            ++numberOfSlices;
        }
    }

    // Fix up some series information that may not be set yet. If it hasn't been set
    // we use some defaults.
    if (seriesInfo->imageNumberOfImages() == 0)
    {
        seriesInfo->setImageNumberOfImages(numberOfImages);
        seriesInfo->setImageSlicesPerImage(slicesPerImage);
        seriesInfo->setSeriesNumberOfSlices(numberOfSlices);
    }

    if (seriesInfo->imageSliceSpacing() == 0.0)
        seriesInfo->setImageSliceSpacing(1.0);

    //    if (seriesInfo->imagePatientPositionX == nil)
    //    {
    //        seriesInfo->imagePatientPositionX = [NSNumber numberWithDouble:0.0];
    //        seriesInfo->imagePatientPositionY = [NSNumber numberWithDouble:0.0];
    //        seriesInfo->imagePatientPositionZ = [NSNumber numberWithDouble:0.0];
    //    }

    if (seriesInfo->imagePatientOrientation() == "")
        seriesInfo->setImagePatientOrientation("1\\0\\0\\0\\1\\0");

    LOG4CPLUS_DEBUG(logger, "Read" << imageStack.size() << " slices into image stack.");

    if (int(imageStack.size()) != fileNames.length())
        return ErrorCode::ERROR_READING_FILE;
    else
        return ErrorCode::SUCCESS;
}

ErrorCode SeriesConverter::writeFiles()
{
    LOG4CPLUS_TRACE(logger, "Enter");

    createTimesArray();

    // Create the directory
    bool err = seriesInfo->outputDir().mkpath(seriesInfo->outputPath());
    if (err == false)
        return ErrorCode::ERROR_CREATING_DIRECTORY;

    QDir outputPath = QDir(seriesInfo->outputPath());
    outputPath.setFilter(QDir::Files);
    if (outputPath.entryList().count() != 0)
    {
        if (seriesInfo->overwriteFiles() == false)
            return ErrorCode::ERROR_DIRECTORY_NOT_EMPTY;
    }

    // Now write them out
    DicomSeriesWriter writer(imageStack, seriesInfo->outputPath());
    return writer.WriteFileSeries();
}





