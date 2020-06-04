#pragma once
#include <map>
#include <string>

using namespace std;

class CommandParser
{
public:
	CommandParser(int argc, char *argv[]);
	const string getInput();
	const string getOutput();

private:
	map <string, string> m_options;
};


