#pragma once
///////////////////////////////////////////////////////////////////////
// RequirementsDemo.h - All the tests that show the requirements     //
//																	 //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Most Projects, CSE687 - Object Oriented Design       //
// Author:      Lakshmi Harshini Kuchibhotla, Syracuse University,	 //
//              lkuchibh@syr.edu									 //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides classes that shows the project requirements
*
* Required Files:
* ---------------
*   ITest.h
*   TestHelpers.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 11 Nov 2018
* - first release
*
* Planned Additions and Changes:
* ------------------------------
* - none planned
*/

#include<iostream>
#include "../TestUtilities/ITest.h"
#include "../TestUtilities/TestHelpes.h"

using Path = std::string;
using Message = std::string;
using Line = size_t;
using File = std::string;
using Files = std::vector<File>;


class TestContainer : public ITests
{
public:
	// Inherited via ITests
	virtual DLL_DECL std::vector<ITest*> tests() override
	{
		return allTests;
	};
public:
	std::vector<ITest*> allTests;
};

/*
Test Requirement 1 is to use Visual Studio 2017 and its C++ Windows Console Projects, as provided in the ECS computer labs.
This requirement has been fulfilled and taken care of.
*/
class TestRequirement1 : public ITest
{
	/*
	*  Test Description:
	*    Demonstrates use of C++
	*  Test Procedure:
	*  - Displays C++ files in project directory
	*/
private:
	const std::string path_;
	LoggerUtilities::IHostedLogger* _pRes;
public:
	TestRequirement1(const std::string& path) : path_(path) {}
	bool test()
	{
		Message msg = "Req #1 - Use C++";
		Path path = path_ + "/TestUtilities";
		return TestUtilities::TestHelpers::showDirContents(path, msg);
	}

	// Inherited via ITest
	virtual DLL_DECL std::string name() override
	{
		return "Test Req 1";
	}
	virtual DLL_DECL std::string author() override
	{
		return "Harshini";
	}
	virtual DLL_DECL void acceptHostedResource(LoggerUtilities::IHostedLogger * pRes) override
	{
		_pRes = pRes;
	};
};

/*
Shall use Windows Presentation Foundation (WPF) for all user display.
This Requirement has been met as GUI project is dependent on WPF.
*/
class TestRequirement2a : public ITest
{
	/*
	*  Test Description:
	*    Demonstrates use of WPF
	*  Test Procedure:
	*  - Displays files of project source code that use.
	*/
private:
	const std::string path_;
	LoggerUtilities::IHostedLogger* _pRes;
public:
	TestRequirement2a(const std::string& path) : path_(path) {}
	bool test()
	{
		Message msg = "Req #2a - use WPF";
		Path fileSpec = path_ + "/GUI";
		return TestUtilities::TestHelpers::showDirContents(fileSpec, msg);
	}

	// Inherited via ITest
	virtual DLL_DECL std::string name() override
	{
		return "Test Req 2a";
	}
	virtual DLL_DECL std::string author() override
	{
		return "Harshini";
	}
	virtual DLL_DECL void acceptHostedResource(LoggerUtilities::IHostedLogger * pRes) override
	{
		_pRes = pRes;
	};
};

class TestRequirement2b : public ITest
{
	/*
	*  Test Description:
	*    Demonstrates use of WPF
	*  Test Procedure:
	*  - show files that have wpf code.
	*  - The demo has the WPF UI
	*/
private:
	const std::string path_;
	LoggerUtilities::IHostedLogger* _pRes;

public:
	TestRequirement2b(const std::string& path) : path_(path) {}
	bool test()
	{
		Message msg = "Req #2b - use WPF for user display";
		Path fileSpec = path_ + "/GUI/MainWindow.xaml";
		return TestUtilities::TestHelpers::showFileLines(fileSpec, 1, 10, msg);
	}
	// Inherited via ITest
	virtual DLL_DECL std::string name() override
	{
		return "Test Req 2b";
	}
	virtual DLL_DECL std::string author() override
	{
		return "Harshini";
	}
	virtual DLL_DECL void acceptHostedResource(LoggerUtilities::IHostedLogger * pRes) override
	{
		_pRes = pRes;
	};
};


/*
Shall assemble the working parts from Projects #1, #2, and #3
into a Client-Server configuration. Unlike conventional Client-Server
architectures, the Client need not wait for a reply for a TestRequest
from the TestHarness before sending additional TestRequests.
*/

