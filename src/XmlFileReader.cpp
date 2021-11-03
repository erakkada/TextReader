#include <iostream>
#include "XmlFileReader.hpp"

int XmlFileReader::is_leaf(xmlNode * node)
{
	xmlNode * child = node->children;
	while(child) {
		if(child->type == XML_ELEMENT_NODE) return 0;

		child = child->next;
	}
	return 1;
}

void XmlFileReader::find_elements(xmlNode * node, int indent_len)
{
    std::string line;

    while(node)
    {
        if(node->type == XML_ELEMENT_NODE)
        {
	  if (is_leaf(node)) {
		line = (const char*)xmlNodeGetContent(node);
		//Returns 1 if smileys are found
		if (1 == findWords(line)) {
			//Store the tag when smileys are found
			vec_TagNames.emplace_back((const char*)node->name);
		}
	  }
        }
	find_elements(node->children, indent_len + 1);
        node = node->next;
    }
}

void XmlFileReader::parse() 
{
        xmlNode *root_element = NULL;

        m_doc = xmlReadFile(m_input.c_str(), NULL, 0);
	if (m_doc == NULL) {
		std::cout << "Could not parse the XML file" << std::endl;
	}

	root_element = xmlDocGetRootElement(m_doc);

	find_elements(root_element, 1);
	findTopTenWords();
}

void XmlFileReader::printSmileysAndTopTenWords()
{
    int i =0;
    //Printing the positions of smileys
    if (map_smileyPositions.size() == 0) {
	std::cout << "No smileys found in the input" << std::endl;
    }
    else {
	    std::cout << "Smiley found in below XML tags" << std::endl;
	    for (auto const& k : map_smileyPositions) {
		    std::cout << "<" << vec_TagNames[i++] << ">";
		    std::cout << " at position ";
		    for(auto const& j : k.second)
			    std::cout << j << " ";
		    std::cout << std::endl;
	    }
	    std::cout << std::endl;
    }	

    std::cout << "Top ten words in the input are below" << std::endl;
    for (int i = 0; ((i < vec_topTenWords.size()) && (i < 10)); i++) {
	    std::cout <<"Word \"" << vec_topTenWords[i].second << "\" counts " << vec_topTenWords[i].first << " times" << std::endl; 
    } 
}


//Below section is for Boost testing
std::vector<std::string> XmlFileReader::getSmileyTags()
{
    return vec_TagNames;
}
