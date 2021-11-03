#ifndef CONSOLEREADER_HPP
#define CONSOLEREADER_HPP
#include <iostream>
#include "Reader.hpp"
class ConsoleReader : public Reader {
   public:
	ConsoleReader(const std::string& input) : Reader(input) {} 
	~ConsoleReader() {}

	void parse();
};
#endif
