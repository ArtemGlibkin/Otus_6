#pragma once
#include <string>
#include <list>
#include <iostream>
#include <sstream>
#include <chrono>
#include <fstream>

using Command = std::string;
class CommandBlock
{
	std::list<Command> cmdBlock;
	time_t time;

	void displayPrint(const std::string& out)
	{
		std::cout << out << std::endl;
	}

	void filePrint(const std::string& out)
	{
		std::string fileName = "bulk" + std::to_string(time) + ".log";
		std::ofstream file(fileName);
		file << out << std::endl;
	}

public:
	CommandBlock() = default;
	void add(const Command& cmd)
	{
		if (cmdBlock.empty())
			time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		cmdBlock.push_back(cmd);
	}

	void print()
	{
		if (cmdBlock.empty())
			return;
		std::stringstream ss;
		ss << "bulk:";
		auto lastElement = --cmdBlock.end();
		auto it = cmdBlock.begin();
		for (it; it != lastElement; it++)
		{
			ss << *it << ", ";
		}
		ss << *it << std::endl;
		displayPrint(ss.str());
		filePrint(ss.str());
	}
};