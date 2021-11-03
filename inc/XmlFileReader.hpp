#ifndef XMLFILEREADER_HPP
#define XMLFILEREADER_HPP

#include <iostream>
#include <libxml/parser.h>
#include "Reader.hpp"

class XmlFileReader : public Reader {
public:
	XmlFileReader() {}
	XmlFileReader(const std::string& input) : Reader(input)  
	{
		m_doc = NULL;
	}
	~XmlFileReader() 
	{
		xmlFreeDoc(m_doc);
		xmlCleanupParser();
	}

	void parse();
        void printSmileysAndTopTenWords();

	//For boost testing
        std::vector<std::string> getSmileyTags();
private:
	xmlDoc *m_doc;
	//To store the xml tag name when smileys are found
	std::vector<std::string> vec_TagNames;

	int is_leaf(xmlNode *node);
	void find_elements(xmlNode *node, int indent_len);
        void printXmlTagStructure(const int& index);
};

#endif
