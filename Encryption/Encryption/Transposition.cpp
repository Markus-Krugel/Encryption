#include "EncryptCommand.h"
#include <iostream>
#include <vector>

// Stores the word in a different order, where every x th char is grouped together

class Transposition
{
	public:
	
		std::string Encode(std::string* toEncode)
		{
			return Encode(toEncode, 5);
		}
	
		std::string Encode(std::string* toEncode, int optional)
		{
			std::string output;
			output.reserve(toEncode->length());
	
			std::vector<std::string> wordList;
			wordList.resize(optional);
	
			for (std::string::size_type i = 0; i < toEncode->length(); ++i)
			{
				int position = i % optional;
	
				wordList[position].push_back(toEncode->at(i));
			}
	
			for (size_t i = 0; i < wordList.size(); i++)
			{
				output.append(wordList[i]);
			}
	
			return output;
		}
	
		std::string EncodeFromeFile(const char* filePath)
		{
			std::string text;
	
			std::ifstream in(filePath, std::ios::in | std::ios::binary);
			if (in)
			{
				in.seekg(0, std::ios::end);
				text.resize(in.tellg());
				in.seekg(0, std::ios::beg);
				in.read(&text[0], text.size());
				in.close();
			}
			else
				std::cout << "Could not open file !" << std::endl;
	
			return Encode(&text);
		}
	
		std::string Decode(std::string* toDecode)
		{
			return "";
		}
	
		std::string DecodeFromeFile(std::string* filePath)
		{
			return "";
		}
};

