#pragma once
/////////////////////////////////////////////////////////////////////
// ReuirementsDemo.cpp - Register and export the tests from		   //
//						 RequirementsDemo.h						   //
// ver 1.0												           //
//                                                                 //
//Lakshmi Harhini Kuchibhotla, Syracuse University, Fall 2018      //
// email: lkuchibh@syr.edu										   //
/////////////////////////////////////////////////////////////////////

#define IN_DLL
#include "RequirementsDemo.h"


__declspec(dllexport) ITests* get_ITests()
{
	std::string path = "../";
	
	TestContainer* testContainer = new TestContainer();
	ITest* test1 = new TestRequirement1(path);
	ITest* test2a = new TestRequirement2a(path);
	ITest* test2b = new TestRequirement2b(path);
	ITest* test3 = new TestRequirement3(path);
	ITest* test4a = new TestRequirement4(path);
	ITest* test4b = new TestRequirement5(path);
	ITest* test5a = new TestRequirement6(path);
	ITest* test5b = new TestRequirement7(path);
	ITest* test5c = new TestRequirement8(path);
	ITest* test6a = new TestRequirement9(path);
	ITest* test6b = new TestRequirement10(path);

	testContainer->allTests.push_back(test1);
	testContainer->allTests.push_back(test2a);
	testContainer->allTests.push_back(test2b);
	testContainer->allTests.push_back(test3);
	testContainer->allTests.push_back(test4a);
	testContainer->allTests.push_back(test4b);
	testContainer->allTests.push_back(test5a);
	testContainer->allTests.push_back(test5b);
	testContainer->allTests.push_back(test5c);
	testContainer->allTests.push_back(test6a);
	testContainer->allTests.push_back(test6b);


	return testContainer;
}
