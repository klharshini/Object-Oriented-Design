#pragma once
///////////////////////////////////////////////////////////////////////
// TestHarness.h - The Main mmother harness that composes that		 //
//				   hosts a process pool, test request pool and       //
//				   that assings the tests to the processes			 //
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
* The package provides a TestHarness class that comprises of the process pool and assigns the tests to it
*
* Required Files:
* ---------------
*   Cpp11-BlockingQueue.h
*   Comm.h
*   Message.h
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
#include "../CppCommWithFileXfer/Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"
#include "../CppCommWithFileXfer/MsgPassingComm/Comm.h"
#include "../CppCommWithFileXfer/Message/Message.h"

using namespace MsgPassingCommunication;

class TestHarness
{
private:
	BlockingQueue<Message> testRequests;
	BlockingQueue<Message> testExecutives;
	MsgPassingCommunication::Comm& comm;
public:
	void sendMessage(MsgPassingCommunication::Message msg);
	void recvMsg(TestHarness* t);
	void onRequestRecieved(MsgPassingCommunication::Message msg);
	void onExecutiveMsgRecieved(MsgPassingCommunication::Message msg);
	void AssignTestRequest();
	TestHarness(MsgPassingCommunication::Comm& comm);
	~TestHarness();
};

