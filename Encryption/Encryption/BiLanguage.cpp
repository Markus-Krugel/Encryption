#include "EncryptCommand.h"
#include <list>
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
			output.push_back(tolower(toEncode->at(i)));

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
		return "";
	}

	std::string DecodeFromeFile(std::string* filePath)
	{
		return "";
	}
};

