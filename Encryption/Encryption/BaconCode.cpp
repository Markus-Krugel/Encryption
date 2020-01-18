#include "EncryptCommand.h"
#include <iostream>


// Replaces an letter based on its alphabet position as a 5 bit binary with a and b's
// e.g. D is aaabb and Z is babbb

class BaconCode : public EncryptCommand
{
	public:
	
		std::string Encode(std::string* toEncode)
		{
			std::string output;
	
			// as this is a 5 bit binary code it has 32 options maximum
			int numberOfOptions = 32;
	
			for (std::string::size_type i = 0; i < toEncode->length(); ++i)
			{
				if (isalpha(toEncode->at(i)))
				{
					for (size_t j = 0; j < alphabet.length(); j++)
					{
						if (toupper(toEncode->at(i)) == alphabet[j])
						{
							if (j < numberOfOptions / 2)
								output.push_back('a');
							else
								output.push_back('b');
	
							if ((j % 16) < 8)
								output.push_back('a');
							else
								output.push_back('b');
	
							if ((j % 8) < 4)
								output.push_back('a');
							else
								output.push_back('b');
	
							if ((j % 4) < 2)
								output.push_back('a');
							else
								output.push_back('b');
	
							if (j % 2 == 0)
								output.push_back('a');
							else
								output.push_back('b');
							
							break;
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
	
		std::string Decode(std::string* toDecode)
		{
			return "";
		}
	
		std::string DecodeFromeFile(std::string* filePath)
		{
			return "";
		}
	
	private:
		std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
};

