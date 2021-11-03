#ifndef READERFACTORY_HPP
#define READERFACTORY_HPP

#include "TextFileReader.hpp"
#include "XmlFileReader.hpp"
#include "ConsoleReader.hpp"
#include "Reader.hpp"

class ReaderFactory {

public:
   ReaderFactory() {}
   ~ReaderFactory() {}
   static Reader* createReader(const std::string& input,  const std::string& type);
};

Reader* ReaderFactory::createReader(const std::string& input,  const std::string& type)
{
	if (type == "console"){
		return new ConsoleReader(input);
	}
	if (type == "text"){
		return new TextFileReader(input);
	}
	if (type == "xml"){
		return new XmlFileReader(input);
	}
	return NULL;
}
#endif
