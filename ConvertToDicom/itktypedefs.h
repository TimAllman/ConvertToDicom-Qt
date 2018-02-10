//
//  itktypedefs.h
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
#ifndef ITKTYPEDEFS_H
#define ITKTYPEDEFS_H

#include "itkheaders.pch.h"

/**
 * @brief InternalPixelType
 * When this program reads in image files they are stored with this canonical pixel type.
 * TODO change this to float.
 */
typedef unsigned short InternalPixelType;

/**
 * @brief Image2DType
 * Canonical type of a 2D image.
 */
typedef itk::Image<InternalPixelType, 2u> Image2DType;

/**
 * @brief Image3DType
 * Canonical type of a 3D image.
 */
typedef itk::Image<InternalPixelType, 3u> Image3DType;

#endif // ITKTYPEDEFS_H
