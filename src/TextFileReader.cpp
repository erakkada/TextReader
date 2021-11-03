#include <iostream>
#include <fstream>
#include "TextFileReader.hpp"

void TextFileReader::parse() {
	std::ifstream file;
	std::string line;

	file.open(m_input);
	if (file.fail()){
		std::cerr << "Error - Failed to open " << m_input << std::endl;
		return;
	}
	while (std::getline(file, line)) {
		findWords(line);
	}
	findTopTenWords();
}