class TestRequirement3 : public ITest
{
	/*
	*  Test Description:
	*   Demonstrates That the client is non blocking
	*  Test Procedure:
	*  - Already shown in the demo
	*/
public:
	TestRequirement3(const std::string& path) : path_(path) {}

	DLL_DECL bool test()
	{
		pRes_->log("Req #3 - Demonstrates That the client is non blocking \n\n");
		pRes_->log("This is already is the client demo that executed. \n\n");
		return true;
	}
	DLL_DECL std::string name()
	{
		return "TestRequirement3";
	}
	DLL_DECL std::string author()
	{
		return "Harhini";
	}
	DLL_DECL void acceptHostedResource(LoggerUtilities::IHostedLogger * pRes)
	{
		pRes_ = pRes;
	}
private:
	LoggerUtilities::IHostedLogger * pRes_ = nullptr;
	const std::string path_ = "../";
};
/*
 Shall provide a Graphical User Interface (GUI) for the client that supports 
 selecting test libraires to send for testing, and supports displaying the test results.
*/

class TestRequirement4 : public ITest
{
	/*
	*  Test Description:
	*   Demonstrates the provision selecting dlls and send the test request. 
	*   Also shows the test results
	*  Test Procedure:
	*  - Already shown in the demo
	*/
public:
	TestRequirement4(const std::string& path) : path_(path) {}

	DLL_DECL bool test()
	{
		pRes_->log("Req #4 - Demonstrates the provision selecting dlls and send the test request.  \n\n");

		pRes_->log("This is already is the client demo that executed. \n\n");
		return true;
	}
	DLL_DECL std::string name()
	{
		return "TestRequirement4";
	}
	DLL_DECL std::string author()
	{
		return "Harhini";
	}
	DLL_DECL void acceptHostedResource(LoggerUtilities::IHostedLogger * pRes)
	{
		pRes_ = pRes;
	}
private:
	LoggerUtilities::IHostedLogger * pRes_ = nullptr;
	const std::string path_ = "../";
};

/*
Shall provide message designs appropriate for this application. 
All messages are instances of the same Message class, 
but have a specified set of attributes and body contents suited for the intended task.
*/


class TestRequirement5 : public ITest
{
	/*
	*  Test Description:
	*    Demonstrates the provision of message designs appropriate for this application
	*  Test Procedure:
	*  - Displays lines of Client that uses appropriate attributes for message class 
	*/
public:
	TestRequirement5(const std::string& path) : path_(path) {}

	DLL_DECL bool test()
	{
		Message msg = "Req #5 - Demonstrates the provision of message designs appropriate for this application - see lines 150 and 151";
		Path path = path_ + "/Translater/Translater.h";
		TestUtilities::TestHelpers::showFileLines(path, 132, 152, msg);
		return true;
	}
	DLL_DECL std::string name()
	{
		return "TestRequirement5";
	}
	DLL_DECL std::string author()
	{
		return "Harhini";
	}
	DLL_DECL void acceptHostedResource(LoggerUtilities::IHostedLogger * pRes)
	{
		pRes_ = pRes;
	}
private:
	LoggerUtilities::IHostedLogger * pRes_ = nullptr;
	const std::string path_ = "../";
};

/*
Shall support sending TestRequest messages from Client to TestHarness Server.
*/

class TestRequirement6 : public ITest
{
	/*
	*  Test Description:
	*   Shall support sending TestRequest messages from Client to TestHarness Server.
	*  Test Procedure:
	*  - Displays lines of client where the tests requests are sent.
	*/
public:
	TestRequirement6(const std::string& path) : path_(path) {}

	DLL_DECL bool test()
	{
		Message msg = "Req #6a - Shall support sending TestRequest messages from Client to TestHarness Server, This is also shown in the demo";
		Path path = path_ + "/Translater/Translater.h";
		TestUtilities::TestHelpers::showFileLines(path, 132, 152, msg);
		return true;
	}
	DLL_DECL std::string name()
	{
		return "TestRequirement6";
	}
	DLL_DECL std::string author()
	{
		return "Harhini";
	}
	DLL_DECL void acceptHostedResource(LoggerUtilities::IHostedLogger * pRes)
	{
		pRes_ = pRes;
	}
private:
	LoggerUtilities::IHostedLogger * pRes_ = nullptr;
	const std::string path_ = "../";
};


/*
Shall support correctly executing each TestRequest, as a sequence of tests, with each TestRequest running in its own Process Pool child process.
*/

