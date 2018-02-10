//
//  errorcodes
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

#include "errorcodes.h"

#include <QString>

const char* ErrorCodeAsString(ErrorCode code)
{
    switch (code)
    {
        case ErrorCode::SUCCESS:
            return "Success";
        case ErrorCode::ERROR:
            return "Error";
        case ErrorCode::ERROR_FILE_NOT_FOUND:
            return "File not found";
        case ErrorCode::ERROR_READING_FILE:
            return "Error reading file";
        case ErrorCode::ERROR_WRITING_FILE:
            return "Error writing file";
        case ErrorCode::ERROR_CREATING_DIRECTORY:
            return "Error creating directory";
        case ErrorCode::ERROR_DIRECTORY_NOT_EMPTY:
            return "Directory not empty";
        case ErrorCode::ERROR_IMAGE_INCONSISTENT:
            return "Image inconsistent";
        default:
            return QString("Unknown ErrorCode value: %1").arg(static_cast<int>(code)).toStdString().c_str();
    };
}
