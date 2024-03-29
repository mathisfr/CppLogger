#include "CppLogger.hpp"
int main(){
    /*  Not mandatory, but recommended for faster logging */
    CppLogger::init();


    /*  Enables / Disable logging to a file */
    CppLogger::toogleJournaling();  //  Enable
    CppLogger::print(LOGS_INFO, "Write info");
    CppLogger::print(LOGS_WARNING, "Write warning");
    CppLogger::print(LOGS_ERROR, "Write error");
    CppLogger::tprint(LOGS_INFO, "Write info");
    CppLogger::tprint(LOGS_WARNING, "Write warning");
    CppLogger::tprint(LOGS_ERROR, "Write error");
    CppLogger::toogleJournaling();  //  Disable

    CppLogger::print(LOGS_INFO, "Write info");
    CppLogger::print(LOGS_WARNING, "Write warning");
    CppLogger::print(LOGS_ERROR, "Write error");
    CppLogger::tprint(LOGS_INFO, "Write info");
    CppLogger::tprint(LOGS_WARNING, "Write warning");
    CppLogger::tprint(LOGS_ERROR, "Write error");
    return 0;
}