#pragma once
///////////////////////////////////////////////////////////////////////
// Demo.cpp - starts the child process with required resources       //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Projects #1, CSE687 - Object Oriented Design         //
// Author:      Lakshmi Harshini Kuchibhotla, Syracuse University,	 //
//              lkuchibh@syr.edu									 //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides the following functionality:
* - starts the test executive process with required resources and demos it
*
* Required Files:
* ---------------
*   Comm.h
*   Message.h
*   TestExecutive.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 11 Oct 2018
* - first release
*
* Planned Additions and Changes:
* ------------------------------
* - none yet
*/
#include "TestExecutive.h"
#include "../CppCommWithFileXfer/MsgPassingComm/Comm.h"
#include "../CppCommWithFileXfer/Message/Message.h"
#include <iostream>
#include <thread>
#include <functional>
#include <windows.h> 


#ifdef TEST_TESTEXECUTIVE

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Please enter the directory for the tests";
	}
	std::string path = argv[1];

	std::shared_ptr<LoggerUtilities::TestLogger> logger = std::shared_ptr<LoggerUtilities::TestLogger>(new LoggerUtilities::TestLogger);
	logger->addStream(&std::cout);
	LoggerUtilities::IHostedLogger * hostedLogger = new LoggerUtilities::HostedLoggger();
	hostedLogger->setLogger(logger);
	TestExecutive testExecutive = TestExecutive(path, hostedLogger);
	testExecutive.LoadDlls();
	testExecutive.LoadDllTestsAndRun();
	delete hostedLogger;
	std::cin.get();
	std::cout << "\n\n";

	return 0;
}

#endif // TEST_TESTEXECUTIVE