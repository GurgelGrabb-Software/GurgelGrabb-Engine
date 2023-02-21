#include "GG/Core/Utility/Logging.h"

#include <iostream>

gg::CLoggerInstance::CLoggerInstance( const char* name )
    : _categoryString(name)
{
}

void gg::CLoggerInstance::LogMsg( const std::string& msg )
{
    std::cout << "[" << _categoryString << "]:" << msg << std::endl;
}