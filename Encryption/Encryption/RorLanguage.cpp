#include "EncryptCommand.h"
#include <iostream>


// Adds an 'o' after every consonant and repeats the consonant.

class RorLanguage : public EncryptCommand
{
	public:
	
		std::string Encode(std::string* toEncode)
		{
			std::string output;
	
			for (std::string::size_type i = 0; i < toEncode->length(); ++i)
			{
				output.push_back(toEncode->at(i));
	
				if (isalpha(toEncode->at(i)) && !charIsVocal(&toEncode->at(i)))
				{
					output.append("o");
					// lower letter because it does look less obvious if word starts with consonant
					output.push_back(tolower(toEncode->at(i)));
				}
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

