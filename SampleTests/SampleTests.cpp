#pragma once
///////////////////////////////////////////////////////////////////////
// SampleTests.cpp  - Sample Tests									 //
//																	 //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Most Projects, CSE687 - Object Oriented Design       //
// Author:      Lakshmi Harshini Kuchibhotla, Syracuse University,	 //
//              lkuchibh@syr.edu									 //
///////////////////////////////////////////////////////////////////////


#define IN_DLL

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

class Test1 : public ITest
{
private:
	LoggerUtilities::IHostedLogger* _pRes;
public:
	bool test()
	{
		_pRes->log("Passing Test log");
		return true;
	}

	// Inherited via ITest
	virtual DLL_DECL std::string name() override
	{
		return "Test 1";
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

class Test2 : public ITest
{
private:
	LoggerUtilities::IHostedLogger* _pRes;
public:
	bool test()
	{
		_pRes->log("Failing Test  \n");
		return false;
	}

	// Inherited via ITest
	virtual DLL_DECL std::string name() override
	{
		return "Test 2";
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

class Test3 : public ITest
{
private:
	LoggerUtilities::IHostedLogger* _pRes;
public:
	bool test()
	{
		_pRes->log("Throwing Test\n");
		std::exception ex("\n  -- this test always throws -- \n\n");
		throw ex;
		throw ex;
		return true;
	}

	// Inherited via ITest
	virtual DLL_DECL std::string name() override
	{
		return "Test 3";
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

__declspec(dllexport) ITests* get_ITests()
{
	std::string path = "..";

	TestContainer* testContainer = new TestContainer();
	ITest* test1 = new Test1();
	ITest* test2 = new Test2();
	ITest* test3 = new Test3();

	testContainer->allTests.push_back(test1);
	testContainer->allTests.push_back(test2);
	testContainer->allTests.push_back(test3);
	return testContainer;
}
