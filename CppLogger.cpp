/**
 * @file CppLogger.cpp
 * @author Mathis Francois
 * @brief CPP file for the log system
 * @version 0.12
 * @date 2024-03-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "CppLogger.hpp"

bool CppLogger::bInit = false;
bool CppLogger::bJournaling = false;

std::map<char, std::string> CppLogger::LevelArray;
int CppLogger::headerMaxSize = 9;
int CppLogger::headerSpace = 5;

std::streambuf* CppLogger::coutBufOg;
std::ofstream CppLogger::logsFile;
std::ostringstream CppLogger::logBuffer;

std::string CppLogger::currentName;

void CppLogger::canWrite(){
    const std::ifstream logsFileForCheck = std::ifstream(LOGS_FILE_NAME);
    if(!CppLogger::bJournaling) return;
    if (CppLogger::bJournaling && logsFileForCheck.good()) return;
    CppLogger::toggleJournaling();
    CppLogger::tprint(LOGS_ERROR, "Unable to write log to file; attempting to reopen the file.");
    CppLogger::toggleJournaling();
}

void CppLogger::initPrint(){
    !CppLogger::currentName.empty() ?
                        (std::cout << "==== CppLogger [" << CppLogger::currentName << "] ====\n")
                        : (std::cout << "==== CppLogger ====\n");
}

void CppLogger::init(){
    if (CppLogger::bInit){
        canWrite();
        return CppLogger::print(LOGS_ERROR, "CppLogger is already initialized");
    }
    CppLogger::LevelArray[LOGS_ERROR] = std::string(LOGS_ERROR_STR);
    CppLogger::LevelArray[LOGS_WARNING] = std::string(LOGS_WARNING_STR);
    CppLogger::LevelArray[LOGS_INFO] = std::string(LOGS_INFO_STR);
    std::ios::sync_with_stdio(false);
    CppLogger::initPrint();
    CppLogger::bInit = true;
}

void CppLogger::init(std::string name){
    if (CppLogger::bInit){
        canWrite();
        return CppLogger::print(LOGS_ERROR, "CppLogger is already initialized");
    }
    CppLogger::LevelArray[LOGS_ERROR] = std::string(LOGS_ERROR_STR);
    CppLogger::LevelArray[LOGS_WARNING] = std::string(LOGS_WARNING_STR);
    CppLogger::LevelArray[LOGS_INFO] = std::string(LOGS_INFO_STR);
    std::ios::sync_with_stdio(false);
    CppLogger::currentName = name;
    CppLogger::initPrint();
    CppLogger::bInit = true;
}


void CppLogger::printInfoHeader(const std::string header_str){
    std::ostringstream oss;

    oss << LOGS_HEADER_BEFOREDECO << header_str << LOGS_HEADER_AFTERDECO;

    int maxWidth = CppLogger::headerMaxSize + CppLogger::headerSpace;
    int headerWidth = oss.str().size();

    int spaceWidth = maxWidth - headerWidth;

    CppLogger::logBuffer << oss.str() << std::setw(spaceWidth) << std::right << "";
}

void CppLogger::print(const char LOGS_LEVEL, const std::string str){
    if (!CppLogger::bInit) return;
    canWrite();
    std::map<char, std::string>::const_iterator it = CppLogger::LevelArray.find(LOGS_LEVEL);
    if (CppLogger::LevelArray.find(LOGS_LEVEL) != CppLogger::LevelArray.end()){
        const std::string header = it->second;
        printInfoHeader(header);
        std::cout << CppLogger::logBuffer.str() << str << '\n';
        CppLogger::logBuffer.str("");
    }
}

void CppLogger::tprint(const char LOGS_LEVEL, const std::string str){
    if (!CppLogger::bInit) return;
    std::time_t nowTime = std::time(nullptr);
    constexpr int maxBufferTimeLenght = 9;
    char timeBuffer[maxBufferTimeLenght];
    strftime(timeBuffer, maxBufferTimeLenght, "%T", std::localtime(&nowTime));
    canWrite();
    CppLogger::logBuffer << "[" << timeBuffer << "]\u2002";
    CppLogger::print(LOGS_LEVEL, str);
}

void CppLogger::toggleJournaling(){
    if (!CppLogger::bInit) return;
    if (!bJournaling){
        FILE* pFile = fopen(LOGS_FILE_NAME, "a");
        if (pFile){
            logsFile = std::ofstream(LOGS_FILE_NAME, std::ios::out | std::ios::app);
            if (logsFile.is_open()){
                coutBufOg = std::cout.rdbuf();
                std::cout.rdbuf(logsFile.rdbuf());
                bJournaling = true;
                CppLogger::initPrint();
            }else{
                CppLogger::tprint(LOGS_ERROR, "Unable to open the file");
            }
            fclose(pFile);
        }else{
            CppLogger::tprint(LOGS_ERROR, "Unable to open or create the file");
        }
    }else{
        std::cout.rdbuf(coutBufOg);
        if (logsFile.is_open()){
            logsFile.close();
        }
        bJournaling = false;
    }
}

void CppLogger::updateLevel(const char levelId, const std::string levelStr){
    if (!CppLogger::bInit) return;
    if (levelId < 0 || (levelId >= 0 && levelId <= 2)){
        CppLogger::tprint(LOGS_ERROR, "The LevelID is incorrect or being used by a default LevelID");
        return;
    }
    CppLogger::LevelArray[levelId] = levelStr;
    const int headerSize = levelStr.size() + 2;
    if (headerSize > CppLogger::headerMaxSize) CppLogger::headerMaxSize = headerSize;
}

void CppLogger::setHeaderSpace(const int spaceSize){
    if (spaceSize < 0){
        CppLogger::tprint(LOGS_ERROR, "The header spacing cannot be negative");
        return;
    }
    CppLogger::headerSpace = spaceSize;
}

void CppLogger::updateLogName(const std::string name){
    CppLogger::currentName = name;
    CppLogger::initPrint();
}