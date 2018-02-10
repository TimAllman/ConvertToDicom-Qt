//
//  dicomfilewriter.cpp
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
#include "dicomserieswriter.h"
#include "dumpmetadatadictionary.h"

#include "itkheaders.pch.h"

#include <QTime>

#include <iostream>
#include <sstream>
#include <iomanip>

DicomSeriesWriter::DicomSeriesWriter(QVector<Image2DType::Pointer>& images, const QString& outputDirectoryName)
    : seriesInfo(SeriesInfo::getInstance()), images(images), outputDirectory(outputDirectoryName),
  logger(Logger::getInstance(std::string(LOGGER_NAME) + ".DicomSeriesWriter"))
{
    std::string name = std::string(LOGGER_NAME) + ".DicomSeriesWriter";
    LOG4CPLUS_TRACE(logger, "Enter");
}

ErrorCode DicomSeriesWriter::WriteFileSeries()
{
    LOG4CPLUS_TRACE(logger, "Enter");
    // Set up the new metadata dictionary array
    // This is based upon the example on the ITK examples wiki
    // http://www.itk.org/Wiki/ITK/Examples/DICOM/ResampleDICOM
    //

    PrepareMetaDataDictionaryArray();

    //
    // create a Dicom series writer
    itk::GDCMImageIO::Pointer dicomIo = itk::GDCMImageIO::New();
    dicomIo->SetPixelType(itk::ImageIOBase::SCALAR);
    dicomIo->KeepOriginalUIDOn();

    // define the filenames generator type and instance
    typedef itk::NumericSeriesFileNames NameGeneratorType;
    NameGeneratorType::Pointer nameGenerator = NameGeneratorType::New();

    QString value = outputDirectory + "/IM-" + QString::number(seriesInfo->seriesNumber()) + "-%04d.dcm";
    nameGenerator->SetSeriesFormat(value.toStdString());
    nameGenerator->SetStartIndex(1);
    nameGenerator->SetEndIndex(itk::SizeValueType(images.size()));
    fileNames = nameGenerator->GetFileNames();

    // We want to empty the output directory so we remove it and recreate it.
    itksys::SystemTools::RemoveADirectory(outputDirectory.toStdString());
    itksys::SystemTools::MakeDirectory(outputDirectory.toStdString());

    typedef itk::ImageSeriesWriter<Image3DType, Image2DType> WriterType;
    WriterType::Pointer writer = WriterType::New();
    writer->SetImageIO(dicomIo);
    writer->SetFileNames(fileNames);
    writer->SetMetaDataDictionaryArray(&dictArray);
    Image3DType::Pointer image = MergeSlices();
    writer->SetInput(image);

    try
    {
        writer->Update();
    }
    catch (itk::ExceptionObject& ex)
    {
        LOG4CPLUS_ERROR(logger, "ExceptionObject caught. " << ex.what());
        return ErrorCode::ERROR_WRITING_FILE;
    }

    return ErrorCode::SUCCESS;
}

void DicomSeriesWriter::CopyDictionary(const itk::MetaDataDictionary& fromDict,
                                       itk::MetaDataDictionary& toDict)
{
    LOG4CPLUS_TRACE(logger, "Enter");

    typedef itk::MetaDataDictionary DictionaryType;

    DictionaryType::ConstIterator itr = fromDict.Begin();
    DictionaryType::ConstIterator end = fromDict.End();
    typedef itk::MetaDataObject< std::string > MetaDataStringType;

    while (itr != end)
    {
        itk::MetaDataObjectBase::Pointer  entry = itr->second;

        MetaDataStringType::Pointer entryvalue = dynamic_cast<MetaDataStringType *>(entry.GetPointer()) ;
        if (entryvalue)
        {
            std::string tagkey = itr->first;
            std::string tagvalue = entryvalue->GetMetaDataObjectValue();
            itk::EncapsulateMetaData<std::string>(toDict, tagkey, tagvalue);
        }
        ++itr;
    }
}

