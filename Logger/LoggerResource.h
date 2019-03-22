#pragma once
#pragma once
///////////////////////////////////////////////////////////////////////
// LoggerResource.h - Provides a LoggerResource implementation that  //
//					  can hold a Logger								 //
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
* - IHostedLogger - Provides an interface IHostedLogger.
* - HostedLogger - This implementation of the IHostedLogger provides a basic implementaion of the abstractions in the interface.
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
#include <string>
#include "../Logger/Logger.h"
namespace LoggerUtilities
{
	class IHostedLogger
	{
	public:
		virtual ~IHostedLogger() {}
		virtual void log(const std::string& msg) = 0;
		virtual void setLogger(std::shared_ptr<ILogger> logger) = 0;
	};

	class HostedLoggger : public IHostedLogger
	{
	public:
		// Inherited via IHostedLogger
		virtual void log(const std::string & msg) override;
		virtual void setLogger(std::shared_ptr<ILogger> logger) override;
	private:
		std::shared_ptr<LoggerUtilities::ILogger> logger;
	};

}
