#pragma once

#define CREATE_LOG_CATEGORY( name ) gg::CLoggerInstance name (#name) ;
#define GG_LOG( cat, msg, ... ) cat.LogMsg( gg::log_internal::BuildLogMsg( msg , __VA_ARGS__ ) )

#include <string_view>
#include <string>
#include <format>

namespace gg
{
    namespace log_internal
    {
        template< typename ... TArgs >
        std::string BuildLogMsg( std::string_view fmt, TArgs&&... args )
        {
            return std::vformat( fmt, std::make_format_args(args...) );
        }
    }

    class CLoggerInstance
    {
    public:
        CLoggerInstance( const char* name );
        void LogMsg( const std::string& msg );
    private:
        std::string _categoryString;
    };
}