#pragma once
#include <api.h>

namespace Gabr
{
	// Log severity levels
	enum class LogSeverity
	{
		TRACE	= 0x01,
		INFO	= 0x02,
		WARN	= 0x03,
		ERR		= 0x04,
		FATAL	= 0x05
	};

	// Logger class (This is singleton class)
	class GABR_API Logger
	{
	public:
		// Get logger instance
		static Logger& Get();


		// Log message to console
		void Log(LogSeverity severity, const std::string& message);

		// Create and initialize logger
		static Logger* Create();

	private:
		// Constructor
		Logger();

		// Destructor
		~Logger();


		// Delete copy constructor and assignment operator to prevent copying
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;


		// Print text to console (with UTF8 support)
		static void Print(const std::string& text);

		// Set console text color
		const char* SetColor(LogSeverity color);
	};
}
