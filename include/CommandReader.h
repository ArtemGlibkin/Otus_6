#pragma once
#include <iostream>
#include <string>
#include "CommandBlock.h"
#include <istream>

class CommandReader
{
	int blockSize = 0;
	bool exitFlag = false;
	bool dynamicBlock = false;
	int dynamicBlockCounter = 0;

	bool isExit(const Command& cmd)
	{
		static const std::string eof = std::string("EOF");
		return exitFlag = (cmd == eof);
	}
	
	bool isBeginBlock(const Command& cmd)
	{
		static const std::string beginBlock = std::string("{");
		return cmd == beginBlock;
	}

	bool isEndBlock(const Command& cmd)
	{
		static const std::string endBlock = std::string("}");
		return cmd == endBlock;
	}

	void beginBlockHandler()
	{
		dynamicBlock = true;
		dynamicBlockCounter++;
	}

	void endBlockHandler()
	{
		if (!dynamicBlock)
			return;

		dynamicBlockCounter--;
		if (dynamicBlockCounter == 0)
			dynamicBlock = false;
	}

	bool inputHandler(const Command& input, CommandBlock& block)
	{
		if (isExit(input))
			return false;
		if (isEndBlock(input))
		{
			endBlockHandler();
			return dynamicBlock;
		}
		if (isBeginBlock(input))
		{
			beginBlockHandler();
			return !(dynamicBlock && (dynamicBlockCounter == 1));
		}

		block.add(input);
		return true;
	}

	void readBlock()
	{
		CommandBlock cmdBlock;
		std::string input;
		int i = 0;
		for (std::string input; (dynamicBlock || (i != blockSize)) && std::getline(std::cin, input); i++)
		{
			if (!inputHandler(input, cmdBlock))
				break;
		}
		cmdBlock.print();
	}

public:
	CommandReader(int n) :blockSize(n) {};
	void reader()
	{
		while (!exitFlag)
			readBlock();
	}
};