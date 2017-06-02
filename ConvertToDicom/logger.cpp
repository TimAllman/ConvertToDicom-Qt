//
//  loggerutils
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

#include "logger.h"

#include "settings.h"

#include <log4cplus/consoleappender.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/loggingmacros.h>

std::string LogLevelToString(LogLevel level);

void SetupLogger(const std::string& loggerName, LogLevel consoleLogLevel, LogLevel fileLogLevel,
                 const std::string& filePath)
{
    static bool setup = false;
    if (setup)
        return;
    setup = true;

    // The logger is set to log all messages. We use the appenders to restrict the output(s).
    Logger logger = Logger::getInstance(loggerName);
    logger.setLogLevel(int(LogLevel::LOG_LEVEL_ALL));

    // The console appender.
    log4cplus::SharedAppenderPtr consoleAppender(new log4cplus::ConsoleAppender);
    std::string consoleAppName = loggerName + ".console";
    consoleAppender->setName(consoleAppName);
    consoleAppender->setThreshold(int(consoleLogLevel));
    //consoleAppender->setThreshold(int(LogLevel::LOG_LEVEL_INFO));
    std::string consolePattern = "%-5p (%d{%q}) [%b:%L] %m%n";
    std::auto_ptr<log4cplus::Layout> layout(new log4cplus::PatternLayout(consolePattern));
    consoleAppender->setLayout(layout);

    logger.addAppender(consoleAppender);

    // Generate the name of the rolling file, by default in $HOME/Library/Logs
    std::string logFilePath;
    std::string logFileName = loggerName + ".log";
    if (filePath.size() == 0)
    {
        #if defined(Q_OS_MACOS) || defined(Q_OS_IOS)
            logFilePath = std::string(getenv("HOME")) + "/Library/Logs/";
        #elif defined(Q_OS_WIN)
            logFilePath = std::string(getenv("HOMEDRIVE")) + std::string(getenv("HOMEPATH")) + "\\Logs\\";
        #elif defined(Q_OS_UNIX)
            logFilePath = std::string("/var/log");
        #endif
    }
    else
    {
        logFilePath = filePath + "/";
    }

    logFilePath += logFileName;

    // Set up the Rolling File Appender format
    std::string logFileAppName = loggerName + ".file";
    log4cplus::SharedAppenderPtr
        logFileApp(new log4cplus::RollingFileAppender(logFilePath, 1000000, 5, false));
    logFileApp->setName(logFileAppName);
    std::string filePattern = "%-5p [%d{%y-%m-%d %H:%M:%S:%q}][%b:%L] %m%n";
    std::auto_ptr<log4cplus::Layout> fileLayout(new log4cplus::PatternLayout(filePattern));
    logFileApp->setLayout(fileLayout);

    // Set up the log file level
    int intFileLogLevel = int(fileLogLevel);
    if (fileLogLevel == LogLevel::LOG_LEVEL_NOT_SET)
    {
        // Load logging level. If LoggingLevelKey is not found in the settings, the default
        // value LogLevel::LOG_LEVEL_INFO is used.
        Settings settings;
        intFileLogLevel = settings.value(Settings::LoggingLevelKey, int(LogLevel::LOG_LEVEL_INFO)).toInt();
    }

    logFileApp->setThreshold(intFileLogLevel);
    logger.addAppender(logFileApp);

    // Force this to the console.
    LOG4CPLUS_INFO(logger, "Logging to file: " << logFilePath << ", Level: "
                   << LogLevelToString(LogLevel(intFileLogLevel)));
}

void ResetLoggerLevel(const char* name, LogLevel level)
{
    log4cplus::Logger logger = log4cplus::Logger::getInstance(name);
    logger.setLogLevel(int(level));
}

/**
 * Convert the log level to a human readable string.
 * @param level The log4m and log4cplus logging level.
 * @return The level as a string or "Unknown" if level is invalid
 */
std::string LogLevelToString(LogLevel level)
{
    std::string retVal;

    switch (level)
    {
        case LogLevel::LOG_LEVEL_OFF:
            retVal = "OFF";
            break;
        case LogLevel::LOG_LEVEL_FATAL:
            retVal = "FATAL";
            break;
        case LogLevel::LOG_LEVEL_ERROR:
            retVal = "ERROR";
            break;
        case LogLevel::LOG_LEVEL_WARN:
            retVal = "WARN";
            break;
        case LogLevel::LOG_LEVEL_INFO:
            retVal = "INFO";
            break;
        case LogLevel::LOG_LEVEL_DEBUG:
            retVal = "DEBUG";
            break;
        case LogLevel::LOG_LEVEL_TRACE:
            retVal = "TRACE";
            break;
        case LogLevel::LOG_LEVEL_NOT_SET:
            retVal = "NOT SET";
            break;
    }

    return retVal;
}
