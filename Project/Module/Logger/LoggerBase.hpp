#ifndef LOGGER_BASE_HPP
#define LOGGER_BASE_HPP
#if defined(ERROR) && defined(_WINGDI_) // wingdi.h can have ERROR defined undef if it exists to prevent compile error and set flag to re-enable it afterwards
#undef ERROR
#define ERROR_UNDEF
#endif

#include <time.h>
#include <iomanip>
#include <chrono>
#include <sstream>
#include "LoggerStreams\LogSteam.hpp"
#include <Helpers\String.hpp>
#include <Helpers\Enum\LogLevel.hpp>

namespace EngineModule
{
	namespace Logger
	{
		
		template<class Stream>
		class LoggerBase
		{
			template <class ...Args>
			void logMessageT(const Enums::LogLevel& logLevel, Args&& ... args)
			{
				if ((int)level <= (int)logLevel)
				{
					std::stringstream ss;
					(ss << ... << args);
					log.LogMessage(logLevel, ss.str());
				}
			};

		protected:

			Core::String keyword;

			Enums::LogLevel level;
			Stream log;

			template <class ...Args>
			void logMessage(const Enums::LogLevel& logLevel, Args&& ... args)
			{
				auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
				std::tm tm;
				localtime_s(&tm, &time);

				logMessageT(logLevel, std::put_time(&tm, "%Y-%m-%d %H:%M:%S"), " ", keyword, args...);
			};

		public:
			LoggerBase(Stream s, const Enums::LogLevel level): log(s), level(level), keyword()
			{
					static_assert(std::is_base_of_v<Logger::Streams::LogStream, std::remove_reference_t<Stream>>, "Stream is not a base of LogStream");
			};

			virtual void setLogLevel(const Enums::LogLevel& newLevel)
			{
				Always("Setting new log level: From " + Enums::to_string(level, false) + " to " + Enums::to_string(newLevel, false));
				level = newLevel;
			};

			template <class ...Args>
			void Debug(Args&& ... args)
			{
				logMessage(Enums::LogLevel::DBG, args...);
			};
			template <class ...Args>
			void Info(Args&& ... args)
			{
				logMessage(Enums::LogLevel::INFO, args...);
			};
			template <class ...Args>
			void Fine(Args&& ... args)
			{
				logMessage(Enums::LogLevel::INFO, args...);
			};
			template <class ...Args>
			void Warning(Args&& ... args)
			{
				logMessage(Enums::LogLevel::WARNING, args...);
			};
			template <class ...Args>
			void Error(Args&& ... args)
			{
				logMessage(Enums::LogLevel::ERROR, args...);
			};
			template <class ...Args>
			void Critical(Args&& ... args)
			{
				logMessage(Enums::LogLevel::CRITICAL, args...);
			};
			template <class ...Args>
			void Always(Args&& ... args)
			{
				logMessage(Enums::LogLevel::ALWAYS, args...);
			};

			template <class ...Args>
			void EngineLogging(Core::String& type, Args&& ... args)
			{
				for (std::string::iterator p = type.begin(); type.end() != p; ++p)
					*p = (char)::toupper(*p);
				logMessage(Enums::fromString(type), args...);
			};

			static Core::String fileInfo(const Core::String& fileName, const size_t& line)
			{
				return " - " + fileName + " (" + std::to_string(line) + ")";
			}
		};

	}
}
#ifdef ERROR_UNDEF // re-enable ERROR 0 define for wingdi.h if it was defined
#define ERROR 0
#endif
#endif