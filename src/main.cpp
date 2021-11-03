#include <iostream>
#include <string>
#include "ReaderFactory.hpp"
//:-)
//:)
//:(
//:-)
//:-(
//:-]

int main(int argc, char** argv)
{
	Reader *reader;
	std::string line;
	std::string text;
	std::string fileName;
	std::string xmlFileName;

	if (argc <= 1) {
		std::cout << "Please provide arguments as" << std::endl 
			  << "1 => if Console Only input" << std::endl 
			  << "2 => if Text File" << std::endl 
			  << "3 => if Test File + XML file" << std::endl;
	}
	switch(atoi(argv[1])){
		case 1:
			std::cout << "Please enter the text for analysis. Press CTRL+d to process the text" << std::endl;
			while (!std::cin.eof()){
				getline(std::cin, line);
				text += line+"\n";
				if (std::cin.fail())
					break;
			}

			std::cout << std::endl << "Input text is " << std::endl << text ;
			std::cout <<"===================================================" << std::endl;

			reader = ReaderFactory::createReader(text, "console");
			if (reader != NULL) {
			   reader->parse();
			   reader->printSmileysAndTopTenWords();
			   delete reader;
			}
			break;
		case 2:
			std::cout << "Please enter the text file name" << std::endl;
			std::cin >> fileName;

			reader = ReaderFactory::createReader(fileName, "text");
			if (reader != NULL) {
			   std::cout << "Text file name is " << reader->getInput() << std::endl;
			   std::cout <<"===================================================" << std::endl;
			   reader->parse();
			   reader->printSmileysAndTopTenWords();
			   delete reader;
			}
			break;
		case 3:
			{
			std::cout << "Please enter the text file name and XML file name" << std::endl;
			std::cin >> fileName;
			std::cin >> xmlFileName;


			reader = ReaderFactory::createReader(fileName, "text");
			if (reader != NULL) {
		           std::cout << "Text file name is " << reader->getInput() << std::endl;
			   std::cout <<"===================================================" << std::endl;
			   reader->parse();
			   reader->printSmileysAndTopTenWords();
			   delete reader;
			   reader = NULL;
			}

			std::cout <<"===================================================" << std::endl;
			reader = ReaderFactory::createReader(xmlFileName, "xml");
			if (reader != NULL) {
			   std::cout << std::endl << "XML file name is " << reader->getInput() << std::endl;
			   std::cout <<"===================================================" << std::endl;
			   reader->parse();
			   reader->printSmileysAndTopTenWords();
			   delete reader;
			}

			break;
			}
		default:
			break;
	}


}


