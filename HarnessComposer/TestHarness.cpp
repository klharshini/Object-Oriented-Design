#pragma once
/////////////////////////////////////////////////////////////////////
// TestHarmness.cpp - Implementation of the TestHarness class	   //
// ver 1.0												           //
//                                                                 //
//Lakshmi Harhini Kuchibhotla, Syracuse University, Fall 2018      //
// email: lkuchibh@syr.edu										   //
/////////////////////////////////////////////////////////////////////

#include "TestHarness.h"


void TestHarness::sendMessage(MsgPassingCommunication::Message msg)
{
	comm.postMessage(msg);
}

void TestHarness::recvMsg(TestHarness * t)
{
	MsgPassingCommunication::Message msg;
	std::cout << "\n Started Listening on recv thread ";
	while (true)
	{
		msg = comm.getMessage();
		std::cout << "\n  Harness recvd  message \"" << msg.name() << "\"";
		if (msg.command() == "stop")
			break;
		if (msg.containsKey("testRequest"))
		{
			t->onRequestRecieved(msg);
		}
		if (msg.containsKey("status"))
		{
			t->onExecutiveMsgRecieved(msg);
		}
	}
}

void TestHarness::onRequestRecieved(MsgPassingCommunication::Message msg)
{
	std::cout << "\n Enqueueing a testRequest from " << msg.from().toString();
	testRequests.enQ(msg);
	AssignTestRequest();
}

void TestHarness::onExecutiveMsgRecieved(MsgPassingCommunication::Message msg)
{
	
	std::cout << "\n Enqueueing a test executive from " << msg.from().toString();
	testExecutives.enQ(msg);
	AssignTestRequest();
}

void TestHarness::AssignTestRequest()
{
	if (testExecutives.size() > 0 && testRequests.size() > 0)
	{
		auto testReqMsg = testRequests.deQ();
		auto testExecutiveMsg = testExecutives.deQ();
		MsgPassingCommunication::Message msg;
		msg.to(testExecutiveMsg.from());
		msg.from(testReqMsg.from());
		msg.attribute("testRequest", testReqMsg.value("testRequest"));

		std::cout << "\n Assigning test Requestfrom " << msg.from().toString() << " to executive at" << msg.to().toString();
		sendMessage(msg);
	}
}

TestHarness::TestHarness(MsgPassingCommunication::Comm & c) : comm(c)
{
	comm.start();
	std::function<void()> tproc = [&]() { recvMsg(this); };
	std::thread thread = std::thread(tproc);
	thread.detach();
}

TestHarness::~TestHarness()
{
	comm.stop();
}
