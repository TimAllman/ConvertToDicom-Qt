//
//  logger
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
#ifndef LOGGER_H
#define LOGGER_H

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/loglevel.h>

#include <string>

#define LOGGER_NAME "ca.brasscats.ConvertToDicom" ///< The base name of the logger used throughout.

/**
 * @brief The LogLevel enum
 * This is created as a convenience, as an interface that
 * can easily be changed should the logger package be changed
 * and as a way of providing typesafe identifiers.
 */
enum struct LogLevel
{
    LOG_LEVEL_OFF = log4cplus::OFF_LOG_LEVEL,
    LOG_LEVEL_FATAL = log4cplus::FATAL_LOG_LEVEL,
    LOG_LEVEL_ERROR = log4cplus::ERROR_LOG_LEVEL,
    LOG_LEVEL_WARN = log4cplus::WARN_LOG_LEVEL,
    LOG_LEVEL_INFO = log4cplus::INFO_LOG_LEVEL,
    LOG_LEVEL_DEBUG = log4cplus::DEBUG_LOG_LEVEL,
    LOG_LEVEL_TRACE = log4cplus::TRACE_LOG_LEVEL,
    LOG_LEVEL_ALL = log4cplus::ALL_LOG_LEVEL,
    LOG_LEVEL_NOT_SET = log4cplus::NOT_SET_LOG_LEVEL
};

/**
 * @brief Logger
 * This is a convenient typedef for the log4cplus::logger.
 */
typedef log4cplus::Logger Logger;

/**
 * Set up the log4cplus logger.
 * @param loggerName The name of the logger.
 * @param fileLogLevel The initial level of the logger. This affects only the rolling
 * file appender. If level is LogLevel::NOT_SET_LOG_LEVEL then the Qt settings will
 * be queried. This can be changed with ResetLoggerLevel(). There is also a console
 * appender which is always set to LogLevel::INFO_LOG_LEVEL.
 * @param logFilePath The complete path of the logger file. Defaults are set in the .cpp file.
 */
void SetupLogger(const std::string& loggerName, LogLevel fileLogLevel, const std::string& logFilePath = "");

/**
 * Reset the logger level of the file appender. The console appender is not affected.
 * @param name The name of the logger
 * @param level The new level.
 */
void ResetLoggerLevel(const char* name, LogLevel level);


#endif // LOGGER_H
