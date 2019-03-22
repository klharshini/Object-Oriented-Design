////////////////////////////////////////////////////////////////////////////
// DemoTests.cpp : multiple test classes to demo					      //
// ver 1.0                                                                //
//                                                                        //
// Application : OOD F18 Project 2			                              //
// Platform    : VS17 Community - Windows 10				              //
// Author:      Lakshmi Harshini Kuchibhotla, Syracuse University         //
//              lkuchibh@syr.edu					                      //
// Source      : Ammar Salman, EECS Department, Syracuse University       //
//               313/788-4694, hoplite.90@hotmail.com                     //
////////////////////////////////////////////////////////////////////////////
/*
*  Package description:
* ======================
*  This is a demo test driver DLL package. It follows the same
*  protocol defined in ITest.h package. For DllLoader, it doesn't care
*  if the TestDriver contains one or many Test Classes as it will attempt
*  to get the collection of ITest*.
*
*  Required files:
* =================
*  ITests.h
*
*  Maintainence History:
* =======================
*  ver 3.0 : 11 Nov 2018
*  - Modified the logs inside
*  ver 2.0 : 07 Oct 2018
*  - replaced all tests
*  - Ammar's infrastructure has not been modified
*  ver 1.0 - first release
*/

#define IN_DLL
#define ARG_SIZE 256

#include "../TestUtilities/ITest.h"
#include <thread>
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

//////////////////////////////////////////////////////////////////
// Test class Demo1

class Demo1 : public ITest {
public:
	DLL_DECL bool test()
	{
		pRes_->log("\n  Testing Demo1 class");
		pRes_->log("\n ---------------------");
		pRes_->log("\n--Test always passes\n");
		return true;
	}
	DLL_DECL std::string name()
	{
		return "Demo1";
	}
	DLL_DECL std::string author()
	{
		return "Harshini";
	}
	DLL_DECL void acceptHostedResource(LoggerUtilities::IHostedLogger * pRes)
	{
		pRes_ = pRes;
	}
private:
	LoggerUtilities::IHostedLogger * pRes_ = nullptr;
};

//////////////////////////////////////////////////////////////////
// Test class Demo2

class Demo2 : public ITest {
public:
	DLL_DECL bool test()
	{
		pRes_->log("\n  Testing Demo2 class");
		pRes_->log("\n ---------------------");
		pRes_->log("\n--Test always fails\n");
		return false;
	}
	DLL_DECL std::string name()
	{
		return "Demo2";
	}
	DLL_DECL std::string author()
	{
		return "Harshini";
	}
	DLL_DECL void acceptHostedResource(LoggerUtilities::IHostedLogger * pRes)
	{
		pRes_ = pRes;
	}
private:
	LoggerUtilities::IHostedLogger * pRes_ = nullptr;
};
//////////////////////////////////////////////////////////////////
// Test class Demo3

class Demo3 : public ITest {
public:
	DLL_DECL bool test()
	{
		pRes_->log("\n  Testing Demo3 class");
		pRes_->log("\n ---------------------");
		pRes_->log("\n--Test always throws\n");
		std::exception ex("\nwas thrown\n");
		throw ex;
		return true; // won't get here
	}
	DLL_DECL std::string name()
	{
		return "Demo3";
	}
	DLL_DECL std::string author()
	{
		return "Harshini";
	}
	DLL_DECL void acceptHostedResource(LoggerUtilities::IHostedLogger * pRes)
	{
		pRes_ = pRes;
	}
private:
	LoggerUtilities::IHostedLogger * pRes_ = nullptr;
};

//////////////////////////////////////////////////////////////////
// Test class Demo4

class Demo4 : public ITest {
public:
	DLL_DECL bool test()
	{
		pRes_->log("\n  Testing Demo4 class");
		pRes_->log("\n ---------------------");
		pRes_->log("\n--Test takes time to execute \n");
		std::this_thread::sleep_for(std::chrono::milliseconds(15000));
		return true;
	}
	DLL_DECL std::string name()
	{
		return "Demo4";
	}
	DLL_DECL std::string author()
	{
		return "Harshini";
	}
	DLL_DECL void acceptHostedResource(LoggerUtilities::IHostedLogger * pRes)
	{
		pRes_ = pRes;
	}
private:
	LoggerUtilities::IHostedLogger * pRes_ = nullptr;
};


//////////////////////////////////////////////////////////////////
// Container that's responsible for returning a collection of the
// previous 2 test classes. It will return a collection of:
// 1) ITest* that points to an instance of TestProcessCmdArgs
// 2) ITest* that points to an instance of TestConverter

class TestCollection : public ITests {
	DLL_DECL std::vector<ITest*> tests();
};

// this is where each test class is instantiated and added to collection
DLL_DECL std::vector<ITest*> TestCollection::tests()
{
	std::vector<ITest*> tests_vec;
	tests_vec.push_back(new Demo1);
	tests_vec.push_back(new Demo2);
	tests_vec.push_back(new Demo3);
	tests_vec.push_back(new Demo4);

	return tests_vec;
}

//////////////////////////////////////////////////////////////////////////////
// this section is where each Test Driver DLL completely differs from other
// test drivers. Although the same name can be used in all TestDrivers, the 
// actual instance of TestCollection is different in the way it returns 
// different collection of ITest*.

DLL_DECL ITests* get_ITests()
{
	return new TestCollection;
}
