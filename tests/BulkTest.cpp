#include <gtest/gtest.h>
#include "CommandReader.h"
#include <sstream>
TEST(BulkTest, SimpleTest) {
	
	std::stringstream ss;
	ss << "cmd1\ncmd2\ncmd3\ncmd4\ncmd5";
	CommandReader cr(3);
	ASSERT_EQ(cr.readBlock(ss).toString(), std::string("bulk:cmd1, cmd2, cmd3\n"));
}

TEST(BulkTest, BracketsTest) {

	std::stringstream ss;
	ss << "cmd1\ncmd2\n{\ncmd3\ncmd4\ncmd5\n}";
	CommandReader cr(3);
	ASSERT_EQ(cr.readBlock(ss).toString(), std::string("bulk:cmd1, cmd2\n"));
	ss.str(std::string(""));
	ss << "{\ncmd3\ncmd4\ncmd5\n}\n";
	ASSERT_EQ(cr.readBlock(ss).toString(), std::string("bulk:cmd3, cmd4, cmd5\n"));
}

TEST(BulkTest, EnclosedBracketsTest) {

	std::stringstream ss;
	ss << "{\ncmd3\n{\ncmd4\ncmd5\n}\ncmd6\n}\n";
	//std::cout << ss.str() << std::endl;
	CommandReader cr(3);
	cr.readBlock(ss).print();
	std::string str = cr.readBlock(ss).toString();
	std::cout << str << std::endl;
	ASSERT_EQ(str, std::string("bulk:cmd3, cmd4, cmd5, cmd6\n"));
}