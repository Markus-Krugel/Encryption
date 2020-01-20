#include "EncryptCommand.h"
#include <iostream>


// Adds a 'bi' after every vocal.

class BiLanguage : public EncryptCommand
{
	public:
	
		std::string Encode(std::string* toEncode)
		{
			std::string output;
	
			for (std::string::size_type i = 0; i < toEncode->length(); ++i)
			{
				output.push_back(toEncode->at(i));
	
				if (charIsVocal(&toEncode->at(i)))
				{
					output.append("bi");
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
			std::string output;

			for (std::string::size_type i = 0; i < toDecode->length(); ++i)
			{
				output.push_back(toDecode->at(i));

				if (isalpha(toDecode->at(i)) && charIsVocal(&toDecode->at(i)))
				{
					if (toDecode->at(i + 1) == 'b' && tolower(toDecode->at(i + 2)) == 'i')
						i += 2;
					else
						return "Algorithm not applicable";
				}
			}

			return output;
		}

		std::string DecodeFromeFile(const char* filePath)
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

			return Decode(&text);
		}
};

