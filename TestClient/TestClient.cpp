#pragma once
///////////////////////////////////////////////////////////////////////
// TestClienbt.cpp - A client that sends test requests and files	 //
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
* This package provides Methods that register the tests to the Harness and recieve the results
*
* Required Files:
* ---------------
*   Comm.h
*   TestRequest.h
*   FileSystem.h
*   Base64Helper.h
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

#include "../CppCommWithFileXfer/MsgPassingComm/Comm.h"
#include "../TestUtilities/TestRequest.h"
#include <iostream>
#include <thread>
#include <functional>
#include <windows.h> 
#include "../Utilities/FileSystem/FileSystem.h"
#include "../TestUtilities/Base64Helper.h"

using namespace MsgPassingCommunication;

void sendMessage(Comm& comm, EndPoint source, EndPoint dest) {

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	Message msg1;
	msg1.to(dest);
	msg1.from(source);
	msg1.value("sendingFile");
	msg1.name("File - SampleTests.dll");
	msg1.file("SampleTests.dll");
	comm.postMessage(msg1);
	
	Message msg2;
	msg2.to(dest);
	msg2.from(source);
	msg2.value("sendingFile");
	msg2.name("File - TestDriver.dll");
	msg2.file("TestDriver.dll");
	comm.postMessage(msg2);

	Message msg3;
	msg3.to(dest);
	msg3.from(source);
	msg3.value("sendingFile");
	msg3.name("File - DemoProjectRequirements.dll");
	msg3.file("DemoProjectRequirements.dll");
	comm.postMessage(msg3);


	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	TestRequest testRequest;
	testRequest.name("Test1");
	testRequest.author("Harshini");
	testRequest.date("11-16-2018");
	testRequest.addDll("SampleTests.dll");
	testRequest.addDll("TestDriver.dll");
	Message testReqMessage(dest, source);
	testReqMessage.name("Test sample");
	testReqMessage.attribute("testRequest", testRequest.toString());
	comm.postMessage(testReqMessage);

	TestRequest testRequest2;
	testRequest2.name("Test1");
	testRequest2.author("Harshini");
	testRequest2.date("11-16-2018");
	testRequest2.addDll("DemoProjectRequirements.dll");
	Message testReqMessage2(dest, source);
	testReqMessage2.name("Test sample");
	testReqMessage2.attribute("testRequest", testRequest2.toString());
	comm.postMessage(testReqMessage2);
}

void recvMessage(Comm& comm)
{
	while (true)
	{
		Message msg = comm.getMessage();
		if (msg.containsKey("log"))
		{
			std::cout << "\n The result of the tests were " << msg.value("result") << "\n";
			std::string decoded = b64decode(msg.value("log"));
			std::cout << decoded;
		}
	}
}

int main(int argc, char* argv[])
{
	std::cout << "\n  Demonstrating Peer1 in Peer-To-Peer Comm Demo";
	std::cout << "\n ===============================================";

	if (argc < 2)
	{
		std::cout << "\n  Please enter path to directory for files to send \n";
		return 1;
	}
	std::string path = argv[1];


	::SetConsoleTitle(L"ClientDemo");

	EndPoint epPeer1("localhost", 8082);
	EndPoint epPeer2("localhost", 8081);

	Comm comm(epPeer1, "Peer1");
	comm.start();

	comm.setSendFilePath(path);
	comm.setSaveFilePath("./");

	std::function<void()> recvProc = [&]() { recvMessage(comm); };
	std::thread recvThread(recvProc);
	recvThread.detach();

	sendMessage(comm, epPeer1, epPeer2);
	std::cin.get();
	comm.stop();
	std::cout << "\n\n";
	return 0;
}
