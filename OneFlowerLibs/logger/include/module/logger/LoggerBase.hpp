#ifndef LOGGER_BASE_HPP
#define LOGGER_BASE_HPP
//#if defined(ERROR) && defined(_WINGDI_) // wingdi.h can have ERROR defined undef if it exists to prevent compile error and set flag to re-enable it afterwards
//#undef ERROR
//#define ERROR_UNDEF
//#endif

#include <time.h>
#include <iomanip>
#include <chrono>
#include <sstream>

#include <module\logger\streams\LogSteam.hpp>
#include <utils/common/string.hpp>
#include <module\logger\LogLevel.hpp>

namespace of::module::Logger
{
		
	template<class T_Stream>
	class LoggerBase
	{
		template <class ...Args>
		void logMessageT(const LogLevel& logLevel, Args&& ... args)
		{
			if ((int)level <= (int)logLevel)
			{
				std::stringstream ss;
				(ss << ... << args);
				log.LogMessage(logLevel, ss.str());
			}
		};

	protected:

		common::String keyword;

		LogLevel level;
		typename T_Stream log;

		template <class ...Args>
		void logMessage(const LogLevel& logLevel, Args&& ... args)
		{
			auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			std::tm tm;
			localtime_s(&tm, &time);

			logMessageT(logLevel, std::put_time(&tm, "%Y-%m-%d %H:%M:%S"), " ", keyword, args...);
		};

	public:
		LoggerBase(T_Stream s, const LogLevel level): log(s), level(level), keyword()
		{
			static_assert(std::is_base_of_v<Logger::Streams::LogStream, std::remove_reference_t<T_Stream>>, "Stream is not a base of LogStream");
		};

		virtual void setLogLevel(const LogLevel& newLevel)
		{
			Always("Setting new log level: From " + to_string(level, false) + " to " + to_string(newLevel, false));
			level = newLevel;
		};

		template <class ...Args>
		void Debug(Args&& ... args)
		{
			logMessage(LogLevel::DBG, args...);
		};
		template <class ...Args>
		void Info(Args&& ... args)
		{
			logMessage(LogLevel::INFO, args...);
		};
		template <class ...Args>
		void Fine(Args&& ... args)
		{
			logMessage(LogLevel::INFO, args...);
		};
		template <class ...Args>
		void Warning(Args&& ... args)
		{
			logMessage(LogLevel::WARNING, args...);
		};
		template <class ...Args>
		void Error(Args&& ... args)
		{
			logMessage(LogLevel::ERROR, args...);
		};
		template <class ...Args>
		void Critical(Args&& ... args)
		{
			logMessage(LogLevel::CRITICAL, args...);
		};
		template <class ...Args>
		void Always(Args&& ... args)
		{
			logMessage(LogLevel::ALWAYS, args...);
		};

		template <class ...Args>
		void EngineLogging(const common::String& type, Args&& ... args)
		{
			common::String upper = type;
			for (common::String::iterator p = upper.begin(); upper.end() != p; ++p)
				*p = (char)::toupper(*p);
			logMessage(fromString(upper), args...);
		};

		static common::String fileInfo(const common::String& fileName, const size_t& line)
		{
			return " - " + fileName + " (" + std::to_string(line) + ")";
		}
	};

}
//#ifdef ERROR_UNDEF // re-enable ERROR 0 define for wingdi.h if it was defined
//#define ERROR 0
//#endif
#endif