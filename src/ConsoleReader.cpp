#include <iostream>
#include <sstream>
#include "Reader.hpp"
#include "ConsoleReader.hpp"

void ConsoleReader::parse() {
	std::string line;

	std::istringstream iss(m_input);

	while (std::getline(iss, line)) {
		findWords(line);
	}
	findTopTenWords();
}

