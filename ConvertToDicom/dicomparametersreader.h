//
//  dicomparametersreader.h
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
#ifndef DICOMPARAMETERSREADER_H
#define DICOMPARAMETERSREADER_H

#include "logger.h"
#include "errorcodes.h"
#include "itktypedefs.h"
#include "seriesinfo.h"

#include "itkheaders.pch.h"

#include <QString>

/**
 * Class to read a dicom series and extract parameters from its dictionary, placing them into
 * the global SeriesInfo instance.
 */
class DicomParametersReader
{
public:
    //typedef unsigned short DicomPixelType; ///< Always write with this pixel type.

    /**
     * Class constructor.
     * @param directoryPath The input directory path. This the full path of the directory containing
     * the DICOM file(s).
     */
    explicit DicomParametersReader(const QString& directoryPath);

    /**
     * Do the parameter reading.
     * @return Suitable value in ErrorCode enum.
     */
    ErrorCode ReadParameters();

protected:
    ErrorCode GetDirectoryContents();

private:
    SeriesInfo* seriesInfo;                          ///< The SeriesInfoITK passed in the constructor.
    std::string inputDirectory;                      ///< The input directory passed in the constructor.
    std::vector<itk::MetaDataDictionary*> dictArray; ///< Array of itk::MetaDataDictionary instances.
    itk::GDCMSeriesFileNames::Pointer namesFinder;
    itk::GDCMSeriesFileNames::SeriesUIDContainerType seriesUIDs;

    Logger logger; ///< Logger for this class.

};

#endif // DICOMSERIESREADER_H
