#ifndef READER_HPP
#define READER_HPP

#include <vector>
#include <map>
class Reader {
public:
	Reader();

	Reader(const std::string& input) : m_input(input), m_lineNumber(0)
	{

	}

	static Reader* createReader(const std::string& input, const std::string& type);

	virtual ~Reader(); 


	std::string getInput() const;
	virtual void printSmileysAndTopTenWords();
	virtual void parse();

	//For Boost testing
	int getSmileyCount();
	std::map<int, std::vector<int>> getSmileyPositions();
	std::vector<std::pair<int, std::string>> getTopTenWords();
 	virtual std::vector<std::string> getSmileyTags();
private:
	std::map<std::string, int> map_Words;	

	int findSmileys(const std::string&, const int pos);
protected:
	std::map<int, std::vector<int>> map_smileyPositions;	
        std::vector<std::pair<int, std::string>> vec_topTenWords;
	std::string m_input;
        int m_lineNumber;

	int findWords(const std::string&);
	void findTopTenWords();
};
#endif
