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