/**
 * @file CppLogger.hpp
 * @author Mathis Francois
 * @brief Header for the log system
 * @version 0.12
 * @date 2024-03-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include <exception>
#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include <fstream> 
#include <map>

/**
 * @brief   LOGS_LEVEL
 * 
 */
#define LOGS_INFO 0x0
#define LOGS_INFO_STR "INFO"
#define LOGS_WARNING 0x1
#define LOGS_WARNING_STR "WARNING"
#define LOGS_ERROR 0x2
#define LOGS_ERROR_STR "ERROR"

/**
 * @brief   LOGS HEADER STYLE
 * 
 */
#define LOGS_HEADER_AFTERDECO "\u203A"
#define LOGS_HEADER_BEFOREDECO "\u2039"

/**
 * @brief   LOGS TIME STYLE
 * 
 */
#define LOGS_TIME_AFTERDECO "]"
#define LOGS_TIME_BEFOREDECO "["

/**
 * @brief   LOGS FILE PARAMS
 * 
 */
#define LOGS_FILE_NAME "logs.txt"

typedef void (*logsLevelFunc)(std::string str);
class CppLogger
{
private:
    static std::map<char, std::string> LevelArray;
    static int headerMaxSize; /*! <Default 9 = LOGS_HEADER_BEFOREDECO + LOGS_WARNING_STR + LOGS_HEADER_AFTERDECO> */
    static int headerSpace; 

    static std::ostringstream logBuffer; /*! <To use std::cout only once> */

    /**
     * @brief   Displays the log header correctly
     * 
     * @param header_str 
     */
    static void printInfoHeader(const std::string header_str);

    /**
     * @brief   Check whether you can write to the output buffer,
     *          because if file logging is active and the file does not exist,
     *          you must return an error on standard output.
     * 
     */
    static void canWrite();

    static void initPrint();

    static std::streambuf* coutBufOg; /*! <For save cout buffer original>*/
    static std::ofstream logsFile; /*! <For open and write in file>*/

    static std::string currentName;
public:
    CppLogger() = delete;
    ~CppLogger() = delete;

    /**
     * @brief Logger initialization
     * 
     */
    static void init();
    static void init(std::string name);
    static bool bInit;

    /**
     * @brief   Enables or disables logging to a file
     * 
     */
    static void toggleJournaling();
    static bool bJournaling;

    /**
     * @brief Function used to display an output on the log system
     * 
     * @param LOGS_LEVEL 
     * @param str 
     */
    static void print(const char LOGS_LEVEL, const std::string str);

    /**
     * @brief Function to be used to display an output on the log system with a time display
     * 
     * @param LOGS_LEVEL 
     * @param str 
     */
    static void tprint(const char LOGS_LEVEL, const std::string str);

    /**
     * @brief Add or modify a debug level
     * 
     * @param levelId 
     * @param level 
     */
    static void updateLevel(const char levelId, const std::string level);

    /**
     * @brief Change the name of the current debug section
     * 
     * @param name 
     */
    static void updateLogName(const std::string name);

    /**
     * @brief Set the Header Space object
     * 
     * @param spaceSize 
     */
    static void setHeaderSpace(const int spaceSize);
};

typedef CppLogger CL;