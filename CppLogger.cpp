/**
 * @file CppLogger.cpp
 * @author Mathis Francois
 * @brief CPP file for the log system
 * @version 0.1
 * @date 2024-03-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "CppLogger.hpp"

bool CppLogger::bInit = false;
bool CppLogger::bJournaling = false;

static std::streambuf* coutBufOg = nullptr; /*! <For save cout buffer original>*/
static std::ofstream logsFile; /*! <For open and write in file>*/

/**
 * @brief   Check whether you can write to the output buffer,
 *          because if file logging is active and the file does not exist,
 *          you must return an error on standard output.
 * 
 * @return true 
 * @return false 
 */
static bool canWrite(){
    if(!CppLogger::bJournaling || (CppLogger::bJournaling && logsFile.is_open())){
        return true;
    }
    std::cout.rdbuf(coutBufOg);
    CppLogger::tprint(LOGS_ERROR, "Impossible to write log to buffer");
    return false;
}

void CppLogger::init(){
    if (CppLogger::bInit){
        if (!canWrite()) return;
        return CppLogger::print(LOGS_ERROR, "CppLogger is already initialized");
    }
    std::ios::sync_with_stdio(false);
    CppLogger::bInit = true;
}

/**
 * @brief   Displays the log header correctly
 * 
 * @param header_str 
 */
static void printInfoHeader(const std::string header_str){
    std::ostringstream oss;

    oss << LOGS_HEADER_BEFOREDECO << header_str << LOGS_HEADER_AFTERDECO;

    int maxWidth = LOGS_HEADER_MAXLEN + LOGS_HEADER_SPACE;
    int headerWidth = oss.str().size();

    int spaceWidth = maxWidth - headerWidth;

    std::cout << oss.str() << std::setw(spaceWidth) << std::right << "";
}

/**
 * @brief   Write information in the log
 * 
 * @param str 
 */
static void printInfo(const std::string str){
    printInfoHeader(LOGS_INFO_STR);
    std::cout << str << std::endl;
}
/**
 * @brief   Write warning in the log
 * 
 * @param str 
 */
static void printWarning(const std::string str){
    printInfoHeader(LOGS_WARNING_STR);
    std::cout << str << std::endl;
}
/**
 * @brief   Write error in the log
 * 
 * @param str 
 */
static void printError(const std::string str){
    printInfoHeader(LOGS_ERROR_STR);
    std::cout << str << std::endl;
}

void CppLogger::print(const char LOGS_LEVEL, const std::string str){
    if (!canWrite()) return;
    if (LOGS_LEVEL & LOGS_INFO){
        printInfo(str);
    }else
    if(LOGS_LEVEL & LOGS_WARNING){
        printWarning(str);
    }else
    if(LOGS_LEVEL & LOGS_ERROR){
        printError(str);
    }
}

void CppLogger::tprint(const char LOGS_LEVEL, const std::string str){
    std::time_t nowTime = std::time(nullptr);
    constexpr int maxBufferTimeLenght = 9;
    char timeBuffer[maxBufferTimeLenght];
    strftime(timeBuffer, maxBufferTimeLenght, "%T", std::localtime(&nowTime));
    if (!canWrite()) return;
    std::cout << "[" << timeBuffer << "]\u2002";
    CppLogger::print(LOGS_LEVEL, str);
}

void CppLogger::toogleJournaling(){
    if (!bJournaling){
        FILE* pFile = fopen(LOGS_FILE_NAME, "w");
        if (pFile){
            logsFile = std::ofstream(LOGS_FILE_NAME);
            if (logsFile.is_open()){
                coutBufOg = std::cout.rdbuf();
                std::cout.rdbuf(logsFile.rdbuf());
                bJournaling = true;
            }
            fclose(pFile);
        }
    }else{
        std::cout.rdbuf(coutBufOg);
        if (logsFile.is_open()){
            logsFile.close();
        }
        bJournaling = false;
    }
}
