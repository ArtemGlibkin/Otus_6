#include <iostream>
#include "CommandReader.h"
int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        CommandReader cr(std::atoi(argv[1]));
        cr.reader();
		return 0;
    }
    else
        std::cout << "Input format wrong" << std::endl;
	return -1;
}