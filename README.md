## Journaling Application

This is a simple C++ logging library for journaling messages with various log levels such as INFO, WARNING, and ERROR. It provides functionality to log messages to the console as well as to a file.

## Check List for future contentes
- [ ] Show Process Id
- [ ] Show Thread Id

## Installation

To use this logging library in your project, simply include the CppLogger.hpp header file and ensure that the CppLogger.cpp implementation file is compiled along with your project.

## Usage

Here's how you can use the logging library in your C++ application:

```cpp
#include "CppLogger.hpp"

int main() {
    // Initialize the logger with a log name
    CL::init("DEBUG#1");

    // Toggle logging to a file
    CL::toggleJournaling();

    // Log various messages with different severity levels
    CL::print(LOGS_INFO, "This is an informational message");
    CL::print(LOGS_WARNING, "This is a warning message");
    CL::print(LOGS_ERROR, "This is an error message");

    // Log messages with timestamps
    CL::tprint(LOGS_INFO, "This is a timestamped informational message");
    CL::tprint(LOGS_WARNING, "This is a timestamped warning message");
    CL::tprint(LOGS_ERROR, "This is a timestamped error message");

    // Update log level for a custom level
    CL::updateLevel(3, "OTHER");
    CL::tprint(3, "This is a message with custom log level (OTHER)");

    // Disable logging to a file
    CL::toggleJournaling();

    // Log another informational message after disabling journaling
    CL::tprint(LOGS_INFO, "This is another informational message after disabling journaling");

    // Add another log level
    CL::updateLogName("DEBUG#2"); // Change log name
    CL::updateLevel(4, "OTHER TEST"); // Add another custom log level
    CL::tprint(4, "This is a message with a new custom log level (OTHER TEST)");

    return 0;
}
```
## Example Output

```log
==== CppLogger [DEBUG#1] ====
[13:57:49] ‹INFO›    This is another informational message after disabling journaling
==== CppLogger [DEBUG#2] ====
[13:57:49] ‹OTHER TEST› This is a message with a new custom log level (OTHER TEST)
```

# Default Logs Levels
* LOGS_INFO: Informational messages.
* LOGS_WARNING: Warning messages.
* LOGS_ERROR: Error messages.
  
# Customize
You can change the space between the level text and the message with :
```cpp
void setHeaderSpace(const int spaceSize);
```
You can change the name of the log file with :
```cpp
#define LOGS_FILE_NAME "logs.txt"
```
You can change the style of the characters surrounding the name of the log level and timestamps with :
```cpp
//  Log level name decorator
#define LOGS_HEADER_AFTERDECO "\u203A"
#define LOGS_HEADER_BEFOREDECO "\u2039"

//  Timestamps decorator
#define LOGS_TIME_AFTERDECO "]"
#define LOGS_TIME_BEFOREDECO "["
```
***Warning ! If you add decorators longer than 1 character, you will have to adjust the line of code in :***
```cpp
void CppLogger::updateLevel(const char levelId, const std::string levelStr){
    ...
    const int headerSize = levelStr.size() + 2; // << HERE (+2 Because there are only 2 characters surrounding the log level name)
    ...
}
```
