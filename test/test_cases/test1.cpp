#define BOOST_TEST_MODULE "ReaderClassModule"
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "ReaderFactory.hpp"  

BOOST_AUTO_TEST_CASE(instance_creation)
{
    Reader *reader = NULL;
    reader = ReaderFactory::createReader("assets/sample.txt", "text");
    BOOST_CHECK(reader != NULL);
    TextFileReader *textReader = dynamic_cast<TextFileReader*>(reader);
    BOOST_CHECK(textReader != NULL);
    delete reader;

    reader = ReaderFactory::createReader("NULL", "console");
    BOOST_CHECK(reader != NULL);
    ConsoleReader *consoleReader = dynamic_cast<ConsoleReader*>(reader);
    BOOST_CHECK(consoleReader != NULL);
    delete reader;

    reader = ReaderFactory::createReader("assets/sample.xml", "xml");
    BOOST_CHECK(reader != NULL);
    XmlFileReader *xmlReader = dynamic_cast<XmlFileReader*>(reader);
    BOOST_CHECK(xmlReader != NULL);
    delete reader;
}

BOOST_AUTO_TEST_CASE( reader_constructors )
{
  Reader obj("input.txt");
  BOOST_CHECK(obj.getInput() == "input.txt");
}

BOOST_AUTO_TEST_CASE( reader_assignment )
{
  Reader obj("sample.txt");
  Reader obj2;
  obj2 = obj;
  BOOST_CHECK_EQUAL(obj2.getInput(), "sample.txt");
}

BOOST_AUTO_TEST_CASE( reader_parse_text )
{
  std::map<int, std::vector<int>> map_smileyCountPosition;
  std::vector<std::pair<int, std::string>> vec_topTenWords;
  int smileyCount = 0;

  int ref_totalSmileyCount = 6;
  int ref_totalFileLineNumber = 4; 
  std::map<int, std::vector<int>> ref_smileyPositions;
  std::vector<std::pair<int, std::string>> ref_topTenWords;

  //Reference line number and positions in each line
  ref_smileyPositions[2].emplace_back(12);
  ref_smileyPositions[3].emplace_back(22);
  ref_smileyPositions[4].emplace_back(1);
  ref_smileyPositions[4].emplace_back(3);
  ref_smileyPositions[4].emplace_back(37);
  ref_smileyPositions[4].emplace_back(40);

  //Reference top ten words
  ref_topTenWords.emplace_back(std::make_pair(3, std::string("I")));
  ref_topTenWords.emplace_back(std::make_pair(2, std::string("am")));
  ref_topTenWords.emplace_back(std::make_pair(1, std::string("what")));
  ref_topTenWords.emplace_back(std::make_pair(1, std::string("to")));
  ref_topTenWords.emplace_back(std::make_pair(1, std::string("this")));
  ref_topTenWords.emplace_back(std::make_pair(1, std::string("test")));
  ref_topTenWords.emplace_back(std::make_pair(1, std::string("taking")));
  ref_topTenWords.emplace_back(std::make_pair(1, std::string("right")));
  ref_topTenWords.emplace_back(std::make_pair(1, std::string("now")));
  ref_topTenWords.emplace_back(std::make_pair(1, std::string("is")));

  Reader *reader = NULL;
  reader = ReaderFactory::createReader("assets/sample.txt", "text");
  BOOST_CHECK(reader != NULL);

  reader->parse();
  smileyCount = reader->getSmileyCount();
  map_smileyCountPosition = reader->getSmileyPositions();
  vec_topTenWords = reader->getTopTenWords();

  //Total number of smileys present in the text file
  BOOST_CHECK(ref_totalSmileyCount == smileyCount); 
  //Check positions of each smiley in each line
  BOOST_CHECK(ref_smileyPositions == map_smileyCountPosition);
  BOOST_CHECK(ref_topTenWords == vec_topTenWords);
  delete reader;
}


BOOST_AUTO_TEST_CASE( reader_parse_xml )
{
  std::map<int, std::vector<int>> map_smileyCountPosition;
  std::vector<std::pair<int, std::string>> vec_topTenWords;
  std::vector<std::string> vec_smileyTags;
  int smileyCount = 0;

  int ref_totalSmileyCount = 6;
  std::vector<std::pair<std::string, std::vector<int>>> ref_smileyPositions;
  std::vector<std::string> ref_vecSmileyTags;
  std::vector<std::pair<int, std::string>> ref_topTenWords;

  //Line number and positions in each line
  std::vector<int> v;

  std::pair<std::string, std::vector<int>> p;
  p.first = "genre";
  v.emplace_back(10);
  v.emplace_back(13);
  v.emplace_back(17);
  p.second = v;
  ref_smileyPositions.emplace_back(p);

  p.first = "genre";
  v.clear();
  v.emplace_back(9);
  p.second = v;
  ref_smileyPositions.emplace_back(p);

  p.first = "description";
  p.second = v;
  ref_smileyPositions.emplace_back(p);

  p.first = "description";
  v.clear();
  v.emplace_back(12);
  p.second = v;
  ref_smileyPositions.emplace_back(p);

  //Reference top ten words
  ref_topTenWords.emplace_back(std::make_pair(8, std::string("the")));
  ref_topTenWords.emplace_back(std::make_pair(7, std::string("of")));
  ref_topTenWords.emplace_back(std::make_pair(5, std::string("to")));
  ref_topTenWords.emplace_back(std::make_pair(5, std::string("in")));
  ref_topTenWords.emplace_back(std::make_pair(5, std::string("a")));
  ref_topTenWords.emplace_back(std::make_pair(4, std::string("and")));
  ref_topTenWords.emplace_back(std::make_pair(4, std::string("Visual")));
  ref_topTenWords.emplace_back(std::make_pair(4, std::string("The")));
  ref_topTenWords.emplace_back(std::make_pair(4, std::string("Fantasy")));
  ref_topTenWords.emplace_back(std::make_pair(4, std::string("Computer")));

  Reader *reader = NULL;
  reader = ReaderFactory::createReader("assets/sample.xml", "xml");
  BOOST_CHECK(reader != NULL);

  reader->parse();
  smileyCount = reader->getSmileyCount();
  map_smileyCountPosition = reader->getSmileyPositions();
  vec_smileyTags = reader->getSmileyTags();
  vec_topTenWords = reader->getTopTenWords();

  //Total number of smileys present in the text file
  BOOST_CHECK(ref_totalSmileyCount == smileyCount); 

  //Check positions of each smiley in each line
  int i = 0, j = 0;
  for (auto const& k : map_smileyCountPosition){
    j = 0;
    for (auto const& p : k.second){
      BOOST_CHECK(p == ref_smileyPositions[i].second[j]);
      j++;
    }
    i++;
  }
  BOOST_CHECK(ref_topTenWords == vec_topTenWords);
  delete reader;
}

