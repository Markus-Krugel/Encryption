#include "EncryptCommand.h"
#include <iostream>


// Replaces letters with the letter from the other side of the alphabet.
// e.g 'A' with 'Z' and 'G' with 'T'

class Atbash : public EncryptCommand
{
	public:
	
		std::string Encode(std::string* toEncode)
		{
			std::string output;
	
			for (std::string::size_type i = 0; i < toEncode->length(); ++i)
			{
				if (isalpha(toEncode->at(i)))
				{
					for (size_t j = 0; j < alphabet.length(); j++)
					{
						if (toupper(toEncode->at(i)) == alphabet[j])
						{
							// Ensures that the correct letter case is used
							if (isupper(toEncode->at(i)))
								output.push_back(reverseAlphabet[j]);
							else
								output.push_back(tolower(reverseAlphabet[j]));
						}
					}
				}
				else
					output.push_back(toEncode->at(i));
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
	
		// its the same procedure as encoding
		std::string Decode(std::string* toDecode)
		{
			return Encode(toDecode);
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

	private:
		std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		std::string reverseAlphabet = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
};

