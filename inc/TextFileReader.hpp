#ifndef TESTFILEREADER_HPP
#define TESTFILEREADER_HPP

#include <iostream>
#include "Reader.hpp"

class TextFileReader : public Reader {
public:
	TextFileReader() {}
	TextFileReader(const std::string& input) : Reader(input) {} 
	~TextFileReader() {}

	void parse();
};

#endif
