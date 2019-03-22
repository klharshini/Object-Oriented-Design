/////////////////////////////////////////////////////////////////////////////
// TestExecutor.h - Defined functions from TestExecutor.h                  //
// ver 1.0                                                                 //
//															               //
// Author:      Lakshmi Harshini Kuchibhotla, Syracuse University          //
//              lkuchibh@syr.edu					                       //
/////////////////////////////////////////////////////////////////////////////

#include "TestExecutor.h"

TestExecutor::TestExecutor(std::shared_ptr<LoggerUtilities::ILogger> logger): pLog(logger)
{
}

bool TestExecutor::executeAllTests(std::vector<ITest*> tests)
{
	bool result = false;
	for (ITest* test : tests)
	{
		bool temp = execute(std::shared_ptr<ITest>(test));
		if (!temp)
			result = false;
	}
	return result;
}

bool TestExecutor::execute(std::shared_ptr<ITest> pTest)
{
	bool result = false;
	try
	{
		result = pTest->test();  // execute test which may throw an exception
		log(pTest->name(), pTest->author(), result);
	}
	catch (std::exception& ex)
	{
		pLog->write("\n Exception Thrown!");
		log(pTest->name(), pTest->author(), false);
		pLog->write(ex.what());
	}
	return result;
}


std::string GetTime()
{
	auto timeNow = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(timeNow);
	struct tm buf;
	localtime_s(&buf, &t);
	std::stringstream ss;
	ss << std::put_time(&buf, "%Y-%m-%d %X");
	return ss.str();
}
//----< display test results >---------------------------------------
//The log just takes the below inputs name, author and text then formats it and prints.
void TestExecutor::log(const std::string& name, const std::string& author, const bool& res)
{
	std::string result = res ? "Passed" : "Failed";
	pLog->write("\n\n--->  " + name + "  " + result + "\n******************************** \n\n" + "Author: " + author + ", Time of execution: " + GetTime() + "\n\n\n");
}

#ifdef TEST_TESTEXECUTOR
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

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Please enter the directory for the tests";
	}
	std::string path = argv[1];
	std::vector<ITest *> tests;
	ITest* test2 = new Test2();
	ITest* test3 = new Test3();
	tests.push_back(test2);
	tests.push_back(test3);
	std::shared_ptr<LoggerUtilities::TestLogger> testLogger = std::shared_ptr<LoggerUtilities::TestLogger>(new LoggerUtilities::TestLogger());
	testLogger->addStream(&std::cout);
	TestExecutor executor = TestExecutor(testLogger);
	executor.executeAllTests(tests);
	std::cin.get();
	std::cout << "\n\n";

	return 0;
}

#endif // TEST_TESTEXECUTOR
