#include "pch.h"
#include "CommandParser.h"


CommandParser::CommandParser(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-') {
			string key = argv[i];
			if ((key == "-i" || key == "-o") && i + 1 < argc) {
				m_options[key] = argv[i + 1];
				i++;
			}
				
			else {
				m_options[key] = "";
			}
		}
	
	}
}

const string CommandParser::getInput()
{
	if (m_options.count("-i"))
		return m_options["-i"];
	else
		return "";
}

const string CommandParser::getOutput()
{
	if (m_options.count("-o"))
		return m_options["-o"];
	else
		return "";
}