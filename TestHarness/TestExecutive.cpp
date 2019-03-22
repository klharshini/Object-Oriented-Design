
#pragma once
/////////////////////////////////////////////////////////////////////////////
// TestExecutor.h - Defined functions from TestExecutor.h                  //
// ver 1.0                                                                 //
//															               //
// Author:      Lakshmi Harshini Kuchibhotla, Syracuse University          //
//              lkuchibh@syr.edu					                       //
/////////////////////////////////////////////////////////////////////////////

#include "TestExecutive.h"
#include "../CppCommWithFileXfer/MsgPassingComm/Comm.h"
#include "../CppCommWithFileXfer/Message/Message.h"
#include <iostream>
#include <thread>
#include <functional>
#include <windows.h> 

TestExecutive::TestExecutive(std::string path, EndPoint s, EndPoint h, Comm & c)
	: directoryPath(path), self(s), harness(h), comm(c)
{
	comm.setSendFilePath("./");
	comm.start();
	std::shared_ptr<LoggerUtilities::TestLogger> logger = std::shared_ptr<LoggerUtilities::TestLogger>(new LoggerUtilities::TestLogger);
	logger->addStream(&std::cout);
	_hostedLogger = new LoggerUtilities::HostedLoggger();
	_hostedLogger->setLogger(logger);
	ReadyForNextTest();
	RecieveTests();
	//dlls.push_back("../HarnessComposer/dllFiles/DemoProjectRequirements.dll");
	//LoadDllTestsAndRun();
}

TestExecutive::~TestExecutive()
{
	comm.stop();
}

void TestExecutive::ReadyForNextTest()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	Message msg(harness, self);
	msg.name("TestExecutive");
	msg.attribute("status", "ready");
	comm.postMessage(msg);
}

void TestExecutive::RecieveTests()
{
	while (true)
	{
		Message msg;
		msg = comm.getMessage();
		if (msg.command() == "stop")
			break;
		currentTestRequest = TestRequest::fromString(msg.value("testRequest"));
		client = msg.from();
		dlls = currentTestRequest.request();
		LoadDllTestsAndRun();
	}
}

void TestExecutive::LoadDlls()
{
	dlls = FileSystem::Directory::getFiles(directoryPath, "*.dll");
}

void TestExecutive::LoadDllTestsAndRun()
{
	stringStream << "\n ========================================================================================";
	stringStream << "\n\n  Test " + currentTestRequest.name() + " Postted by " + currentTestRequest.author();
	stringStream << "\n ========================================================================================";
	for (std::string dllPath : dlls)
	{
		DllLoader loader = DllLoader();
		bool isLoaded = loader.loadAndExtract(dllPath);
		if (!isLoaded)
		{
			stringStream << "\n \n -----> Tests not loaded from the dll please verify the dll \n \n";
			std::cout << stringStream.str();
			std::string res = b64encode(stringStream.str());
			sendResult(res);
			return;
		}
		std::vector<ITest*> tests = loader.tests();

		for (ITest* test : tests)
		{
			test->acceptHostedResource(_hostedLogger);
		}

		RunTests(tests);
	}
	std::string res = b64encode(stringStream.str());
	sendResult(res);
	//sendResult(stringStream.str());
	ReadyForNextTest();
}

void TestExecutive::sendResult(std::string log)
{
	Message msg;
	msg.to(client);
	msg.from(self);
	msg.name("Test result");
	msg.attribute("requestName", currentTestRequest.name());
	msg.attribute("log", log);
	comm.postMessage(msg);
}

void TestExecutive::RunTests(std::vector<ITest*> tests)
{
	std::shared_ptr<LoggerUtilities::TestLogger> testLogger = std::shared_ptr<LoggerUtilities::TestLogger>(new LoggerUtilities::TestLogger());
	testLogger->addStream(&std::cout);
	testLogger->addStream(&stringStream);
	TestExecutor executor = TestExecutor(testLogger);
	executor.executeAllTests(tests);
}

using namespace MsgPassingCommunication;

void RecieveMessage(Comm& comm) {
	Message msg;

	while (true)
	{
		msg = comm.getMessage();
		std::cout << "\n  Peer2 recvd  message \"" << msg.name() << "\"";
		if (msg.command() == "stop")
			break;
	}
}

/*<----- starts the child process with required resources---->*/
int main(int argc, char* argv[])
{
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	if (argc < 2)
	{
		std::cout << "Please enter the directory for the tests";
	}
	std::string path = argv[1];

	std::cout << "\n  Starting TestExecutive";
	std::cout << "\n ===============================================";

	std::string port;
	if (argc < 3)
	{
		std::cout << "\n No port given for Executive, using the value 8083";
		port = "8083";
	}
	else
		port = argv[2];


	EndPoint harnessEp;
	std::string endPoint;
	if (argc < 4)
	{
		std::cout << "\n address for the test harness is not given";
		return 1;
	}
	endPoint = argv[3];
	harnessEp = EndPoint::fromString(endPoint);
	std::stringstream convert(port);
	int port_int = 0;
	convert >> port_int;

	EndPoint ep("localhost", port_int);
	Comm comm(ep, "TestExecutive" + port);

	TestExecutive testExecutive(path, ep, harnessEp, comm);

	std::cin.get();
	std::cout << "\n\n";

	return 0;
}
