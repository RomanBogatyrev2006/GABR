#include "logger.h"
#ifdef GABR_TARGET_WIN
	#include <Windows.h>
#endif

namespace Gabr
{
	// Constructor
	Logger::Logger()
	{
		#ifdef GABR_TARGET_WIN
			SetConsoleOutputCP(CP_UTF8);
			SetConsoleCP(CP_UTF8);

			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			DWORD dwMode = 0;
			GetConsoleMode(hOut, &dwMode);
			dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			SetConsoleMode(hOut, dwMode);
		#endif
	}

	// Destructor
	Logger::~Logger()
	{
		
	}

	// Print text to console (with UTF8 support)
	void Logger::Print(const std::string& text)
	{
		#if defined(GABR_TARGET_WIN)
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			if (hConsole == INVALID_HANDLE_VALUE)
			{
				std::cout << text;
				return;
			}

			int wide_len = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, nullptr, 0);
			std::wstring wide(wide_len, L'\0');
			MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, &wide[0], wide_len);
			DWORD written = 0;
			WriteConsoleW(hConsole, wide.c_str(), (DWORD)wcslen(wide.c_str()), &written, nullptr);
		#else
			std::cout << text;
		#endif
	}

	// Set console text color
	const char* Logger::SetColor(LogSeverity color)
	{
		switch (color)
		{
			case LogSeverity::TRACE:	return "\033[37m";
			case LogSeverity::INFO:		return "\033[94m";
			case LogSeverity::WARN:		return "\033[33m";
			case LogSeverity::ERR:		return "\033[31m";
			case LogSeverity::FATAL:	return "\033[91m";
			default: return "\033[0m";
		}
	}
	
	// Get logger instance
	Logger& Logger::Get()
	{
		static Logger instance;
		return instance;
	}

	// Log message to console
	void Logger::Log(LogSeverity severity, const std::string& message)
	{
		// Getting current time
		time_t raw_time;
		time(&raw_time);
		
		struct tm time_info;
		
		#if defined(GABR_TARGET_WIN)
			localtime_s(&time_info, &raw_time);
		#else
			localtime_r(&raw_time, &time_info);
		#endif

		// Log
		std::ostringstream builder;
		builder << SetColor(severity) <<
			std::setw(2) << std::setfill('0') << time_info.tm_hour <<	":" <<
			std::setw(2) << std::setfill('0') << time_info.tm_min  <<	":" <<
			std::setw(2) << std::setfill('0') << time_info.tm_sec  <<	" " <<
			message << "\033[0m" << std::endl;
		
		Print(builder.str());
	}

	// Create and initialize logger
	Logger* Logger::Create()
	{
		return new Logger();
	}
}