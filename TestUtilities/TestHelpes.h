#pragma once
///////////////////////////////////////////////////////////////////////
// TestHelpers.h - facilities for single-user test harness			 //
// ver 2.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Most Projects, CSE687 - Object Oriented Design       //
// Author:      Lakshmi Harshini Kuchibhotla, Syracuse University,	 //
//              lkuchibh@syr.edu									 //
// Source:		Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////

/*
* Package Operations:
* -------------------
* This package provides classes:
* - TestHelper    Provides functions to print lines from files to show code.
*
* Required Files:
* ---------------
*   StringUtilities.h
*   FileUtilities.h
*
* Maintenance History:
* --------------------
* ver 2.0 : 13 Oct 2018
* - Extracted into a different file.
* ver 1.0 : 12 Jan 2018
* - first release
*
* Notes:
* ------
* - Designed to provide all functionality in header file.
* - Implementation file only needed for test and demo.
*
* Planned Additions and Changes:
* ------------------------------
* - none yet
*/
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/FileSystem/FileSystem.h"
#include <iomanip>
#include <fstream>

namespace TestUtilities
{
	using Path = std::string;
	using Message = std::string;
	using Line = size_t;
	using File = std::string;
	using Files = std::vector<File>;

	class TestHelpers
	{
	public:
		static bool showDirContents(const Path& path, const Message& msg = "");
		static bool showFileLines(const Path& path, Line start, Line end, const Message& msg = "");
	};

	//----< show all C++ source files in path >------------------------

	inline bool TestHelpers::showDirContents(const Path& path, const Message& msg)
	{
		if (msg.size() > 0)
			Utilities::title(msg);
		std::cout << "\n  " << FileSystem::Path::getFullFileSpec(path);
		if (!FileSystem::Directory::exists(path))
		{
			std::cout << "\n  path does not exist";
			return false;
		}

		Files files = FileSystem::Directory::getFiles(path);
		for (auto file : files)
		{
			std::string ext = FileSystem::Path::getExt(file);
			if (ext == "h" || ext == "cpp")
				std::cout << "\n    " << file;
		}
		std::cout << "\n";
		return true;
	}
	//----< show specified contiguous lines from a code file >---------

	inline bool TestHelpers::showFileLines(const Path& path, Line start, Line end, const Message& msg)
	{
		if (msg.size() > 0)
			Utilities::title(msg);
		std::cout << "\n  " << FileSystem::Path::getFullFileSpec(path);

		std::ifstream file(path);
		if (!file.good())
		{
			std::cout << "\n  can't open file";
			return false;
		}

		std::string line;
		size_t count = 0;
		while (std::getline(file, line))
		{
			if (++count < start) continue;
			if (count > end) break;
			std::cout << "\n  " << std::setw(4) << count << " " << line;
		}
		std::cout << "\n";
		return true;
	}

	//----< displays newline when instance goes out of scope >---------

	struct Cosmetic { ~Cosmetic() { std::cout << "\n"; } };
}