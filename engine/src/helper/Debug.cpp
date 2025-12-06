// -- Kobengine Includes --
#include "Debug.h"


//--------------------------------------------------
//    Logging
//--------------------------------------------------
void kobengine::Debug::Log(const std::string& msg)
{
	OnMessageLogged.Invoke(msg, LogSeverity::Normal);
}
void kobengine::Debug::LogWarning(const std::string& msg)
{
	OnMessageLogged.Invoke(msg, LogSeverity::Warning);
}
void kobengine::Debug::LogError(const std::string& msg)
{
	OnMessageLogged.Invoke(msg, LogSeverity::Error);
}
