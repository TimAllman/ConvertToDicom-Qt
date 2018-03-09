//
//  imageinfo.h
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
#ifndef IMAGEINFO_H
#define IMAGEINFO_H

#include "logger.h"

#include <QString>

#include <string>
#include <vector>
#include <sstream>
#include <exception>

/**
 * This class contains some of the metadata in an image of interest. It is used as a
 * temporary container for information to be shown in the <code>previewTextEdit</code>
 * in the main window.
 */
class ImageInfo
{
public:
    /**
     * Default constructor.
     */
    ImageInfo();

    /**
     * Copy constructor
     * @param other The other instance.
     */
    ImageInfo(const ImageInfo& other);

    /**
     * Copy assignment operator.
     * @param other The other instance
     * @return Reference to *this.
     */
    ImageInfo& operator=(const ImageInfo& other);

    /**
     * Initialises tthe instance.
     */
    void init();

    //Getters
    /**
     * Get the type of source image as a string. The string is derived from the string returned by
     * <code>itk::ImageIOBase::GetNameOfClass()</code>.
     * @return The type of source image as a string.
     */
    std::string imageTypeName()
    {
        return m_imageTypeName;
    }

    /**
     * Get the number of dimensions in this image, 2 or 3 most likely.
     * @return The number of dimensions in this image.
     */
    unsigned int numDims()
    {
        return m_numDims;
    }

    int slicesPerImage()
    {
        return m_slicesPerImage;
    }

    /**
     * Get the pixel spacing in mm for a given dimension.
     * @param dim The dimension of interest (0..2).
     * @return The pixel spacing for dimension <code>dim</code>
     */
    double spacing(unsigned int dim)
    {
        if (dim > m_numDims - 1)
        {
            LOG4CPLUS_FATAL(m_logger, "Argument dim out of range: " << dim
                            << ". Range is 0 to " << m_numDims - 1);
            throw std::out_of_range("Argument dim out of range.");
        }
        return m_spacing[static_cast<std::vector<double>::size_type>(dim)];
    }

    /**
     * Get the spacings for the image as a string.
     * @return The spacings for the image as a string, separated by slashes.
     */
    std::string spacingStr()
    {
        std::stringstream sstr;
        for (unsigned int idx = 0; idx < m_numDims; ++idx)
        {
            sstr << m_spacing[static_cast<std::vector<double>::size_type>(idx)];
            if (idx < m_numDims - 1)
                sstr << "/";
        }
        return sstr.str();
    }

    /**
     * Get the origin in mm for a given dimension.
     * @param dim The dimension of interest.
     * @return
     */
    double origin(int dim)
    {
        return m_origin[static_cast<std::vector<double>::size_type>(dim)];
    }

    /**
     * Get the origin for the image as a string.
     * @return The origin for each dimension for the image as a string, separated by
     * slashes.
     */
    std::string originStr()
    {
        std::stringstream sstr;
        for (unsigned int idx = 0; idx < m_numDims; ++idx)
        {
            sstr << m_origin[static_cast<std::vector<double>::size_type>(idx)];
            if (idx < m_numDims - 1)
                sstr << "/";
        }

        return sstr.str();
    }

    int numberOfImages()
    {
        return m_numberOfImages;
    }

    std::string imageOrientationPatient()
    {
        return m_imageOrientationPatient;
    }

    //Setters
    /**
     * Set the image type name. Any string which does not end with "ImageIO" will cause a
     * `std::invalid_argument(const char*)` exception to be thrown.
     * @param imageTypeName  The string returned by <code>itk::ImageIOBase::GetImageTypeName()</code>.
     * The argument will be of the form <em>"xxxxImageIO"</em> where <em>xxxx</em> is the name of the image
     * format. It is this name which is extracted and stored.
     */
    void setImageTypeName(const std::string& imageTypeName);

    /**
     * Set the number of dimensions in this image.
     * @param numDims The number of dimensions (2 or 3).
     */
    void setNumDims(unsigned int numDims)
    {
        m_numDims = numDims;
    }

    void setSpacing(unsigned int dim, double spacing)
    {
        m_spacing[static_cast<std::vector<double>::size_type>(dim)] = spacing;
    }

    void setOrigin(unsigned int dim, double origin)
    {
        m_spacing[static_cast<std::vector<double>::size_type>(dim)] = origin;
    }

    void setDimension(unsigned int dim, int dimension)
    {
        m_spacing[static_cast<std::vector<int>::size_type>(dim)] = dimension;
    }

    void setSlicesPerImage(int slicesPerImage)
    {
        m_slicesPerImage = slicesPerImage;
    }

    void setNumberOfSlices(int numberOfSlices)
    {
        m_numberOfSlices = numberOfSlices;
    }

    void setNumberOfImages(int numberOfImages)
    {
        m_numberOfImages = numberOfImages;
    }

    void setImageOrientationPatient(const std::string iop)
    {
        m_imageOrientationPatient = iop;
    }

    void setPixelType(const std::string pixelType)
    {
        m_pixelType = pixelType;
    }

private:
    std::string m_imageTypeName;      ///<  The type of image. (nrrd, jpeg etc.)
    unsigned int m_numDims;           ///<  Number of dimensions.
    std::vector<double> m_spacing;
    std::vector<double> m_origin;
    std::vector<int> m_dimensions;
    int m_slicesPerImage;
    int m_numberOfSlices;
    int m_numberOfImages;

    std::string m_imageOrientationPatient;
    std::string m_pixelType;

    Logger m_logger;
};

#endif // IMAGEINFO_H
