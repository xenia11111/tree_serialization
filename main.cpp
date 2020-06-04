#include "pch.h"

#include <iostream>
#include<fstream>
#include<string>
#include"Tree.h"
#include"CommandParser.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc > 5) { 
		std::cerr << "Too many arguments!"; 
		return EXIT_FAILURE;
	}
	
	CommandParser parser(argc, argv);
	string input = parser.getInput();
	string output = parser.getOutput();
	
	try {
		if(input==""||output==""){ 
			std::cerr << "Wrong parameters!";
			return EXIT_FAILURE;
		}

		ifstream in(input);
		ofstream out(output);

		if (in.fail()) {
			throw ifstream::failure("file error");
		}

		Tree* t = new Tree();
		t->deserialize(in);
		t->Print();
		t->serialize(out);
	}
	catch (ifstream::failure& ) {
		cout << "Error: Failure to open file" << std::endl;
	}
	return 0;
}
