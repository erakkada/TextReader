#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include "TextFileReader.hpp"
#include "XmlFileReader.hpp"
#include "ConsoleReader.hpp"
#include "Reader.hpp"

Reader::Reader() 
{
}

Reader::~Reader() 
{

}

void Reader::parse() 
{

}
#if 0
Reader* Reader::createReader(const std::string& input,  const std::string& type)
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

std::string Reader::getInput() const  
{
	return m_input;
}	

int Reader::findSmileys(const std::string& line, const int pos)
{
	int positionInLine = 0; 
	std::vector<int> vec_positionInLine;
	vec_positionInLine.reserve(5);
	int foundSmiley = 0;

	// Traverse the string character by character to detect smileys at any position in the word.
	for (int i = 0; i < line.length(); i++) {
		//Check for colon character
		if  (line[i] == ':') {
			positionInLine = pos+i+1;
			i++;
			//Checking next character after colon is any of below. Then it is a smiley
			if ((line[i] == '-') || (line[i] == '(') || (line[i] == ')') || (line[i] == ']')) {
				//Checking next character after '-' is any of below. Then it is a smiley
				if (line[i] == '-') {
					i++;
					if ((line[i] == '(') || (line[i] == ')') || (line[i] == ']')) {
						map_smileyPositions[m_lineNumber].emplace_back(positionInLine);
						foundSmiley = 1;
					}
				} else {
					map_smileyPositions[m_lineNumber].emplace_back(positionInLine);
					foundSmiley = 1;
				}
			}
		}
	}
	return foundSmiley;
}


int Reader::findWords(const std::string& line)
{
	std::string word;
	int positionInLine = 0, ret = 0;

	m_lineNumber++;

	std::stringstream iss(line);

	while (iss >> word){
		//Dont consider words starts with or contains smileys
		if(!findSmileys(word, positionInLine)) {
			map_Words[word]++;
		}
		else {
			//If atleast one smiley is present in the enitre line
			ret = 1; 
		}
		positionInLine += word.length() + 1; // whitespace counted as 1
	}
	return ret;
}


void Reader::findTopTenWords()
{
	for (auto const& k : map_Words) {
		vec_topTenWords.emplace_back(std::make_pair(k.second, k.first));
	}
	sort(vec_topTenWords.begin(), vec_topTenWords.end());
	reverse(vec_topTenWords.begin(), vec_topTenWords.end());
	//Erase elements except first 10 
	if (vec_topTenWords.size()>10)
		vec_topTenWords.erase(vec_topTenWords.begin()+10, vec_topTenWords.end());
}


void Reader::printSmileysAndTopTenWords()
{
	//Printing the positions of smileys
	if (map_smileyPositions.size() == 0) {
		std::cout << "No smileys found in the input" << std::endl;
	}
	else {
		std::cout << "Smiley found in " << std::endl;
		for (auto const& k : map_smileyPositions) {
			std::cout << "line " << k.first <<  " at position ";
			for(auto const& i : k.second)
				std::cout << i << " ";
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
int Reader::getSmileyCount()
{
	int smileyCount = 0;
	for (auto const& k : map_smileyPositions) {
		smileyCount += k.second.size();
	}
	return smileyCount;
}

std::map<int, std::vector<int>> Reader::getSmileyPositions()
{
	return map_smileyPositions;
}

std::vector<std::pair<int, std::string>> Reader::getTopTenWords()
{
	return vec_topTenWords;
}

std::vector<std::string> Reader::getSmileyTags()
{
	return {};
}