void DicomSeriesWriter::PrepareMetaDataDictionaryArray()
{
    LOG4CPLUS_TRACE(logger, "Enter");

    // It may have been used in a previous run.
    dictArray.clear();

    itk::MetaDataDictionary seriesDict = seriesInfo->metaDataDictionary();
    LOG4CPLUS_TRACE(logger, "********** seriesDict - 1 ************");
    LOG4CPLUS_TRACE(logger, DumpDicomMetaDataDictionary(seriesDict));

    bool isTimeSeries = (seriesInfo->seriesTimeIncrement() > 0.0);
    if (isTimeSeries)
    {
        std::stringstream sstr;
        int numTimes = seriesInfo->imageNumberOfImages();
        if (numTimes > 1)
        {
            sstr.str("");
            sstr << numTimes;
            std::string numTemporalPositions = sstr.str();
            itk::EncapsulateMetaData<std::string>(seriesDict, "0020|0105", numTemporalPositions);
        }
    }

    // These are converted images so we show that.
    itk::EncapsulateMetaData<std::string>(seriesDict, "0008|0008", "ORIGINAL");
    itk::EncapsulateMetaData<std::string>(seriesDict, "0008|0064", "WSD");

    LOG4CPLUS_TRACE(logger, "********** seriesDict - 2 ************");
    LOG4CPLUS_TRACE(logger, DumpDicomMetaDataDictionary(seriesDict));

    // Derivation Description - How this image was derived
    std::ostringstream value;
    value.str("");
    value << "Converted to DICOM using " << ITK_SOURCE_VERSION;
    // Deal with a 1024 character max length.
    unsigned lengthOfDesc = static_cast<unsigned>(value.str().length());
    std::string derivationDesc(value.str(), 0, lengthOfDesc > 1024 ? 1024 : lengthOfDesc);
    itk::EncapsulateMetaData<std::string>(seriesDict, "0008|2111", derivationDesc);

    // loop through the images, and the slices in each image
    int instanceNumber = 1;
    for (int imageIdx = 0; imageIdx < seriesInfo->imageNumberOfImages(); ++imageIdx)
    {
        itk::MetaDataDictionary imageDict;
        CopyDictionary(seriesDict, imageDict);

        if (isTimeSeries)
        {
            // Temporal Position
            std::stringstream sstr;
            sstr.str("");
            sstr << imageIdx+1;
            std::string temporalPosition = sstr.str();
            itk::EncapsulateMetaData<std::string>(imageDict, "0020|0100", temporalPosition);
        }

        QTime time = seriesInfo->acqTimes()[imageIdx];
        std::string acqTime = time.toString("HHmmss.zzz").toStdString();
        itk::EncapsulateMetaData<std::string>(imageDict, "0008|0032", acqTime);

        float sliceLocation = 0.0;
        for (int sliceIdx = 0; sliceIdx < seriesInfo->imageSlicesPerImage(); ++sliceIdx)
        {
            // Make a new dictionary for the slice and copy over the information already set
            // We need a pointer because the dictionary array is an array of pointers.
            itk::MetaDataDictionary *sliceDict = new itk::MetaDataDictionary();
            CopyDictionary(imageDict, *sliceDict);

            gdcm::UIDGenerator sopuidGen;
            std::string sopInstanceUID = sopuidGen.Generate();
            //itk::EncapsulateMetaData<std::string>(*sliceDict, "0008|0018", sopInstanceUID);
            itk::EncapsulateMetaData<std::string>(*sliceDict, "0002|0003", sopInstanceUID);

            // Set the IPP for this slice
            std::stringstream sstr;
            sstr << std::fixed << std::setprecision(2) << seriesInfo->imagePositionPatientX() << "\\"
            << seriesInfo->imagePositionPatientY() << "\\" << seriesInfo->imagePositionPatientZ() << "\\";

            std::string imagePositionPatient = seriesInfo->imagePositionPatientString(sliceIdx).toStdString();
            itk::EncapsulateMetaData<std::string>(*sliceDict, "0020|0032", imagePositionPatient);

            // The relative location of this slice from the first one.
            sstr.str("");
            sstr << std::fixed << std::setprecision(1) << sliceLocation;
            itk::EncapsulateMetaData<std::string>(*sliceDict, "0020|1041",  sstr.str());
            sliceLocation += seriesInfo->imageSliceSpacing();

            sstr.str("");
            sstr << instanceNumber;
            itk::EncapsulateMetaData<std::string>(*sliceDict, "0020|0013", sstr.str());
            ++instanceNumber;

            LOG4CPLUS_TRACE(logger, "*** Image " << imageIdx << " slice " << sliceIdx << " ***");
            LOG4CPLUS_TRACE(logger, DumpDicomMetaDataDictionary(*sliceDict));
            dictArray.push_back(sliceDict);
        }
    }
}

Image3DType::Pointer DicomSeriesWriter::MergeSlices()
{
    LOG4CPLUS_TRACE(logger, "Enter");

    // Concatenate the whole bunch of slices into one image.
    typedef itk::TileImageFilter<Image2DType, Image3DType> TileFilterType;
    TileFilterType::Pointer tileFilter = TileFilterType::New();

    itk::FixedArray<unsigned int, 3> layout;
    layout[0] = 1;
    layout[1] = 1;
    layout[2] = 0;

    LOG4CPLUS_DEBUG(logger, "Layout = " << layout);

    tileFilter->SetLayout(layout);
    tileFilter->SetDefaultPixelValue(0);
    int numSlices = images.size();
    for (int idx = 0; idx < numSlices; ++idx)
    {
        tileFilter->SetInput(unsigned(idx), images[idx]);
    }

    tileFilter->Update();

    Image3DType::Pointer image3d = tileFilter->GetOutput();
    return image3d;
}
