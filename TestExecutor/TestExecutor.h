#pragma once
///////////////////////////////////////////////////////////////////////
// TestExecutor.h - Provides a test executor that runs a collection  //
//					of tests										 //
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
* - TestExecutor - Basic implementation for the executor to run the tests and log
*
* Required Files:
* ---------------
*   ITest.h
*   Logger.h
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
#include <memory>
#include "../Logger/Logger.h"
#include "../TestUtilities/ITest.h"
class TestExecutor
{
public:
	TestExecutor(std::shared_ptr<LoggerUtilities::ILogger> logger);
	bool executeAllTests(std::vector<ITest*> tests);
	bool execute(std::shared_ptr<ITest> pTest);
	void log(const std::string & name, const std::string & author, const bool & res);
private:
	std::shared_ptr<LoggerUtilities::ILogger> pLog;
};
//----< execute tests in the context of a try-catch block >----------
