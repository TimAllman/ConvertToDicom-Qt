//
//  dicomsparametersreader.cpp
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
#include "dicomparametersreader.h"

#include "itkheaders.pch.h"

DicomParametersReader::DicomParametersReader(const QString& directoryPath)
    : seriesInfo(SeriesInfo::getInstance()), inputDirectory(directoryPath.toStdString()),
      namesFinder(itk::GDCMSeriesFileNames::New()),
      logger(Logger::getInstance(std::string(LOGGER_NAME) + ".DicomParametersReader"))
{
    namesFinder->SetInputDirectory(inputDirectory);
    namesFinder->SetUseSeriesDetails(true);

}

//ErrorCode DicomParametersReader::GetDirectoryContents()
//{
//    seriesUIDs = namesFinder->GetSeriesUIDs();

//    LOG4CPLUS_INFO(logger, "SeriesUIDs found in " << inputDirectory);
//    for (itk::GDCMSeriesFileNames::SeriesUIDContainerType::const_iterator iter = seriesUIDs.begin();
//         iter != seriesUIDs.end(); ++iter)
//    {
//        LOG4CPLUS_INFO(logger, "    " << *iter);
//    }


//}

ErrorCode DicomParametersReader::ReadParameters()
{
    // First step is to find the files forming the series.

    return ErrorCode::SUCCESS;
}
