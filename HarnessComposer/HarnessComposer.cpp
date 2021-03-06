#pragma once
///////////////////////////////////////////////////////////////////////
// harnessComposer.cpp - Main function that starts the composer and	 //
//					   the childprocesses							 //
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
* The main function that demonstrates the project
*
* Required Files:
* ---------------
*   TestHarness.h
*   Process.h
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

#include <iostream>
#include <string>
#include "TestHarness.h"
#include "../Process/Process.h"


int main(int argc, char* argv[])
{
	std::string port;
	if (argc < 2)
	{
		std::cout << "\n No default port given for Harness, using the value 8081";
		port = "8081";
	}
	else
		port = argv[1];

	std::string saveFileDir;
	if (argc < 3)
	{
		std::cout << "\n No default save file dir given for Harness, using the value ./ ";
		saveFileDir = "./dllFiles";
	}
	else
	{
		saveFileDir = argv[2];
	}
	std::string exeDir;

	if (argc < 4)
	{
		std::cout << "\n No default executables dir given for Harness, using the value ./ ";
		exeDir = "./";
	}
	else
	{
		exeDir = argv[3];
	}
	std::cout << port;
	std::cout << "\n The Process for the Main Harness";
	std::cout << "\n ====================================";
	std::stringstream convert(port);
	int port_int = 0;
	convert >> port_int;
	MsgPassingCommunication::EndPoint endPoint("localhost", port_int);
	MsgPassingCommunication::Comm comm(endPoint, "Harness");
	comm.setSaveFilePath(saveFileDir);
	TestHarness testHarness(comm);
	
	std::string appPath = exeDir + "WpfApp1.exe";

	Process p0;
	p0.application(appPath);
	p0.commandLine(" INDEMO");
	p0.create();

	Process p1;
	appPath = exeDir + "TestHarness.exe";
	p1.application(appPath);
	p1.title("TestExecutive");
	p1.commandLine(" ../HarnessComposer/dllFiles/ 8083 localhost:8081");
	p1.create();

	Process p2;
	p2.application(appPath);
	p2.title("TestExecutive");
	p2.commandLine(" ../HarnessComposer/dllFiles/ 8084 localhost:8081");
	p2.create();

	std::cin.get();
}
