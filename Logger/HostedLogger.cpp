#pragma once
/////////////////////////////////////////////////////////////////////////////
// HostedLogger.cpp - Defined functions from loggerResurce                 //
// ver 1.0                                                                 //
//															               //
// Author:      Lakshmi Harshini Kuchibhotla, Syracuse University          //
//              lkuchibh@syr.edu					                       //
/////////////////////////////////////////////////////////////////////////////
#include "LoggerResource.h"

namespace LoggerUtilities 
{
	void HostedLoggger::log(const std::string & msg)
	{
		logger->write(msg);
	}
	void HostedLoggger::setLogger(std::shared_ptr<LoggerUtilities::ILogger> logger)
	{
		this->logger = logger;
	}

}


#ifdef TEST_LOGGER

int main(int argc, char* argv[])
{

	std::shared_ptr<LoggerUtilities::TestLogger> testLogger = std::shared_ptr<LoggerUtilities::TestLogger>(new LoggerUtilities::TestLogger());
	testLogger->addStream(&std::cout);
	
	testLogger->log("testName", "testAuthor", "random");
	testLogger->write("something");

	std::cin.get();
	std::cout << "\n\n";

	return 0;
}

#endif // TEST_LOGGER
