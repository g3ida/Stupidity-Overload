#ifndef _DEF_LOG_H_
#define _DEF_LOG_H_

#define LOGGING

#ifdef LOGGING

	#include "Logger.h"

	#define LOG Logger::print<Logger::Severity::debug>
	#define LOG_ERR Logger::print<Logger::Severity::error>
	#define LOG_WARN Logger::print<Logger::Severity::warning>

#else

	#define LOG(...)
	#define LOG_ERR(...)
	#define LOG_WARN(...)

#endif

#endif //_DEF_LOG_H_
