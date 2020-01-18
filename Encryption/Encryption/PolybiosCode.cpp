#include "EncryptCommand.h"
#include <iostream>


// Stores the alphabet in a 5x5 table where i and j shares the same cell . The row is the ten's digit and the column the single unit.

class PolybiosCode : public EncryptCommand
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
							// this is being done because i and j share the same cell
							// and therefore from j on every cell has to go one back
							if (j >= 9)
								j--;
	
							// the + '0' is to convert the int to a char because otherwise pushback would interpret it as an ascii character
	
							// the rounding up does not work if the number is divisible by 5
							if (j % 5 == 0)
								output.push_back(((int)ceil((double)j / 5) +1) + '0');
							else
								output.push_back(((int)ceil((double)j / 5)) + '0');
							output.push_back(((j % 5) + 1) + '0');
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

