## Journaling Application

This is a simple C++ logging library for journaling messages with various log levels such as INFO, WARNING, and ERROR. It provides functionality to log messages to the console as well as to a file.

## Installation

To use this logging library in your project, simply include the CppLogger.hpp header file and ensure that the CppLogger.cpp implementation file is compiled along with your project.

## Usage

Here's how you can use the logging library in your C++ application:

```cpp
#include "CppLogger.hpp"

int main() {
    // Initialize the logger (not mandatory, but recommended for faster logging)
    CppLogger::init();

    // Enable or disable logging to a file
    CppLogger::toggleJournaling(); // Enable journaling

    // Log messages with different log levels
    CppLogger::print(LOGS_INFO, "Write info");
    CppLogger::print(LOGS_WARNING, "Write warning");
    CppLogger::print(LOGS_ERROR, "Write error");

    // Log messages with timestamps
    CppLogger::tprint(LOGS_INFO, "Write info");
    CppLogger::tprint(LOGS_WARNING, "Write warning");
    CppLogger::tprint(LOGS_ERROR, "Write error");

    // Disable journaling
    CppLogger::toggleJournaling();

    // Log messages standard output
    CppLogger::print(LOGS_INFO, "Write info");
    CppLogger::print(LOGS_WARNING, "Write warning");
    CppLogger::print(LOGS_ERROR, "Write error");
    CppLogger::tprint(LOGS_INFO, "Write info");
    CppLogger::tprint(LOGS_WARNING, "Write warning");
    CppLogger::tprint(LOGS_ERROR, "Write error");

    return 0;
}
```
## Example Output

```log
‹INFO›    Write info
‹WARNING› Write warning
‹ERROR›   Write error
[22:43:13] ‹INFO›    Write info
[22:43:13] ‹WARNING› Write warning
[22:43:13] ‹ERROR›   Write error
```

## Log Levels

* **LOGS_INFO**: Informational messages.  
* **LOGS_WARNING**: Warning messages.  
* **LOGS_ERROR**: Error messages.  