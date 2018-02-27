//
//  imageinfo.cpp
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
#include "imageinfo.h"

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

ImageInfo::ImageInfo()
    : m_spacing(3), m_origin(3), m_dimensions(3),
      m_logger(log4cplus::Logger::getInstance(std::string(LOGGER_NAME) + ".ImageInfo"))
{

}

void ImageInfo::setImageTypeName(const std::string& imageIoClassName)
{
    // strip the trailing "ImageIO" from the name of the ITK class doing the reading.
    std::size_t pos = imageIoClassName.find("ImageIO");
    if (pos != std::string::npos)
    {
        m_imageTypeName = imageIoClassName;
        m_imageTypeName.erase(pos);

        LOG4CPLUS_DEBUG(m_logger, "Image type name = " + m_imageTypeName);
    }
    else
    {
        LOG4CPLUS_ERROR(m_logger, "Could not determine image type name: " + imageIoClassName);
        throw std::invalid_argument(imageIoClassName);
    }
}

