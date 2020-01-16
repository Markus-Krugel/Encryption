#include "EncryptCommand.h"
#include <list>
#include <iostream>


// Adds an 'U' to the beginning of a word, if the word starts with
// a vocal it replaces it with an 'U'.

class USprache : public EncryptCommand
{
	public:

		std::string Encode(std::string* toEncode)
		{
			bool wordStart = true;
			std::list<char> text;

			for (std::string::size_type i = 0; i < toEncode->length(); ++i) 
			{
				if (wordStart)
				{
					wordStart = false;

					if (charIsVocal(&toEncode->at(i)))
					{
						if (isupper(toEncode->at(i)))
							text.push_back('U');
						else
							text.push_back('u');

						continue;
					}
					text.push_back('U');
				}
				else if (isspace(toEncode->at(i)))
					wordStart = true;
				
				text.push_back(tolower(toEncode->at(i)));
			}

			std::string output;
			output.reserve(text.size());

			// store size now as it will change with each iteration
			int textSize = text.size();
			for (size_t i = 0; i < textSize; i++)
			{
				output.push_back(text.front());
				text.pop_front();
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

