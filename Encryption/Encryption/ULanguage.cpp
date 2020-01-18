#include "EncryptCommand.h"
#include <iostream>


// Adds an 'U' to the beginning of a word, if the word starts with
// a vocal it replaces it with an 'U'.

class ULanguage : public EncryptCommand
{
	public:

		std::string Encode(std::string* toEncode)
		{
			bool wordStart = true;
			std::string output;

			for (std::string::size_type i = 0; i < toEncode->length(); ++i) 
			{
				if (wordStart)
				{
					wordStart = false;

					if (charIsVocal(&toEncode->at(i)))
					{
						if (isupper(toEncode->at(i)))
							output.append("U");
						else
							output.append("u");

						continue;
					}
					output.append("U");
				}
				else if (isspace(toEncode->at(i)))
					wordStart = true;
				
				char temp = (char)(tolower(toEncode->at(i)));

				output.append(std::string(&temp));
			}

			return output;
		}
	
		std::string EncodeFromeFile(const char* filePath)
		{
			std::string output;

			std::ifstream in(filePath, std::ios::in | std::ios::binary);
			if (in)
			{
				in.seekg(0, std::ios::end);
				output.resize(in.tellg());
				in.seekg(0, std::ios::beg);
				in.read(&output[0], output.size());
				in.close();
			}
			else
				std::cout << "Could not open file !" << std::endl;

			return Encode(&output);
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

