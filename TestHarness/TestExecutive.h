#pragma once
///////////////////////////////////////////////////////////////////////
// TestExecutive.h - Provides a test executive that runs a collection//
//					 of tests										 //
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
* - TestExecutive - Basic implementation for the executive to direct the test loading and execution
*
* Required Files:
* ---------------
*   ITest.h
*   LoggerResource.h
*   FileSystem.h
*   StringUtilities.h
*   DllLoader.h
*   TestExecutor.h
*   Base64Helper.h
*   Comm.h
*   Message.h
*   TestRequest.h
*
* Maintenance History:
* --------------------
* ver 2.0 : 11 Nov 2018
* - Added comm and messages to send the results
* ver 1.0 : 11 Oct 2018
* - first release
*
* Planned Additions and Changes:
* ------------------------------
* - none yet
*/
#pragma once
#include <string>
#include <vector>
#include "../TestUtilities/ITest.h"
#include "../Logger/LoggerResource.h"
#include "../Utilities/FileSystem/FileSystem.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../TestLoader/DllLoader.h"
#include "../TestExecutor/TestExecutor.h"
#include "../CppCommWithFileXfer/MsgPassingComm/Comm.h"
#include "../CppCommWithFileXfer/Message/Message.h"
#include "../TestUtilities/TestRequest.h"
#include "../TestUtilities/Base64Helper.h"

using namespace MsgPassingCommunication;

class TestExecutive
{
public:
	TestExecutive(std::string path, EndPoint self, EndPoint harness, Comm& comm);
	~TestExecutive();
	void ReadyForNextTest();
	void RecieveTests();
	void LoadDlls();
	void LoadDllTestsAndRun();
	void sendResult(std::string log);
	void RunTests(std::vector<ITest*>);
private:
	std::string directoryPath;
	std::stringstream stringStream;
	EndPoint self;
	EndPoint client;
	EndPoint harness;
	TestRequest currentTestRequest;
	Comm& comm;
	std::vector<std::string> dlls;
	LoggerUtilities::IHostedLogger* _hostedLogger;
};
