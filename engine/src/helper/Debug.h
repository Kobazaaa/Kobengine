#ifndef KOBENGINE_DEBUG_H
#define KOBENGINE_DEBUG_H

// -- Kobengine Includes --
#include "Event.h"

// -- Standard Library --
#include <string>

namespace kobengine
{
    //? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //? ~~    Severity
    //? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    enum class LogSeverity
    {
        Normal,
        Warning,
        Error
    };

    //? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //? ~~    Debug
    //? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    class Debug
    {
    public:
        //--------------------------------------------------
		//    Constructor
		//--------------------------------------------------
        explicit Debug() = delete;

		//--------------------------------------------------
		//    Logging
		//--------------------------------------------------
        static void Log(const std::string& msg);
        static void LogWarning(const std::string& msg);
        static void LogError(const std::string& msg);

        static inline Event<const std::string&, LogSeverity> OnMessageLogged;
    };
}

#endif // KOBENGINE_DEBUG_H
