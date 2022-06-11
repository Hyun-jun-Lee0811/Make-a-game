/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: Logger.h
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/4/16
-----------------------------------------------------------------*/
#pragma once
#include <string>
#include <fstream>
#include <chrono>

namespace CS230
{
	class Logger
	{
	public:
		enum class Severity
		{
			Verbose,
			Debug,
			Event,
			Error,
		};

		void LogError(std::string text) { Log(Severity::Error, text); }
		void LogEvent(std::string text) { Log(Severity::Event, text); }
		void LogDebug(std::string text) { Log(Severity::Debug, text); }
		void LogVerbose(std::string text) { Log(Severity::Verbose, text); }

		Logger(Severity severity, bool useConsole, std::chrono::system_clock::time_point startTime);
		~Logger();
	private:
		void Log(Severity, std::string displayText);
		std::ofstream outStream;
		Severity minLevel;
		std::chrono::system_clock::time_point startTime_;

		double GetSecondsSinceStart()
		{
			return std::chrono::duration<double>(std::chrono::system_clock::now() - startTime_).count();
		}
	};
}