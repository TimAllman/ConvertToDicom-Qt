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
#ifndef ERRORCODES_H
#define ERRORCODES_H

/**
 * Collection of error codes
 */
enum struct ErrorCode
{
    SUCCESS,                  ///< All is well.
    ERROR,                    ///< General error.
    ERROR_FILE_NOT_FOUND,     ///< File(s) not found.
    ERROR_READING_FILE,       ///< Problem reading existing file(s).
    ERROR_WRITING_FILE,       ///< Problem creating or writing file(s).
    ERROR_CREATING_DIRECTORY, ///< Problem creating a directory.
    ERROR_DIRECTORY_NOT_EMPTY,///< Directory contains files when it shouldn't.
    ERROR_IMAGE_INCONSISTENT  ///< Problem with input images.
};

const char* ErrorCodeAsString(ErrorCode code);

#endif // ERRORCODES_H
