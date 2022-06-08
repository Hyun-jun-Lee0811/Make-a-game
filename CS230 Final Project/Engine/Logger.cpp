/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Logger.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date:Spring 2022/4/16
-----------------------------------------------------------------*/
#include <iostream>
#include "Logger.h"

CS230::Logger::Logger(Logger::Severity severity, bool useConsole, std::chrono::system_clock::time_point startTime) : minLevel(severity), outStream("Trace.log")
, startTime_(startTime)
{
	if (useConsole == true)
	{
		outStream.set_rdbuf(std::cout.rdbuf());
	}
}

CS230::Logger::~Logger()
{
	outStream.flush();
	outStream.close();
}

void CS230::Logger::Log(CS230::Logger::Severity severity, std::string message)
{
	if (severity >= minLevel)
	{
		outStream.precision(4);
		outStream << '[' << std::fixed << GetSecondsSinceStart() << "]\t";

		switch (severity)
		{
		case Severity::Error:
			outStream << "Error" << '\t' << message << '\n';
			break;
		case Severity::Event:
			outStream << "Event" << '\t' << message << '\n';
			break;
		case Severity::Debug:
			outStream << "Debug" << '\t' << message << '\n';
			break;
		case Severity::Verbose:
			outStream << "Verb" << '\t' << message << '\n';
			break;
		}
	}
}