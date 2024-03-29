/**
 * @file CppLogger.hpp
 * @author Mathis Francois
 * @brief Header for the log system
 * @version 0.1
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

/**
 * @brief   LOGS_LEVEL
 * 
 */
#define LOGS_INFO 0x1
#define LOGS_INFO_STR "INFO"
#define LOGS_WARNING 0x2
#define LOGS_WARNING_STR "WARNING"
#define LOGS_ERROR 0x4
#define LOGS_ERROR_STR "ERROR"

/**
 * @brief   LOGS HEADER STYLE
 *  LOGS_HEADER_MAXLEN must be adjusted if you want your "LOGS_HEADER_BEFOREDECO" and "LOGS_HEADER_AFTERDECO"
 *  to be more than two characters long and if "LOGS_WARNING_STR" is no longer the largest possible word
 */
#define LOGS_HEADER_AFTERDECO "\u203A"
#define LOGS_HEADER_BEFOREDECO "\u2039"
#define LOGS_HEADER_SPACE 5
#define LOGS_HEADER_MAXLEN 9 /*! <9 = LOGS_HEADER_BEFOREDECO + LOGS_WARNING_STR + LOGS_HEADER_AFTERDECO> */

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

class CppLogger
{
public:
    CppLogger() = delete;
    ~CppLogger() = delete;

    /**
     * @brief Logger initialization
     * 
     */
    static void init();
    static bool bInit;

    /**
     * @brief   Enables or disables logging to a file
     * 
     */
    static void toogleJournaling();
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

};

