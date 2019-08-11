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
                std::cerr << "[Error] ";
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
    if(m_LogLevel == LogLevel::Error)
    {
        std::cerr << std::endl;
    }
    else
    {
        std::cout << std::endl;
    }   
}

void Log::SetLogLevel(LogLevel logLevel)
{
    s_LogLevel = logLevel;
}