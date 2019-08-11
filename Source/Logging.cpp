#include "Logging.hpp"

#ifndef NDEBUG
LogLevel Log::s_LogLevel = LogLevel::Info;
#else
LogLevel Log::s_LogLevel = LogLevel::Error;
#endif

Log::Log(LogLevel logLevel) :
    m_LogLevel(logLevel)
{
    if(m_LogLevel <= s_LogLevel)
    {
        switch(m_LogLevel)
        {
            case LogLevel::Error:
                std::cout << "[Error] ";
                break;
            case LogLevel::Warning:
                std::cout << "[Warning] ";
                break;
            case LogLevel::Info:
            default:
                std::cout << "[Info] ";
                break;
        }
    }
}

Log::~Log()
{
    std::cout << std::endl;
}

void Log::SetLogLevel(LogLevel logLevel)
{
    s_LogLevel = logLevel;
}