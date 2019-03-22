#pragma once
///////////////////////////////////////////////////////////////////////
// Logger.h - Provides a Logger implementaion with multiple streams  //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Projects #1, CSE687 - Object Oriented Design         //
// Author:      Lakshmi Harshini Kuchibhotla, Syracuse University,	 //
//              lkuchibh@syr.edu									 //
// Source:		Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides classes:
* - Logger - Basic implementation for the Logger using vector streams and a default stream to show errors.
* - TestLogger - This implementation of the logger allows us to log the the test information include the time-date, name and author.
*
* Maintenance History:
* --------------------
* ver 1.0 : 3 Sep 2018
* - first release
*
* Planned Additions and Changes:
* ------------------------------
* - none yet
*/
#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <time.h>

namespace LoggerUtilities
{

	class ILogger
	{
	public:
		virtual void addStream(std::ostream* pStream) = 0;
		virtual void write(const std::string& text) = 0;
	};

	class Logger :public ILogger
	{
	public:
		virtual void addStream(std::ostream* pStream) override
		{
			streams_.push_back(pStream);
		}

		virtual void write(const std::string& text) override
		{
			for (auto pStrm : streams_)
				*pStrm << text.c_str();
		}

		// Overload the << operator to provide a ostream like behaviour;
		Logger& operator << (const std::string& text)
		{
			write(text);
			return *this;
		}

	private:
		std::vector<std::ostream*> streams_;
	};

	class TestLogger : public Logger
	{
	public:
		// This function was written with the help of some classmates and internet
		// reference: https://stackoverflow.com/questions/17223096/outputting-date-and-time-in-c-using-stdchrono
		//
		std::string GetTime()
		{
			auto timeNow = std::chrono::system_clock::now();
			std::time_t t = std::chrono::system_clock::to_time_t(timeNow);
			struct tm buf;
			localtime_s(&buf, &t);
			std::stringstream ss;
			ss << std::put_time(&buf, "%Y-%m-%d %X");
			return ss.str();
		}

		//The log just takes the below inputs name, author and text then formats it and prints.
		void log(const std::string& name, const std::string& author, const std::string& text)
		{
			write("\n\n--->  " + name + "\n******************************** \n\n" + "Author: " + author + ", Time of execution: " + GetTime() + "\n" + text + "\n\n\n");
		}
	};
}
