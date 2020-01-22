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
			std::string output;

			int position = 0;

			if(!WordOnlyContainsAandBs(toDecode))
				return "Algorithm not applicable";
			else
			{
				for (std::string::size_type i = 0; i < toDecode->length(); i ++)
				{
					if (isalpha(toDecode->at(i)))
					{
						position = 0;

						if (toDecode->at(i) == 'b')
							position += 16;

						if (toDecode->at(i + 1) == 'b')
							position += 8;

						if (toDecode->at(i + 2) == 'b')
							position += 4;

						if (toDecode->at(i + 3) == 'b')
							position += 2;

						if (toDecode->at(i + 4) == 'b')
							position += 1;

						output.push_back(alphabet[position]);

						i += 4;
					}
					else
						output.push_back(toDecode->at(i));
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
	
	private:
		std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

		bool WordOnlyContainsAandBs(std::string* toDecode)
		{
			for (size_t i = 0; i < toDecode->length(); i++)
			{
				if (isalpha(toDecode->at(i)) && toDecode->at(i) != 'a' && toDecode->at(i) != 'b')
					return false;
			}

			return true;
		}
};

