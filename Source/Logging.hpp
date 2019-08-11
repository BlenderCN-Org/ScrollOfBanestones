#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <mutex>
#include <iostream>
#include <string>

enum LogLevel
{
    Error,
    Warning,
    Info,
};

class Log
{
public:
    Log(LogLevel logLevel);
    ~Log();

    template<typename T>
    Log& operator<<(T&& rhs)
    {
        if(m_LogLevel <= s_LogLevel)
        {
            std::cout << std::forward<T>(rhs);
        }
        return *this;
    }

    static void SetLogLevel(LogLevel logLevel);
private:
    LogLevel m_LogLevel;
    static LogLevel s_LogLevel;
};

#endif // !LOGGING_HPP