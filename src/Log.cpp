#include "Log.hpp"
#include <iostream>
#include <cstdarg>

#define BUF_LENGTH		1024
#define COLOR(c)		"\033[" << c << "m"


bool Log::print_debug = false;


void Log::print(int color, const char* pre, const char* log)
{
	std::cout << COLOR(color) << "[" << pre << "]" << COLOR(49) << " : " << log << "\r\n";
}


void Log::debug(const char* fmt, ...)
{
	if (!Log::print_debug)
		return;
		
	/* args parsing */
	va_list arglist;
	char buff[BUF_LENGTH];
	va_start(arglist, fmt);
	vsnprintf(buff, BUF_LENGTH, fmt, arglist);
	va_end(arglist);

	print(47, "debug", buff);
}


void Log::info(const char* fmt, ...)
{
	/* args parsing */
	va_list arglist;
	char buff[BUF_LENGTH];
	va_start(arglist, fmt);
	vsnprintf(buff, BUF_LENGTH, fmt, arglist);
	va_end(arglist);

	print(42, "info", buff);
}


void Log::warn(const char* fmt, ...)
{
	/* args parsing */
	va_list arglist;
	char buff[BUF_LENGTH];
	va_start(arglist, fmt);
	vsnprintf(buff, BUF_LENGTH, fmt, arglist);
	va_end(arglist);

	print(43, "warn", buff);
}


void Log::error(const char* fmt, ...)
{
	/* args parsing */
	va_list arglist;
	char buff[BUF_LENGTH];
	va_start(arglist, fmt);
	vsnprintf(buff, BUF_LENGTH, fmt, arglist);
	va_end(arglist);

	print(41, "error", buff);
}


void Log::critical(const char* fmt, ...)
{
	/* args parsing */
	va_list arglist;
	char buff[BUF_LENGTH];
	va_start(arglist, fmt);
	vsnprintf(buff, BUF_LENGTH, fmt, arglist);
	va_end(arglist);

	print(45, "critical", buff);
}