class TestRequirement7 : public ITest
{
	/*
	*  Test Description:
	*   Shall support correctly executing each TestRequest, as a sequence of tests, with each TestRequest running in its own Process Pool child process.
	*  Test Procedure:
	*  - Shown in the console output during the demo
	*/
public:
	TestRequirement7(const std::string& path) : path_(path) {}

	DLL_DECL bool test()
	{
		pRes_->log("Req #7 - Shall support correctly executing each TestRequest, as a sequence of tests, with each TestRequest running in its own Process Pool child process.  \n\n");

		pRes_->log("Shown in the console output during the demo \n\n");
		return true;
	}
	DLL_DECL std::string name()
	{
		return "TestRequirement7";
	}
	DLL_DECL std::string author()
	{
		return "Harhini";
	}
	DLL_DECL void acceptHostedResource(LoggerUtilities::IHostedLogger * pRes)
	{
		pRes_ = pRes;
	}
private:
	LoggerUtilities::IHostedLogger * pRes_ = nullptr;
	const std::string path_ = "../";
};


class TestRequirement8 : public ITest
{
	/*
	*  Test Description:
	*  Shall support sending test results, via results messages, from the child process executing the tests to the Client that made the request.
	*  Test Procedure:
	*  - Displays the lines where the test results are sent
	*/
public:
	TestRequirement8(const std::string& path) : path_(path) {}

	DLL_DECL bool test()
	{
		Message msg = "Req #8a -  sending test results, via results messages, from the child process executing the tests to the Client that made the request.";
		Path path = path_ + "/TestHarness/TestExecutive.cpp";
		TestUtilities::TestHelpers::showFileLines(path, 99, 110, msg);

		pRes_->log("Req #8b - Show that the client can recieve such messages\n\n");

		pRes_->log("Shown as a txt file output during the demo\n\n ");
		
		return true;
	}
	DLL_DECL std::string name()
	{
		return "TestRequirement8";
	}
	DLL_DECL std::string author()
	{
		return "Harhini";
	}
	DLL_DECL void acceptHostedResource(LoggerUtilities::IHostedLogger * pRes)
	{
		pRes_ = pRes;
	}
private:
	LoggerUtilities::IHostedLogger * pRes_ = nullptr;
	const std::string path_ = "../";
};

class TestRequirement9 : public ITest
{
	/*
	*  Test Description:
	*  Shall demonstrate correct test operations for two or more concurrent clients. 
	*  You need to ensure that testing takes enough time to ensure that more than one child process is running at the same time.
	*  Test Procedure:
	*  - Included a time taking test in the demo
	*/
public:
	TestRequirement9(const std::string& path) : path_(path) {}

	DLL_DECL bool test()
	{
		pRes_->log("Req #9 - demonstrate correct test operations for two or more concurrent clients \n\n");

		pRes_->log("Included a time taking test in the demo \n\n");
		
		return true;
	}
	DLL_DECL std::string name()
	{
		return "TestRequirement9";
	}
	DLL_DECL std::string author()
	{
		return "Harhini";
	}
	DLL_DECL void acceptHostedResource(LoggerUtilities::IHostedLogger * pRes)
	{
		pRes_ = pRes;
	}
private:
	LoggerUtilities::IHostedLogger * pRes_ = nullptr;
	const std::string path_ = "../";
};

class TestRequirement10 : public ITest
{
	/*
	*  Test Description:
	*   Shall include an automated unit test suite that demonstrates your Clients and TestHarness satisfy all of the functional requirements, above.
	*  Test Procedure:
	*  - The demo run is currrently on the requrements 
	*/
public:
	TestRequirement10(const std::string& path) : path_(path) {}

	DLL_DECL bool test()
	{
		pRes_->log("Req #9 - Shall include an automated unit test suite that demonstrates your Clients and TestHarness satisfy all of the functional requirements, above. \n\n");

		pRes_->log("The demo run demonstrates the requrements ");

		return true;
	}
	DLL_DECL std::string name()
	{
		return "TestRequirement10";
	}
	DLL_DECL std::string author()
	{
		return "Harhini";
	}
	DLL_DECL void acceptHostedResource(LoggerUtilities::IHostedLogger * pRes)
	{
		pRes_ = pRes;
	}
private:
	LoggerUtilities::IHostedLogger * pRes_ = nullptr;
	const std::string path_ = "../";
};